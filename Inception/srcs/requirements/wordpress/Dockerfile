FROM	debian:buster

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

COPY wp-config.php /wordpress/wp-config.php
RUN sed 's/listen = \/run\/php\/php7.3-fpm.sock/listen = 0.0.0.0:9000/' -i /etc/php/7.3/fpm/pool.d/www.conf
COPY script.sh /tmp

RUN mkdir /run/php
RUN	wget https://wordpress.org/latest.tar.gz
RUN	tar xzvf latest.tar.gz
RUN mv /wordpress/* /var/www/html/
RUN	rm -r /wordpress latest.tar.gz
RUN	chown -R www-data:www-data /var/www/html

EXPOSE 9000

CMD  [ "bash", "/tmp/script.sh"]