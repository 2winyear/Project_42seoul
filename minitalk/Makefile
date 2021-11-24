SERVER=server
CLIENT=client

all: server client

server:
	gcc server.c ft_atoi.c ft_putnbr_fd.c -o $(SERVER)

client:
	gcc client.c ft_atoi.c ft_putnbr_fd.c -o $(CLIENT)

clean: 
	rm $(SERVER) $(CLIENT)

fclean: clean

re: clean all


B_SERVER=server_bonus
B_CLIENT=client_bonus

b_all: b_test

b_test: b_server b_client

b_server:
	gcc server_bonus.c ft_atoi.c ft_putnbr_fd.c -o $(B_SERVER)

b_client:
	gcc client_bonus.c ft_atoi.c ft_putnbr_fd.c -o $(B_CLIENT)

b_clean: 
	rm $(B_SERVER) $(B_CLIENT)

b_fclean: b_clean

b_re: b_clean b_all