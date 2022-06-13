"use strict";
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.UserController = void 0;
const common_1 = require("@nestjs/common");
const email_service_1 = require("../email/email.service");
let UserController = class UserController {
    constructor(emailService) {
        this.emailService = emailService;
    }
    async signin() {
        await this.emailService.signin('dudns0503@naver.com');
        return 'signin';
    }
    async signup() {
        await this.emailService.signup('dudns0503@naver.com');
        return 'signup';
    }
};
__decorate([
    common_1.Get('/signin'),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", []),
    __metadata("design:returntype", Promise)
], UserController.prototype, "signin", null);
__decorate([
    common_1.Get('/signup'),
    __metadata("design:type", Function),
    __metadata("design:paramtypes", []),
    __metadata("design:returntype", Promise)
], UserController.prototype, "signup", null);
UserController = __decorate([
    common_1.Controller('user'),
    __metadata("design:paramtypes", [email_service_1.EmailService])
], UserController);
exports.UserController = UserController;
//# sourceMappingURL=user.controller.js.map