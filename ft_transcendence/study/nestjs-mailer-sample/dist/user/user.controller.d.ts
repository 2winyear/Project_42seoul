import { EmailService } from 'src/email/email.service';
export declare class UserController {
    private readonly emailService;
    constructor(emailService: EmailService);
    signin(): Promise<string>;
    signup(): Promise<string>;
}
