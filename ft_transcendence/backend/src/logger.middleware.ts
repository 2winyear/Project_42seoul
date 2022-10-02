import { Injectable, NestMiddleware } from '@nestjs/common';
import { NextFunction, Request, Response } from 'express';
import * as dayjs from 'dayjs';

@Injectable()
export class LoggerMiddleware implements NestMiddleware {
  use(req: Request, res: Response, next: NextFunction) {
    let color: number;

    switch (req.method) {
      case 'GET':
        color = 32;
        break;

      case 'POST':
        color = 35;
        break;

      case 'PUT':
        color = 34;
        break;

      case 'DELETE':
        color = 31;
        break;

      default:
        color = 37;
    }

    const startTime = Date.now();

    console.log(
      `\x1b[33m=====\x1b[0m ${dayjs(startTime)
        .tz()
        .format(
          'YYYY-MM-DD HH:mm:ss.SSS',
        )} \x1b[33m=====\x1b[0m \x1b[${color}m${req.method}\x1b[0m ${
        req.originalUrl
      }`,
    );

    res.on('finish', () => {
      const endTime = Date.now();
      const elapsedTime = (endTime - startTime) / 1000;

      console.log(
        `✨ start time second: [${dayjs(startTime)
          .tz()
          .format('ss.SSS')}] elapsed time: [${elapsedTime}s]`,
      );
    });

    next();
  }
}
