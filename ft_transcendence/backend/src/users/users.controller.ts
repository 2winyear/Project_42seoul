import {
  Controller,
  Get,
  Body,
  Post,
  Put,
  Param,
  ParseIntPipe,
  UploadedFile,
  UseInterceptors,
  UseGuards,
  Delete,
  Query,
  BadRequestException,
} from '@nestjs/common';
import { ApiBearerAuth, ApiOperation, ApiTags } from '@nestjs/swagger';
import { User } from './entities/users.entity';
import { UsersService } from './users.service';
import {
  NicknameDto,
  SimpleUserDto,
  TargetIdDto,
  UserProfileDto,
  WinLoseCountDto,
} from './dto/users.dto';
import { diskStorage } from 'multer';
import { editFileName, imageFileFilter } from '../files/file-uploading.utils';
import { FileInterceptor } from '@nestjs/platform-express';
import { GameRecordDto } from './dto/users.dto';
import { FollowIdDto } from './dto/follow.dto';
import { AuthGuard } from '@nestjs/passport';
import { GetJwtUser } from 'src/auth/jwt.strategy';
import { BlockResultDto } from './dto/blockedUser.dto';

@ApiTags('users')
@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

  @ApiOperation({ summary: '[test for dev] 회원 닉네임/아바타 초기화' })
  @Get('reset/:id')
  async resetUser(@Param('id', ParseIntPipe) id: number): Promise<User> {
    const user = await this.usersService.getUserById(id);

    user.nickname = null;
    user.avatar = null;
    await user.save();
    return user;
  }

  @ApiOperation({ summary: 'seungyel✅ 이미지 업로드' })
  @ApiBearerAuth('access-token')
  @Post('/:myId/uploadImage')
  @UseGuards(AuthGuard())
  @UseInterceptors(
    FileInterceptor('image', {
      storage: diskStorage({
        destination: './files',
        filename: editFileName,
      }),
      fileFilter: imageFileFilter,
    }),
  )
  async uploadedFile(
    @UploadedFile() file,
    @Param('myId', ParseIntPipe) id: number,
  ) {
    const response = {
      originalname: file.originalname,
      filename: file.filename,
      UpdateImg: await this.usersService.findByNicknameAndUpdateImg(
        id,
        file.filename,
      ),
    };
    return response;
  }

  @ApiOperation({ summary: 'kankim✅ 모든 유저의 id, 닉네임, 상태 가져오기' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Get('')
  async getUsers(): Promise<SimpleUserDto[]> {
    const userInfo = await this.usersService.getUsers();

    return userInfo;
  }

  @ApiOperation({ summary: '✅ 본인 정보 가져오기' })
  @ApiBearerAuth('access-token')
  @Get('/own')
  @UseGuards(AuthGuard())
  async getOwnInfo(@GetJwtUser() user: User): Promise<UserProfileDto> {
    if (!user.id) throw new BadRequestException('접근 권한이 없습니다.');
    return user.toUserProfileDto();
  }

  @ApiOperation({ summary: 'kankim✅ 특정 유저의 프로필 조회' })
  @ApiBearerAuth('access-token')
  @Get(':myId')
  @UseGuards(AuthGuard())
  async getUserProfile(
    @Param('myId', ParseIntPipe) myId: number,
    @Query('targetId', ParseIntPipe) targetId: number,
    @GetJwtUser() user: User,
  ): Promise<UserProfileDto> {
    const userProfile = await this.usersService.getUserProfile(
      user,
      myId,
      targetId,
    );

    return userProfile;
  }

  @ApiOperation({ summary: 'kankim✅ 친구 추가' })
  @ApiBearerAuth('access-token')
  @Post(':myId/friends')
  @UseGuards(AuthGuard())
  async addFriend(
    @GetJwtUser() user: User,
    @Param('myId', ParseIntPipe) followerId: number,
    @Body() followIdDto: FollowIdDto,
  ): Promise<void> {
    await this.usersService.addFriend(user, followerId, followIdDto.followId);
  }

  @ApiOperation({ summary: 'kankim✅ 친구 삭제' })
  @ApiBearerAuth('access-token')
  @Delete(':myId/friends')
  @UseGuards(AuthGuard())
  async removeFriend(
    @GetJwtUser() user: User,
    @Param('myId', ParseIntPipe) followerId: number,
    @Body() followIdDto: FollowIdDto,
  ): Promise<void> {
    await this.usersService.removeFriend(
      user,
      followerId,
      followIdDto.followId,
    );
  }

  @ApiOperation({ summary: 'kankim✅ 친구 목록( id, 닉네임 ) 조회' })
  @ApiBearerAuth('access-token')
  @Get(':myId/friends')
  @UseGuards(AuthGuard())
  async getFriends(
    @GetJwtUser() user: User,
    @Param('myId', ParseIntPipe) userId: number,
  ): Promise<SimpleUserDto[]> {
    return await this.usersService.getFriends(user, userId);
  }

  @ApiOperation({ summary: 'kankim✅ 전적 조회' })
  @ApiBearerAuth('access-token')
  @Get(':userId/gameRecords')
  @UseGuards(AuthGuard())
  async getGameRecords(
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<GameRecordDto[]> {
    const gameRecords = this.usersService.getGameRecords(userId);

    return gameRecords;
  }

  @ApiOperation({ summary: 'kankim✅ 닉네임 변경' })
  @ApiBearerAuth('access-token')
  @Put(':myId/nickname')
  @UseGuards(AuthGuard())
  async updateNickname(
    @GetJwtUser() user: User,
    @Param('myId', ParseIntPipe) userId: number,
    @Body() nicknameDto: NicknameDto,
  ): Promise<UserProfileDto> {
    const users = await this.usersService.updateNickname(
      user,
      userId,
      nicknameDto.nickname,
    );

    return users;
  }

  @ApiOperation({ summary: 'kankim✅ 유저의 승,패 카운트 조회' })
  @ApiBearerAuth('access-token')
  @Get(':userId/winLoseCount')
  async getWinLoseCount(
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<WinLoseCountDto> {
    return await this.usersService.getWinLoseCount(userId);
  }

  @ApiOperation({
    summary:
      'kankim✅ 유저 차단하기 토글. target유저를 차단했으면 true, 차단 해제 했으면 false 리턴',
  })
  @ApiBearerAuth('access-token')
  @Put(':myId')
  @UseGuards(AuthGuard())
  async blockUserToggle(
    @GetJwtUser() user: User,
    @Param('myId', ParseIntPipe) myId: number,
    @Body() target: TargetIdDto,
  ): Promise<BlockResultDto> {
    return await this.usersService.blockUserToggle(user, myId, target.targetId);
  }
}
