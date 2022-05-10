# set -e

# if [ -f '/etc/php7/php-fpm.d/www.conf' ]; then
# 	echo "configuring php-fpm..."
# 	cat /etc/php7/php-fpm.d/www.conf \
# 	| sed 's/127.0.0.1:9000/9000/' \
# 	| sed 's/;clear_env = no/clear_env = no/' > /etc/php7/php-fpm.d/wp.conf
	
# 	rm /etc/php7/php-fpm.d/www.conf
# fi

# # if [ -d '/var/www/html/wordpress' ]; then
# # 	echo "wordpress has been found installed in mounted volume."
# # else
# # 	echo "copying initial wordpress data."
# # 	cp $(find / -name wp-config-docker.php) /wordpress/wp-config.php
# # 	cp -r /wordpress /var/www/html
# # fi

# chown -R www-data:www-data /var/www/html

# echo "wordpress has been setted up."

# # exec "$@"

# # !bin/bash/

# # 	Download wordpress compressed file, decompress it,
# # 	move the dir to the right emplacement and delete .tar file

# # mv /tmp/wp-config.php /var/www/wordpress
# # chown -R www-data:www-data /var/www/wordpress/

# # 	Set up daemonize to 'no' in the php-fpm.conf so i can run it properly after

# # sed -i -e "s|MYSQL_DATABASE|'$MYSQL_DATABASE'|g" /var/www/wordpress/wp-config.php
# # sed -i -e "s|MYSQL_USER|'$MYSQL_USER'|g" /var/www/wordpress/wp-config.php
# # sed -i -e "s|MYSQL_PASSWORD|'$MYSQL_PASSWORD'|g" /var/www/wordpress/wp-config.php
# # sed -i -e "s|;daemonize = yes|daemonize = no|g" /etc/php/7.3/fpm/php-fpm.conf
# # mkdir -p /run/php/

# exec /usr/sbin/php-fpm7.3 -F


#!bin/bash/
mkdir -p /run/php/

if [ ! -f /var/www/wordpress/wp-config.php ]
then
wp config create	--allow-root \
					--skip-check \
					--dbname=$DB_NAME \
					--dbuser=$DB_USER \
					--dbpass=$DB_PASSWORD \
					--dbhost=$DB_HOST \
					--dbprefix=wp_ \
					--path=/var/www/wordpress
sleep 10
fi

wp core install		--allow-root \
					--url=$WP_URL \
					--title=test_site \
					--admin_user=$WP_ADMIN \
					--admin_password=$WP_ADMIN_PASSWORD \
					--admin_email=$WP_ADMIN_EMAIL \
					--path=/var/www/wordpress

#wp user create bob	"$WP_REG_USER@$WP_URL" \
#					--allow-root \
#					--role=author \
#					--user_pass=$WP_REG_USER_PASSWORD \
#					--path=/var/www/wordpress

/usr/sbin/php-fpm7.3 -F --nodaemonize