#!/bin/bash

sed -ie 's/127.0.0.1/0.0.0.0/g' /etc/mysql/mariadb.conf.d/50-server.cnf
sed -ie 's/#port/port/g' /etc/mysql/mariadb.conf.d/50-server.cnf

if [ ! -d /var/lib/mysql/$DB_NAME ]; then
  service mysql start
  apt-get install -y gettext-base
  envsubst < /tmp/create_mysql_db.sql | mysql
  service mysql stop
fi

chown -R mysql:mysql /var/lib/mysql

mysqld_safe