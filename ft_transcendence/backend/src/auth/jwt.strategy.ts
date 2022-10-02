import {
  createParamDecorator,
  ExecutionContext,
  forwardRef,
  Inject,
  Injectable,
  UnauthorizedException,
} from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { User } from '../users/entities/users.entity';
import { UsersService } from '../users/users.service';

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy) {
  constructor(
    @Inject(forwardRef(() => UsersService))
    private readonly usersService: UsersService,
  ) {
    super({
      secretOrKey: process.env.EC2_JWT_SECRET || process.env.JWT_SECRET,
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
    });
  }

  private accessTokens: Map<number, string> = new Map<number, string>();

  getJwtAccessToken = (id: number): string => {
    return this.accessTokens[id];
  };

  setJwtAccessToken = (id: number, accessToken: string): void => {
    this.accessTokens.set(id, accessToken);
  };

  deletejwtAccessToken(id: number) {
    this.accessTokens.has(id);
    this.accessTokens.delete(id);
  }

  async validate(payload): Promise<User> {
    const { id, email, accessToken, permit } = payload;
    const user = await this.usersService.getUserByEmail(email);
    if (!user) {
      throw new UnauthorizedException('회원이 아닙니다.');
    }

    const token = this.accessTokens;
    if (token.get(id) !== accessToken) {
      throw new UnauthorizedException('잘못된 토큰입니다.');
    }

    if (permit !== 'permitted') {
      console.log('JWTValidation: Issuing temporary token.');
      return new User();
    }
    return user;
  }
}

export const GetJwtUser = createParamDecorator(
  (data, ctx: ExecutionContext): User => {
    const req = ctx.switchToHttp().getRequest();
    return req.user;
  },
);
