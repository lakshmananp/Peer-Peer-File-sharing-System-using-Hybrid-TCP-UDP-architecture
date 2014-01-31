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
struct hostent *he;
struct in_addr **addr_list;
int sd,nd; /*socket descriptors*/
char buffer[1024]="",buff1[1024]="";
int i=0,len=0;
char tempstore[3][1000];
char store[1000]="";
char *sta=NULL;
int destport;
myclient.sin_family=AF_INET;

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
server1.sin_port=htons(32991);

if(bind(sd,(struct sockaddr*)&server1,sizeof(server1))<0)
perror("bind error");


printf("\n\n\nPhase 2 : The UDP Port number of the Client1 is :%d and its IP address is :%s",ntohs(server1.sin_port),inet_ntoa(server1.sin_addr));





strcpy(buffer,"Client1 doc1");
/*sending the data to the server*/
len=sizeof(server);
if(sendto(sd,buffer,sizeof(buffer),0,(struct sockaddr*)&server,len)==-1)
perror("send error");
printf("\n\nPhase 2 : The file request from Client1 has been sent to the Directory Server");

/*Receiving data from the server*/
strcpy(buffer,"");
len=sizeof(server);
if(recvfrom(sd,buffer,sizeof(buffer),0,(struct sockaddr*)&server,&len)==-1)
perror("receive error");
//if(recvfrom(sd,buff1,sizeof(buff1),0,(struct sockaddr*)&server,&len)==-1)
//perror("receive error");

//puts(buffer);
//puts(buff1);

//segregating the file server name and the corressponding port number
char temp1[100],temp2[100];
int ct=0;
sta=strtok(buffer,"\n");
while(sta!=NULL)
{
strcpy(tempstore[i],sta);
sta=strtok(NULL,"\n");
i++;
}
char filerequest[100];
ct=i;
int destport1;
for(i=0;i<ct;i++)
{
sscanf(tempstore[i],"%s %s %d",temp1,temp2,&destport);
//printf("%s%s%d",temp1,temp2,destport);
if(strcmp(temp1,"Client1")==0)
{
destport1=destport;
strcpy(filerequest,temp2);
}
}

printf("\n\nPhase 2 : File request from Client1 is present in %s and its TCP port number is %d",filerequest,destport1);
//sscanf(buff1,"%d",&destport);

printf("\n\nPhase 2 : End of Phase2 for Client1 \n");
close(sd);
printf("\n\n\n****************************PHASE 2 ENDS ********************************\n\n");
//sleep(2000);
/*TCP CONNECTION COMMENCES*/

printf("\n\n\n\n\n****************************PHASE 3 BEGINS ******************************");


struct sockaddr_in servaddr,servaddr1;
 int sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
  perror("cannot create socket");

bzero(&servaddr,sizeof(servaddr));

servaddr.sin_family=AF_INET;
servaddr.sin_addr=*((struct in_addr *)he->h_addr);
servaddr.sin_port=htons(destport1);


myclient.sin_addr=*((struct in_addr *)he->h_addr);

    
   

if(bind(sockfd,(struct sockaddr*)&myclient,sizeof(myclient))<0)
perror("bind error");
 int port;
// Dynamic tcp port number 
    //struct sockaddr_in sinport;
    socklen_t len12=sizeof(myclient);
    if(getsockname(sockfd,(struct sockaddr *)&myclient,&len12)==-1)
        perror("getsockname");
    else
        port=ntohs(myclient.sin_port);
// connecting to the file server
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

printf("\n\n\nPHASE 3 :The TCP Port number of Client1 is :%d and its IP address is :%s",ntohs(myclient.sin_port),inet_ntoa(myclient.sin_addr));

char buff[1000];
int n=write(sockfd,"Client1 doc1",20);
printf("\n\nPhase 3 : File request from Client1 has been sent to %s",filerequest);
n=read(sockfd,buff,sizeof(buff));

printf("\n\nPhase 3 : Client1 received %s from %s",buff,filerequest);
//puts(buff);

printf("\n\nPhase 3 :  End of Phase3 for Client1 \n\n");
printf("\n\n\n****************************PHASE 3 ENDS ********************************");
close(sockfd);
return 0;
}

