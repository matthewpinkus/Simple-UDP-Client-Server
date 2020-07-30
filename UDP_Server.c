/* Server side implementation of UDP client-server model  */

#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
  
#define BUF_LEN 48
#define PORT 1084

/* 
	Function to reverse instr and store in to outstr, 
	and returns the length of the string
*/
int string_reverse(char *instr, char *outstr) 
{
	int len;
	len = strlen(instr);
	
	for (int i = 0l; i < len; i++)
			outstr[i] = instr[len-1-i];
		
	outstr[len] = '\0';
	return len;
}

int main(int argc, char *argv[])
{ 
	/* Initialising variables */
	int max_iterations; 		/* maximum amount to perform tasks		*/
	int ret; 					/* return bind() code 					*/
	int in_cnt, out_cnt;		/* byte counters for send and receive	*/
	int revs_cnt, i;			/* reverse_string counter, loop counter */
	char client_buf[BUF_LEN]; 	/* client buffer to hold sent string	*/
	char reverse_client_buf[BUF_LEN];
								/* reverses client buffer				*/
	int sockfd; 				/* socket file descriptor 				*/
	struct sockaddr_in server; 	/* server address structure				*/
	struct sockaddr_in client; 	/* client address structure				*/
	int client_len;				/* length of the client address			*/
	unsigned short echo_port; 	/* servers predefined port number		*/
	
	if (argc != 2)
	{
			printf("Requires max iterations, usages is ./server max_iterations");
	}
	
	max_iterations = atoi(argv[1]);
	printf("Server initializing...\n");
	
	/* Set port number and max iterations from command line*/
	echo_port=PORT;
	
	/* Create the socket */
	sockfd = socket(PF_INET, SOCK_DGRAM, 17);
	if (sockfd<0)
	{
			perror("While calling sockfd()");
			exit(EXIT_FAILURE);
	}
	
	/* Set up server address details to bind */
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;
	
	/* Bind the server to a specific socket */
	ret = bind(sockfd, (const struct sockaddr *)&server, sizeof(server));
	if (ret<0)
	{
			perror("While calling bind()");
			close(sockfd);
			exit(EXIT_FAILURE);
	}
	
	/* Server run loop to limit requests */
	
	for (i=0;i<max_iterations;i++) 
	{
		printf("Iteration %d of %d. Waiting for client...\n", i+1, max_iterations);
		
		/* Receive messsage from client */
		client_len = sizeof(client);
		in_cnt = recvfrom(sockfd, client_buf, BUF_LEN, 0, 
				(struct sockaddr *)&client, (socklen_t *)&client_len);
		
		if (in_cnt < 0)
		{
				perror("While calling recvfrom()");
				exit(EXIT_FAILURE);
		}
		
		/* Printing the received message from client*/
		client_buf[in_cnt] = '\0';
		printf("Received message is %d bytes long\n", in_cnt);
		printf("%s\n", client_buf);
		
		/* Reversing the message and printing */
		revs_cnt = string_reverse(client_buf, reverse_client_buf);
		printf("Reversed string is %d bytes long\n", revs_cnt);
		printf("%s\n", reverse_client_buf);
		
		/* Send reversed message back to client */
		out_cnt = sendto(sockfd, reverse_client_buf, revs_cnt+1, 0, 
						(struct sockaddr *)&client, sizeof(client));
		
		if (out_cnt<0)
		{
				perror("While calling sendto()");
				exit(EXIT_FAILURE);
		}
		
		printf("Reply sent\n\n");
	}
	printf("Finished sending and receiving data to/from client!\n");
	close(sockfd);
		
	return 0;
}







