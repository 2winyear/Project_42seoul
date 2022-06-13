import { MailerService } from '@nestjs-modules/mailer';
export declare class EmailService {
    private readonly mailerService;
    constructor(mailerService: MailerService);
    _send(tos: string[], subject: string, templateName: string, context?: any): Promise<boolean>;
    signin(to: string): Promise<void>;
    signup(to: string): Promise<void>;
}
