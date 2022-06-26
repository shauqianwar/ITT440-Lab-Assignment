//reference https://gist.github.com/bricef/2436364
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mcrypt.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int encrypt
(
	void* buffer,
	int buffer_len, 
	char* IV, 
	char* key,
	int key_len 
)
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 )
	{
		return 1;
	}

	mcrypt_generic_init(td, key, key_len, IV);
	mcrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);
  
	return 0;
}

int decrypt
(
	void* buffer,
	int buffer_len,
	char* IV, 
	char* key,
	int key_len 
)
{
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 )
	{
		return 1;
	}
  
	mcrypt_generic_init(td, key, key_len, IV);
	mdecrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);
  
	return 0;
}

void display(char* ciphertext, int len)
{
	int i;
	for (i=0; i<len; i++)
	{
		printf("%d ", ciphertext[i]);
	}
	printf("\n");
}

int main()
{
	int socket_desc, new_socket, c;
	struct sockaddr_in server, client;
	char *message;
	
	FILE *file;
	file = fopen("index.html", "r");
	char response [2048];
	char header[2048] = "HTTP/1.1 200 OK\r\n\n";
	fgets(response,1024,file);
	strcat(header,response);
	
	
	char* plaintext = response;
	char* IV = "";
	char* key = "";
	int keysize = 32;
	char* buffer;
	int buffer_len = 32;
	long valread;
	//create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("Cannot create socket");
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8080);
	
	//bind
	if(bind(socket_desc,(struct sockaddr *)&server, sizeof(server))<0)
	{
		puts("Binding fail");
		return 1;
	}
	puts("Binding done");
	
	//listen
	listen(socket_desc, 5);

	buffer = calloc(1, buffer_len);
	strncpy(buffer, plaintext, buffer_len);


	encrypt(buffer, buffer_len, IV, key, keysize); 
	printf("\ncipher:  ");
	display(buffer , buffer_len);
	
	while(1)
	{
		printf("\nWaiting for connection....\n\n");

		new_socket = accept(socket_desc, NULL, NULL);
		
		send(new_socket, header, sizeof(header),0);
		recv(new_socket, header, sizeof(header), 0);
		printf("\nMessage sent!\n");
		close(new_socket);
	}
	
	return 0;
}
