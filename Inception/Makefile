DCFILE = ./srcs/docker-compose.yml

all:
	bash ./srcs/requirements/tools/hosts.sh
	docker-compose -f $(DCFILE) build
	docker-compose -f $(DCFILE) up -d

fclean: stop rm_cont rm_volumes rm_network rm_images rm_data

stop:
	- docker stop $$(docker ps -qa)
rm_cont:
	- docker rm $$(docker ps -qa)
rm_volumes:
	- docker volume rm $$(docker volume ls -q)
rm_network:
	- docker network rm $$(docker network ls -q) 2>/dev/null
rm_images:
	- docker rmi -f $$(docker images -qa)
rm_data:
	rm -rf /home/seungzel/data/wp
	rm -rf /home/seungzel/data/db
	mkdir /home/seungzel/data/wp
	mkdir /home/seungzel/data/db

up:
	docker-compose ./srcs/docker-compose.yml up -d
down:
	docker-compose down
ps:
	docker-compose ./srcs/docker-compose.yml ps
