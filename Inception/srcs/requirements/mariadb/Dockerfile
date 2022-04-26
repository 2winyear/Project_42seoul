FROM debian:buster

RUN apt-get update -y 
RUN apt-get upgrade -y 
RUN apt-get -y install mariadb-server

COPY /mariadb/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

