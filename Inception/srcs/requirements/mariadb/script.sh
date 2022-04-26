#!/bin/bash

service mysql start

CREATE DATABASE wordpress_db;
echo "CREATE USER 'epicarts'@'%' IDENTIFIED BY 'password'" | mysql
echo "GRANT ALL ON wordpress_db.* TO 'epicarts'@'%'" | mysql
echo "FLUSH PRIVILEGES" | mysql

