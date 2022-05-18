FROM debian:buster

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install nginx -y
RUN apt-get install openssl -y
RUN apt-get install vim -y

COPY ./nginx.conf		/tmp/

RUN openssl req -x509 -sha256 -nodes -days 365 -newkey rsa:2048 \
	-subj "/C=KR/ST=Korea/L=Seoul/O=Seoul42/CN=seungyel.42.fr" \
	-keyout /etc/ssl/private/seungyel.key \
	-out /etc/ssl/certs/seungyel.crt

RUN	rm -rf /etc/nginx/sites-enabled/* && \
	mv tmp/nginx.conf /etc/nginx/sites-available/nginx.conf && \
	ln -fs /etc/nginx/sites-available/nginx.conf /etc/nginx/sites-enabled/

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]