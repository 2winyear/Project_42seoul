if [ "on" == "${AUTOINDEX}" ]; then
	echo "autoindex on!"
	sed -i "s@autoindex off;@autoindex on;@g" /etc/nginx/sites-available/default
fi

service php7.3-fpm start
service mysql start
service nginx start
bash
