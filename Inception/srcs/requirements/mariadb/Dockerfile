FROM debian:buster

COPY		./script.sh				/tmp/
COPY		./create_mysql_db.sql	/tmp/

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get -y install mariadb-server

RUN chmod 111 /tmp/script.sh

CMD [ "bash", "/tmp/script.sh" ]

EXPOSE 3306