FROM debian:buster
RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install nginx -y
RUN apt-get install openssl -y
RUN apt-get install vim -y
RUN openssl req -x509 -sha256 -nodes -days 365 -newkey rsa:2048 \
	-subj "/C=KR/ST=Korea/L=Seoul/O=Seoul42/CN=seungyel.42.fr" \
	-keyout /etc/ssl/private/seungyel.key \
	-out /etc/ssl/certs/seungyel.crt
# RUN echo "127.0.0.1 $intra_id.42.fr" >> /etc/hosts

COPY ./nginx.conf		/etc/nginx/nginx.conf
COPY ./hosts 			/etc/

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]