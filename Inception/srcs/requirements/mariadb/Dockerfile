FROM	debian:latest

RUN	apt-get -y update
RUN	apt-get -y upgrade
RUN	apt-get -y install mariadb-server
RUN	apt-get -y install vim

COPY wp_seungyel_db.sql /
COPY configure.sh /usr/local/bin/

EXPOSE 3306

VOLUME [ "/bar/lib/mysql" ]

ENTRYPOINT [ "configure.sh" ]

CMD		["tail", "-f"]