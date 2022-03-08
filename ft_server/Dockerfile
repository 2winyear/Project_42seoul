FROM debian:buster
LABEL MAINTAINER="seungyel <seungyel.student.42seoul.kr>"
RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install curl -y
RUN apt-get install nginx -y
RUN apt-get install php-fpm -y
RUN apt-get install mariadb-server php-mysql -y
RUN apt-get install openssl -y
RUN apt-get install wget -y
RUN apt-get install php-mbstring php-curl -y

#openssl 설치-개인키생성-인증서생성-권한제한
RUN openssl genrsa -out ft_server.localhost.key 4096; \
	openssl req -x509 -nodes -days 365 \
	-key ft_server.localhost.key \
	-out ft_server.localhost.crt \
	-subj "/C=KR/ST=SEOUL/L=Gaepo-dong/O=42Seoul/OU=seungyel/CN=localhost"; \
	chmod 644 ft_server.localhost.*; \
	mv ft_server.localhost.crt /etc/ssl/certs/; \
	mv ft_server.localhost.key /etc/ssl/private/;

#phpmyadmin
RUN wget https://files.phpmyadmin.net/phpMyAdmin/5.0.2/phpMyAdmin-5.0.2-all-languages.tar.gz
RUN tar -xvf phpMyAdmin-5.0.2-all-languages.tar.gz
RUN mv phpMyAdmin-5.0.2-all-languages phpmyadmin
RUN mv phpmyadmin /var/www/html/

#wordpress
RUN wget https://wordpress.org/latest.tar.gz
RUN tar -xvf latest.tar.gz
RUN mv wordpress/ var/www/html/
RUN chown -R www-data:www-data /var/www/html/wordpress

# init arg
ARG WP_DB_NAME=wordpress
ARG WP_DB_USER=seungyel
ARG WP_DB_PASSWORD=42seoul

# setup mysqlDB(mariaDB)
RUN service mysql start; \
	mysql -e "CREATE DATABASE ${WP_DB_NAME};\
	USE ${WP_DB_NAME}; \
	CREATE USER '${WP_DB_USER}'@'localhost' IDENTIFIED BY '${WP_DB_PASSWORD}'; \
	GRANT ALL PRIVILEGES ON ${WP_DB_NAME}.* TO '${WP_DB_USER}'@'localhost' WITH GRANT OPTION; \
	FLUSH PRIVILEGES;"

COPY ./srcs/server.sh /
COPY ./srcs/config.inc.php /var/www/html/phpmyadmin/
COPY ./srcs/default /etc/nginx/sites-available/
COPY ./srcs/wp-config.php /var/www/html/wordpress/

EXPOSE 80
EXPOSE 443
ENTRYPOINT ["/bin/bash", "/server.sh"]
