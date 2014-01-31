#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<netdb.h>

int main(int argc,char** argv)
{
struct sockaddr_in server,client; /*socket address structures*/
int sd,nd; /*socket descriptors*/
char buffer[1024]="";
int len=0;
struct hostent *he;
struct in_addr **addr_list;
/*Getting the nunki.usc.edu adddress and assigning it */
if((he=gethostbyname("nunki.usc.edu"))==NULL)
{
herror("gethostbyname");
return 2;
}
addr_list=(struct in_addr**)he->h_addr_list;




/*creating the socket*/
sd=socket(AF_INET,SOCK_DGRAM,0);
if(sd<0)
perror("socket creation error");


/*initializing the socket addresses*/
bzero(&server,sizeof(server));


/*initializing the server attributes*/
server.sin_family=AF_INET;
server.sin_addr=*((struct in_addr *)he->h_addr);
server.sin_port=htons(21991);

client.sin_family=AF_INET;
client.sin_addr=*((struct in_addr *)he->h_addr);
client.sin_port=htons(24991);

if(bind(sd,(struct sockaddr*)&client,sizeof(client))<0)
perror("bind error");

printf("\n\n\n****************************PHASE 1 BEGINS ******************************");
printf("\n\nPhase 1:File Server3 has UDP port number =%d and IP address =%s",ntohs(client.sin_port),inet_ntoa(client.sin_addr));


strcpy(buffer,"File_Server3 53991");

/*sending the data to the server*/
len=sizeof(server);
if(sendto(sd,buffer,sizeof(buffer),0,(struct sockaddr*)&server,len)==-1)
perror("send error");


printf("\n\n\nPhase 1: The registration request from File Server3 has been sent to the Directory Server \n\nPhase 1 : End of Phase1 for File Server3\n");
printf("\n\n\n****************************PHASE 1 ENDS ********************************");
close(sd);



char buff[1000],buff1[1000];
struct sockaddr_in servaddr,cliaddr;
int sockfd=socket(AF_INET,SOCK_STREAM,0);
 
if(sockfd<0)
perror("cannot create socket");

bzero(&servaddr,sizeof(servaddr));

servaddr.sin_family=AF_INET;
servaddr.sin_addr=*((struct in_addr *)he->h_addr); 
servaddr.sin_port=htons(53991);
printf("\n\n\n****************************PHASE 3 BEGINS ******************************");

if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
perror("Bind error");
printf("\n\nPhase 3 :File Server3 has TCP port number :%d  And IP address :%s",ntohs(servaddr.sin_port),inet_ntoa(servaddr.sin_addr));
printf("  ");

 // file server keeps listening for connections from clients in a infinite while loop
while(1)
{
listen(sockfd,2);
 len=sizeof(cliaddr);
 int newfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
 int n=read(newfd,buff,sizeof(buff));
 if(strstr(buff,"doc1") != NULL)
 {
 printf("\n\nPhase3 : File Server3 has received a request from Client1 for Doc1");
 strcpy(buff,"");
 strcpy(buff,"doc1");
 }
 else if(strstr(buff,"doc2") != NULL)
 {
 printf("\n\nPhase3 : File Server3 has received a request from Client2 for Doc2");
 strcpy(buff,"");
 strcpy(buff,"doc2");
 }
 n=write(newfd,buff,sizeof(buff));
// puts(buff);

 if(strcmp(buff,"doc1") == 0)
 printf("\n\nPhase3 : File Server3 has sent %s to Client1",buff);
 else if(strcmp(buff,"doc2")==0)
 printf("\n\nPhase3 : File Server3 has sent %s to Client2",buff);
 puts("");
// puts(buff);
}
close(sockfd);



return 0;
}

