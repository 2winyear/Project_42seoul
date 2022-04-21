FROM	debian:latest

RUN		apt-get -y update
RUN		apt-get -y upgrade
RUN		apt-get -y install mariadb-server
RUN		apt-get -y install vim

# RUN		vim /etc/mysql/mariadb.conf.d/50-server.cnf
# bind-addres 주석처리할것.

CMD		["tail", "-f"]