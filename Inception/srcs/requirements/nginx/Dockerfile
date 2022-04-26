# FROM	debian:buster

# LABEL	maintainer="<seungyel@student.42seoul.kr>"

# RUN		apt-get -y update
# RUN		apt-get -y upgrade
# RUN		apt-get -y install openssl
# RUN		apt-get -y install nginx
# RUN		apt-get -y install vim
# RUN		apt-get -y install bash
# RUN		openssl req -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=KR/ST=Seoul/L=Guro/O=42Seoul/OU=gam/CN=seungyel" -keyout localhost.dev.key -out localhost.dev.crt
# RUN		mv localhost.dev.crt etc/ssl/certs/
# RUN		mv localhost.dev.key etc/ssl/private/
# RUN		chmod 600 etc/ssl/certs/localhost.dev.crt etc/ssl/private/localhost.dev.key

# COPY	nginx.conf /etc/nginx/nginx.conf
# COPY    script.sh /tmp/script.sh

# # EXPOSE      80
# EXPOSE      443


FROM debian:buster
RUN apt-get  update
RUN apt-get  install nginx -y
RUN apt-get  install openssl -y
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/ssl/private/nginx.key -out /etc/ssl/certs/nginx.crt -subj "/C=RU/ST=Moscow/L=Moscow/O=DVSGroup/OU=SavchenkoDV/CN=https:\/\/github.com\/SavchenkoDV/emailAddress=dvs.rocket@gmail.com"
COPY ./default etc/nginx/sites-enabled/default
CMD ["nginx", "-g", "daemon off;"]