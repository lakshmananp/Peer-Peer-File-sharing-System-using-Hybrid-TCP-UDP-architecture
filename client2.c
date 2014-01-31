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
struct sockaddr_in server,client,myclient,myclient1; /*socket address structures*/
int sd,nd; /*socket descriptors*/
char buffer[1024]="",buff1[1000]="";
int len=0;
int destport;
myclient.sin_family=AF_INET;
struct hostent *he;
struct in_addr **addr_list;
/*Getting the nunki.usc.edu adddress and assigning it */
if((he=gethostbyname("nunki.usc.edu"))==NULL)
{
herror("gethostbyname");
return 2;
}
addr_list=(struct in_addr**)he->h_addr_list;





printf("\n\n\n\n\n****************************PHASE 2 BEGINS ******************************");


/*creating the socket*/
sd=socket(AF_INET,SOCK_DGRAM,0);
if(sd<0)
perror("socket creation error");


/*initializing the socket addresses*/
bzero(&server,sizeof(server));


/*initializing the server attributes*/
server.sin_family=AF_INET;
server.sin_addr=*((struct in_addr *)he->h_addr);
server.sin_port=htons(31991);

 struct sockaddr_in server1;
server1.sin_family=AF_INET;
server1.sin_addr=*((struct in_addr *)he->h_addr);
server1.sin_port=htons(33991);

if(bind(sd,(struct sockaddr*)&server1,sizeof(server1))<0)
perror("bind error");



printf("\n\n\nPhase 2 : The UDP Port number of  Client2 is :%d and its IP address is :%s",ntohs(server1.sin_port),inet_ntoa(server1.sin_addr));

strcpy(buffer,"Client2 doc2");

/*sending the data to the server*/
len=sizeof(server);

if(sendto(sd,buffer,sizeof(buffer),0,(struct sockaddr*)&server,len)==-1)
perror("send error");
printf("\n\nPhase 2 : The file request from Client2 has been sent to the Directory Server");

fflush(stdin);
/*Receiving data from the server*/
strcpy(buffer,"   ");
len=sizeof(server);
if(recvfrom(sd,buffer,1000,0,(struct sockaddr*)&server,&len)==-1)
perror("receive error");
//printf("\n\n\nPhase 2 :Client 2 has received the following from the server : %s",buffer);
//if(recvfrom(sd,buff1,1000,0,(struct sockaddr*)&server,&len)==-1)
//perror("receive error");
//printf("client2 has received the following from the server:%s %s",buff1,buffer);


//int destport;
char tempstore[3][100];
char *sta=NULL;
char temp1[100],temp2[100];
int ct=0,i=0;

// segregating the fileserver name and the port number and storing it
sta=strtok(buffer,"\n");
while(sta!=NULL)
{
strcpy(tempstore[i],sta);
sta=strtok(NULL,"\n");
i++;
}
ct=i;
char filerequest[100];
int destport1;
for(i=0;i<ct;i++)
{
sscanf(tempstore[i],"%s %s %d",temp1,temp2,&destport);
//printf("%s%s%d",temp1,temp2,destport);
if(strcmp(temp1,"Client2")==0)
{
strcpy(filerequest,temp2);
destport1=destport;
}
}

printf("\n\nPhase 2 : File request from Client2 is present in %s and its TCP port number is %d",filerequest,destport1);
//sscanf(buff1,"%d",&destport);

printf("\n\nPhase 2 : End of Phase2 for Client2 ");
close(sd);
printf("\n\n\n****************************PHASE 2 ENDS ********************************\n\n");


printf("\n\n\n\n\n****************************PHASE 3 BEGINS ******************************");
/*TCP COMMUNICATION WITH THE FILE SERVER*/
struct sockaddr_in servaddr,servaddr1;
int sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
  perror("cannot create socket");

//bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr=*((struct in_addr *)he->h_addr);
servaddr.sin_port=htons(destport1);


myclient.sin_addr=*((struct in_addr *)he->h_addr);


  



if(bind(sockfd,(struct sockaddr*)&myclient,sizeof(myclient))<0)
perror("bind error");
//Dynamic TCP port number
  int port;
    //struct sockaddr_in sinport;
    socklen_t len12=sizeof(myclient);
    if(getsockname(sockfd,(struct sockaddr *)&myclient,&len12)==-1)
        perror("getsockname");
    else
        port=ntohs(myclient.sin_port);

printf("\n\n\nPhase 3: The TCP Port number of Client2 is :%d and its IP address is :%s",ntohs(myclient.sin_port),inet_ntoa(myclient.sin_addr));

connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));


char buff[1000];
printf("\n\nPhase 3: File request from Client2 has been sent to %s",filerequest);
int n=write(sockfd,"Client2 doc2",20);
n=read(sockfd,buff,sizeof(buff));
printf("\n\nPhase 3 :Client2 has received Doc2 from  %s",filerequest);
//puts(buff);
close(sockfd);
printf("\n\nPhase 3: End of phase3 for Client2\n\n");
printf("\n\n\n****************************PHASE 3 ENDS ********************************");
close(sockfd);
return 0;
}

