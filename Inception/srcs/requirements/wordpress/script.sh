set -e

if [ -f '/etc/php7/php-fpm.d/www.conf' ]; then
	echo "configuring php-fpm..."
	cat /etc/php7/php-fpm.d/www.conf \
	| sed 's/127.0.0.1:9000/9000/' \
	| sed 's/;clear_env = no/clear_env = no/' > /etc/php7/php-fpm.d/wp.conf
	
	rm /etc/php7/php-fpm.d/www.conf
fi

if [ -d '/var/www/html/wordpress' ]; then
	echo "wordpress has been found installed in mounted volume."
else
	echo "copying initial wordpress data."
	cp $(find / -name wp-config-docker.php) /wordpress/wp-config.php
	cp -r /wordpress /var/www/html
fi

chown -R www-data:www-data /var/www/html

echo "wordpress has been setted up."

exec "$@"