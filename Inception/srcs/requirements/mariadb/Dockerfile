FROM debian:buster

# COPY ./50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

RUN apt-get update -y 
RUN apt-get upgrade -y 
# RUN apt-get -y install dumb-init
# RUN rm -rf /etc/mysql/mariadb.conf.d/50-server.cnf
RUN apt-get -y install mariadb-server
RUN apt-get -y install mariadb-client

COPY ./script.sh /tmp/script.sh
COPY ./wp-saved.sql /tmp/wp-saved.sql

RUN			chmod 111 /tmp/script.sh
# RUN			mv ./tmp/my.cnf /etc/mysql/my.cnf
# RUN			chmod 0444 /etc/mysql/50-server.cnf

# ENTRYPOINT	["/usr/bin/dumb-init"]

EXPOSE 3306

CMD [ "/tmp/script.sh" ]