# FROM	debian:buster

# RUN	apt-get -y update
# RUN	apt-get -y upgrade
# RUN	apt-get -y install php7.3
# RUN	apt-get -y install php-fpm
# RUN	apt-get -y install php-cli
# RUN	apt-get -y install wget
# RUN	apt-get -y install curl
# RUN	apt-get -y install php-mysql
# RUN	apt-get -y install php-mbstring
# RUN	apt-get -y install php-xml
# RUN	apt-get -y install sendmail
# RUN	apt-get -y install vim
# RUN	apt-get -y install bash
# RUN	wget https://wordpress.org/latest.tar.gz
# RUN	tar -xvf latest.tar.gz 
# RUN mv /wordpress/* /var/www/html/ 
# RUN	rm -r /wordpress latest.tar.gz
# RUN	chown -R www-data:www-data /var/www/html
# RUN mv /var/www/html/wp-config-sample.php /var/www/html/wp-config.php

# EXPOSE 9000

# # ENTRYPOINT  [ "sh", "script.sh"]

# COPY wordpress.conf /etc/nginx/conf.d

FROM debian:buster

RUN apt-get update

RUN apt-get -y install php7.3 php-mysqli php-fpm mariadb-client
COPY ./www.conf /etc/php/7.3/fpm/pool.d

ADD https://ru.wordpress.org/wordpress-5.7.2-ru_RU.tar.gz /var/www/
RUN cd /var/www && tar -xzvf wordpress-5.7.2-ru_RU.tar.gz
RUN rm -f /var/www/wordpress-5.7.2-ru_RU.tar.gz
RUN rm -f /var/www/wordpress/wp-config-sample.php
COPY ./wp-config.php ./var/www/wordpress/

RUN mkdir ./run/php/
CMD ./usr/sbin/php-fpm7.3 -F