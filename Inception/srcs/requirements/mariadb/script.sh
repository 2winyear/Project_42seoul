#!/bin/bash

service mysql start

db_exist=$(echo "SHOW DATABASES" | mysql -u root | grep "wp_db" | wc -l)
echo "CREATE DATABASE wp_db;" | mysql -u root
echo "CREATE USER '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD'" | mysql -u root
echo "GRANT ALL ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%'" | mysql -u root
echo "FLUSH PRIVILEGES" | mysql -u root

if [ $db_exist = "0" ]
then
	mysql wp_db -u root < /tmp/wp-saved.sql
fi
service mysql stop

exec /usr/sbin/mysqld -u root
