import { MailerService } from '@nestjs-modules/mailer';
import { Injectable } from '@nestjs/common';

@Injectable()
export class EmailService {
  constructor(private readonly mailerService: MailerService) {}

  async _send(
    tos: string[],
    subject: string,
    templateName: string,
    context: any = {},
  ): Promise<boolean> {
    await this.mailerService.sendMail({
      to: tos.join(', '),
      subject,
      template: `${templateName}`,
      context,
    });
    return true;
  }

  async sendEmail(to: string, emailAuthCode: string) {
    await this._send([to], 'domodachi 2차 인증번호', 'sendEmail.ejs', {
      email: to,
      emailpassword: emailAuthCode,
    });
  }
}
