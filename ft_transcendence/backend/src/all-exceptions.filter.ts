import {
  ExceptionFilter,
  Catch,
  ArgumentsHost,
  HttpException,
  HttpStatus,
} from '@nestjs/common';
import { HttpAdapterHost } from '@nestjs/core';
import { Request } from 'express';

@Catch()
export class AllExceptionsFilter implements ExceptionFilter {
  constructor(private readonly httpAdapterHost: HttpAdapterHost) {}

  catch(exception: unknown, host: ArgumentsHost): void {
    // In certain situations `httpAdapter` might not be available in the
    // constructor method, thus we should resolve it here.
    const { httpAdapter } = this.httpAdapterHost;

    const ctx = host.switchToHttp();
    const req = ctx.getRequest<Request>();

    const httpStatus =
      exception instanceof HttpException
        ? exception.getStatus()
        : HttpStatus.INTERNAL_SERVER_ERROR;

    const responseBody = {};
    responseBody['statusCode'] = httpStatus;
    if (exception instanceof HttpException) {
      responseBody['name'] = exception.name;
      responseBody['msg'] = exception.message;
    } else {
      responseBody['name'] = 'INTERNAL_SERVER_ERROR';
      responseBody['msg'] = '알 수 없는 서버 에러';
    }
    responseBody['data'] = null;

    httpAdapter.reply(ctx.getResponse(), responseBody, httpStatus);

    console.log('\x1b[36m-----\x1b[0m Request Param \x1b[36m-----\x1b[0m');
    console.log(req.params);

    console.log('\x1b[36m-----\x1b[0m Request Query \x1b[36m-----\x1b[0m');
    console.log(req.query);

    console.log('\x1b[36m-----\x1b[0m Request Body  \x1b[36m-----\x1b[0m');
    console.log(req.body);

    console.log('\x1b[36m-----\x1b[0m Response Body \x1b[36m-----\x1b[0m');
    console.log(responseBody);
  }
}
