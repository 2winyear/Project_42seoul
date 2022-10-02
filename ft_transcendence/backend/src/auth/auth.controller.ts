import {
  Body,
  Controller,
  Get,
  Post,
  Put,
  Delete,
  Query,
  Param,
  ParseIntPipe,
  UseGuards,
} from '@nestjs/common';
import { ApiBearerAuth, ApiOperation, ApiTags } from '@nestjs/swagger';
import { EmailDto, NicknameDto } from '../users/dto/users.dto';
import { AuthService } from './auth.service';
import {
  IsSignedUpDto,
  CodeStringDto,
  IsDuplicateDto,
  SecondAuthResultDto,
} from './dto/auth.dto';
import { AuthGuard } from '@nestjs/passport';
import { GetJwtUser } from './jwt.strategy';
import { User } from 'src/users/entities/users.entity';

@ApiTags('auth')
@Controller('auth')
export class AuthController {
  constructor(private readonly authService: AuthService) {}

  @ApiOperation({ summary: '[test for backend] issue a fresh JWT' })
  @Get('issueJwt/:id')
  async getJwt(@Param('id', ParseIntPipe) id: number): Promise<string> {
    return this.authService.issueJwt(id);
  }

  @ApiOperation({ summary: '[test for backend] test JWT validity' })
  @ApiBearerAuth('access-token')
  @Get('testJwt')
  @UseGuards(AuthGuard())
  async testJwt(): Promise<string> {
    return 'GOOD JWT';
  }

  @ApiOperation({
    summary: 'kankim✅ 유저의 회원가입 여부 확인',
  })
  @Post('isSignedUp')
  async isSignedUp(@Body() codeDto: CodeStringDto): Promise<IsSignedUpDto> {
    return await this.authService.isSignedUp(codeDto.code);
  }

  // @ApiOperation({ summary: 'kankim✅ 회원가입' })
  // @Post('signUp')
  // async signUp(@Body() updateUserdto: UpdateUserDto): Promise<IsSignedUpDto> {
  //   return await this.authService.signUp(updateUserdto);
  // }

  @ApiOperation({ summary: 'kankim✅ 닉네임 중복 확인' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Post('isDuplicateNickname')
  async isDuplicateNickname(
    @Body() nicknameDto: NicknameDto,
  ): Promise<IsDuplicateDto> {
    return await this.authService.isDuplicateNickname(nicknameDto.nickname);
  }

  @ApiOperation({ summary: '로그아웃' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Put('logout/:userId')
  async logOut(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) userId: number,
  ): Promise<void> {
    await this.authService.logoutStatus(user, userId);
  }

  @ApiOperation({ summary: '✅ 2차 인증 등록 시작' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Post('/secondAuth/:userId')
  async startSecondAuth(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) id: number,
    @Body() emailDto: EmailDto,
  ): Promise<SecondAuthResultDto> {
    const isOk = await this.authService.startSecondAuth(
      user,
      id,
      emailDto.email,
    );

    return { isOk, jwt: null };
  }

  @ApiOperation({ summary: '✅ 2차 인증 번호 검증' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Get('/secondAuthVerify/:userId')
  async verifySecondAuth(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) id: number,
    @Query('code') code: string,
  ): Promise<SecondAuthResultDto> {
    return await this.authService.verifySecondAuth(user, id, code);
  }

  @ApiOperation({ summary: '✅ 2차 인증 등록 완료' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Get('/secondAuthEnroll/:userId')
  async enrollSecondAuth(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) id: number,
  ): Promise<void> {
    await this.authService.enrollSecondAuth(user, id);
  }

  @ApiOperation({ summary: '✅ 2차 인증 해제' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Delete('/secondAuth/:userId')
  async disableSecondAuth(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) id: number,
  ): Promise<void> {
    await this.authService.disableSecondAuth(user, id);
  }

  @ApiOperation({ summary: '✅ 2차 인증 수행' })
  @ApiBearerAuth('access-token')
  @UseGuards(AuthGuard())
  @Get('/secondAuth/:userId')
  @UseGuards(AuthGuard())
  async shootSecAuth(
    @GetJwtUser() user: User,
    @Param('userId', ParseIntPipe) id: number,
  ): Promise<SecondAuthResultDto> {
    const result = new SecondAuthResultDto();
    result.isOk = await this.authService.shootSecondAuth(user, id);
    if (result.isOk === true)
      result.jwt = await this.authService.generateUserJwt(user);
    else result.jwt = null;

    return result;
  }
}
