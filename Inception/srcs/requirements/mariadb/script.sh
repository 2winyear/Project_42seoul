#!/bin/bash

sed -ie 's/127.0.0.1/0.0.0.0/g' /etc/mysql/mariadb.conf.d/50-server.cnf
sed -ie 's/#port/port/g' /etc/mysql/mariadb.conf.d/50-server.cnf

if [ ! -d /var/lib/mysql/$DB_NAME ]; then
  service mysql start
  apt-get install -y gettext-base
  envsubst < /tmp/create_mysql_db.sql | mysql
  mysqladmin --user=root --password=$DB_ROOT_PASSWORD
  service mysql stop
fi

chown -R mysql:mysql /var/lib/mysql

mysqld_safe

# service mysql start

# db_exist=$(echo "SHOW DATABASES" | mysql -u root | grep "wp_db" | wc -l)
# echo "CREATE DATABASE wp_db;" | mysql -u root
# echo "CREATE USER '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD'" | mysql -u root
# echo "GRANT ALL ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%'" | mysql -u root
# echo "FLUSH PRIVILEGES" | mysql -u root

# if [ $db_exist = "0" ]
# then
# 	mysql wp_db -u root < /tmp/wp-saved.sql
# fi
# service mysql stop

# exec /usr/sbin/mysqld -u root
