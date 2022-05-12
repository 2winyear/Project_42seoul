FROM	debian:buster

COPY 		/script.sh /tmp/

RUN	apt-get -y update
RUN	apt-get -y upgrade
RUN	apt-get -y install php7.3
RUN	apt-get -y install php-fpm
RUN	apt-get -y install php-cli
RUN	apt-get -y install wget
RUN	apt-get -y install curl
RUN	apt-get -y install php-mysql
RUN	apt-get -y install php-mbstring
RUN	apt-get -y install php-xml
RUN	apt-get -y install sendmail
RUN	apt-get -y install vim
RUN	apt-get -y install bash

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp

WORKDIR /var/www/wordpress

RUN wp core download --path=/var/www/wordpress --allow-root
RUN chown -R www-data:www-data *
RUN chmod -R 755 /var/www/*

RUN sed 's/listen = \/run\/php\/php7.3-fpm.sock/listen = 0.0.0.0:9000/' -i /etc/php/7.3/fpm/pool.d/www.conf

EXPOSE 9000

CMD  [ "bash", "/tmp/script.sh"]