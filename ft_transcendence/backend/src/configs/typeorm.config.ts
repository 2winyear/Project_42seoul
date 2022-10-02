import { TypeOrmModuleOptions } from '@nestjs/typeorm';

export const TypeORMConfig: TypeOrmModuleOptions = {
  type: 'postgres',
  host: process.env.EC2_TYPEORM_HOST || process.env.TYPEORM_HOST,
  port: +process.env.EC2_TYPEORM_PORT || +process.env.TYPEORM_PORT,
  username: process.env.EC2_TYPEORM_USERNAME || process.env.TYPEORM_USERNAME,
  password: process.env.EC2_TYPEORM_PASSWORD || process.env.TYPEORM_PASSWORD,
  database: process.env.EC2_TYPEORM_DATABASE || process.env.TYPEORM_DATABASE,
  entities: ['dist/**/*.entity{.ts,.js}'],
  synchronize: true,
  logging: true,
};
