typedef struct s_server
{
	int server_socket;
	struct sockaddr_in server_address;
	fd_set sockets;
	fd_set read_set;
	fd_set write_set;
	int max_fds;
	int max_id;
} t_server;

typedef struct s_client
{
	int fd;
	int id;
	char *message_buffer;
	struct s_client *next;
} t_client;