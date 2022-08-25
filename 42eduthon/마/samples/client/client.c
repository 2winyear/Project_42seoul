# include	"client.h"

int main(void)
{
	int sock, recv_len, addr_len;
	struct sockaddr_in addr, client_addr;
	s_cpu_data user_data;
	
	// set socket fd
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		perror("socket ");
		return 1;
	}

	// set socket IP, Port
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	// socket bind
	if (bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
	{
		perror("bind ");
		return (1);
	}

	while (1)
	{
		if (recv(sock, (void*)&user_data, sizeof(user_data), 0) > 0)
		{
			printf("user : %.2f%%, sys : %.2f%%, idle : %.2f%%\n",
				user_data.user,
				user_data.sys,
				user_data.idle
			);
			fflush(stdout);
		}
	}
	close(sock);

	return 0;
}