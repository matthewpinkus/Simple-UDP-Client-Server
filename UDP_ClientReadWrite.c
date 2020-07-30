/* 
Client side implementation of UDP client-server model with 
read() and write() functions 
*/

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<errno.h> 

#define PORT 1084
#define BUF_LEN 48


int main(int argc, char *argv[]) 
{
	char send_string[BUF_LEN];			/* string to send from client 	*/
	char reversed_string[BUF_LEN];		/* reversed string from server 	*/
	struct sockaddr_in server = {0}; 	/* avoiding memset 				*/
	int server_len;						/* size of server struct		*/
	int in_cnt, out_cnt;   				/* byte counters 				*/
	int sockfd;							/* file descriptor of socket	*/
	int conn;							/* connection to server			*/

	if (argc!=2)
	{
			printf("Specify string to send to server.\n");
			exit(EXIT_FAILURE);
	}
	/* Decoding message, storing in variable to send to server */
	strcpy(send_string, argv[1]);

	/* Create the socket */
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sockfd<0)
	{
			perror("While calling socket()");
			exit(EXIT_FAILURE);
	}
	
	/* Set up server addresses */
	server.sin_family = PF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;
	
	/* Connecting to the server */
	conn = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
	if (conn<0)
    {
			perror("While calling connect()");
			exit(EXIT_FAILURE);
    }
	
	/* Sending message to server */
	out_cnt = write(sockfd, send_string, BUF_LEN);
	
	if (out_cnt<0)
	{
			perror("While calling write()");
			exit(EXIT_FAILURE);
	}
	printf("Sending \"%s\" to server.\n", send_string);

	/* Receiving message from server */
	server_len = sizeof(server);
	in_cnt = read(sockfd, reversed_string, BUF_LEN);
			
	if (in_cnt<0)
	{
			perror("While calling read()");
			exit(EXIT_FAILURE);
	}
	printf("Server has responded with %s\n", reversed_string);
	
	close(sockfd);
	
	return 0;
}

