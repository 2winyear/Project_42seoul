FROM	debian:buster

LABEL	maintainer="<seungyel@student.42seoul.kr>"

RUN		apt-get -y update
RUN		apt-get -y upgrade
RUN		apt-get -y install openssl
RUN		apt-get -y install nginx
RUN		openssl req -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=KR/ST=Seoul/L=Guro/O=42Seoul/OU=gon/CN=junghan" -keyout localhost.dev.key -out localhost.dev.crt
RUN		mv localhost.dev.crt etc/ssl/certs/
RUN		mv localhost.dev.key etc/ssl/private/
RUN		chmod 600 etc/ssl/certs/localhost.dev.crt etc/ssl/private/localhost.dev.key

COPY	nginx.conf /etc/nginx/nginx.conf
CMD		["nginx", "-g", "daemon on;"]