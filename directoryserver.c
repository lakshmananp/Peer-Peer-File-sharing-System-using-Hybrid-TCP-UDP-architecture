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

#define dirudpport1 21991
#define dirudpport2 31991

/*Structure to store resource details read from the file resource.txt*/
typedef struct storage
{
char line[5][100];
int ct;
}s;

/*Structure to store cost details read from the file topology.txt*/
typedef struct cost
{
int f[3];
}c;

/*Storing the servername and the associated costs which the clients need to contact*/
typedef struct clientrequests
{
char fileservername[5][100];
int costs[5];
int count;
}cr;


int main()
{
/*All initialisations and declarations */
s s1[5];
c c1[5];
cr cr1[5];
int s1count=0;
int c1count=0;
struct hostent *he;
struct in_addr **addr_list;
struct sockaddr_in server,client1,client2,client3,client4,client5; /*socket address structures*/
int sd,nd; /*server and client socket descriptors*/
char buffer[1024]="";
char buffer1[1024]="";
char buffer2[1024]="";
char buffer3[100]="";
char buffer4[100]="";
char tem1[100]="";
char name[50]="directory.txt";
int len1=0,len2=0,len3=0,len4=0,len5=0,flag1,flag2,counter1,counter2,z;
char filename1[15];
int i=0;
/*END OF ALL INITIALISATIONS AND DECLARATIONS*/



/*Getting the nunki.usc.edu adddress and assigning it */
if((he=gethostbyname("nunki.usc.edu"))==NULL)
{
herror("gethostbyname");
return 2;
}
addr_list=(struct in_addr**)he->h_addr_list;


/*creating the UDP socket*/
sd=socket(AF_INET,SOCK_DGRAM,0);
if(sd<0)
{
perror("\n\nSocket creation error");
}


/*initializing the socket addresses*/
bzero(&server,sizeof(server));


/*initializing the server attributes*/
server.sin_family=AF_INET;
server.sin_addr=*((struct in_addr *)he->h_addr);
server.sin_port=htons(dirudpport1);
                                                         /*PHASE 1 BEGINS HERE */



/*binding the socket*/
if(bind(sd,(struct sockaddr*)&server,sizeof(server))<0)
perror("bind error");


printf("\n\n\n\n************************************PHASE 1 BEGINS *********************");
printf("\n\nPHASE 1 :The Directory server has UDP port number :%d and IP address :%s",ntohs(server.sin_port),inet_ntoa(server.sin_addr));



/*receiving from the fileserver*/
len1=sizeof(client1);
if(recvfrom(sd,buffer,20,0,(struct sockaddr*)&client1,&len1)==-1)
perror("receive error");

/*displaying the data received from the fileserver*/
for(i=0;i<12;i++)
filename1[i]=buffer[i];
filename1[i]='\0';
printf("   ");
printf("\n\nPHASE 1 :The Directory_Server has received a request from %s",filename1);
printf("\nCLIENT %s : %s\n",inet_ntoa(client1.sin_addr),buffer);
//strcpy(tem1,inet_ntoa(client1.sin_addr));
strcpy(filename1,"");



/*receiving from the fileserver*/
len2=sizeof(client2);
if(recvfrom(sd,buffer1,20,0,(struct sockaddr*)&client2,&len2)==-1)
perror("receive error");

/*displaying the data received from the file server*/
for(i=0;i<12;i++)
filename1[i]=buffer1[i];
filename1[i]='\0';
printf("\n\nPHASE 1 : The Directory server has received a request from %s",filename1);
strcpy(filename1,"");
printf("\nCLIENT %s : %s\n",inet_ntoa(client2.sin_addr),buffer1);
//strcpy(tem1,inet_ntoa(client2.sin_addr));


/*receiving from the fileserver*/
len3=sizeof(client3);
if(recvfrom(sd,buffer2,20,0,(struct sockaddr*)&client3,&len3)==-1)
perror("receive error");
/*displaying the received data*/
for(i=0;i<12;i++)
filename1[i]=buffer2[i];
filename1[i]='\0';
printf("\n\nPhase 1 : The Directory server has received a request from %s",filename1);
printf("\nCLIENT %s : %s\n",inet_ntoa(client3.sin_addr),buffer2);
//strcpy(tem1,inet_ntoa(client3.sin_addr));
close(sd);

/*Aggregating the details obtained from the file servers together in a single buffer*/
char store[3000]="";
strcat(store,buffer);
strcat(store,"\n");
strcat(store,buffer1);
strcat(store,"\n");
strcat(store,buffer2);
//printf("File contents should be :\n\n");
//puts(store);
char c[1000]; 



/*Writing the buffer into file called directory.txt*/
FILE *fptr; 
fptr=fopen("directory.txt","w"); 
if(fptr==NULL){ printf("Error in opening file directory.txt!"); exit(1); } 
fprintf(fptr,"%s",store); 
fclose(fptr); 
printf("\n\n\nPHASE 1 : The directory.txt file has been created\n\n\nPHASE 1 : End of PHASE 1 for Directory Server ");

printf("\n\n\n****************************PHASE 1 ENDS ********************************");

   					

                                         				/*PHASE 1 ENDS HERE */





  									/*PHASE 2 BEGINS HERE */

struct sockaddr_in server1;
int sd1=socket(AF_INET,SOCK_DGRAM,0);
if(sd1<0)
{
perror("\n\nSocket creation error");
}
/*initializing the socket addresses*/
bzero(&server1,sizeof(server1));


/*initializing the server attributes*/
server1.sin_family=AF_INET;
server1.sin_addr=*((struct in_addr *)he->h_addr);
server1.sin_port=htons(dirudpport2);
printf("\n\n\n\n\n\n*************************PHASE 2 BEGINS *******************************");


/*binding the socket*/
if(bind(sd1,(struct sockaddr*)&server1,sizeof(server1))<0)
perror("bind error");

printf("\n\nThe Directory server has UDP port number :%d and IP address :%s",ntohs(server1.sin_port),inet_ntoa(server1.sin_addr));

char buffer31[20]="";
char buffer41[20]="";
int k=0,l=0;
/*Receiving the client requests*/
len4=sizeof(client4);
if(recvfrom(sd1,buffer3,100,0,(struct sockaddr*)&client4,&len4)==-1)
perror("receive error");

for(k=8;k<strlen(buffer3);k++)
buffer31[l++]=buffer3[k];
buffer31[l]='\0';
strcpy(buffer3,"");
strcpy(buffer3,buffer31);
k=0;l=0;

/*displaying the received data*/
//printf("\nCLIENT %s : %s\n",inet_ntoa(client4.sin_addr),buffer3);
if(strstr(buffer3,"doc1") != NULL)
printf("\n\nPhase 2 : Directory Server has received a request from Client1");
else if(strstr(buffer3,"doc2") != NULL)
printf("\n\nPhase 2 : Directory Server has received a request from Client2");

/*Receiving the client request*/
len5=sizeof(client5);
if(recvfrom(sd1,buffer4,100,0,(struct sockaddr*)&client5,&len5)==-1)
perror("receive error");

for(k=8;k<strlen(buffer4);k++)
buffer41[l++]=buffer4[k];
buffer41[l]='\0';
strcpy(buffer4,"");
strcpy(buffer4,buffer41);
k=0;l=0;

/*displaying the received data*/
//printf("\nCLIENT %s : %s\n",inet_ntoa(client5.sin_addr),buffer4);
if(strstr(buffer4,"doc1") != NULL)
printf("\n\nPhase 2 : Directory Server has received a request from Client1");
else if(strstr(buffer4,"doc2") != NULL)
printf("\n\nPHASE 2 : Directory Server has received a request from Client2");

//puts(buffer3);
//puts(buffer4);
int cc,dd;
if(strcmp(buffer3,"doc1")==0 && strcmp(buffer4,"doc2")==0)
cc=1;
else if(strcmp(buffer3,"doc2")==0 && strcmp(buffer4,"doc1")==0)
cc=0;


/*Storing file access cost details in a structure object*/  

   FILE *ptr_file2;
   ptr_file2=fopen("topology.txt","r");
   if(!ptr_file2)
   {
   printf("\n\nError : Unable to open file topology.txt !!!!");
   return 1;
   }
   int n=0;  
   while(fgets(c,1000,ptr_file2)!=NULL)
      {
           //puts(c);
           sscanf(c,"%d %d %d",&c1[n].f[0],&c1[n].f[1],&c1[n].f[2]);
   //        printf("%d%d%d\n\n\n",c1[n].f[0],c1[n].f[1],c1[n].f[2]);
           n++;
       }
  c1count=n;
  fclose(ptr_file2);
 /*End of code to access cost details and storing in a apprpriate structure object*/ 


 
 flag1=flag2=0;
 counter1=counter2=0;
 z=0;
 strcpy(c,"");   
  

 /*Checking all those file servers which has the document buffer3 and storing their details in a structute object*/

  FILE *fp;
  fp=fopen("resource.txt","r");
  if(!fp)
  return 1;
    
   while(fgets(c,1000,fp)!=NULL)
   { 
      //printf("%s",c);
      if(strstr(c,buffer3)!=NULL)
      {       //puts(c);
            if(strstr(c,"File_Server1")!=NULL)
            {
 //               printf("1");
               if(strcmp(buffer3,"doc1")==0)
               {
                 flag1=1;
               strcpy(cr1[0].fileservername[z],"File_Server1");
               
               cr1[0].costs[z]=c1[0].f[0];
               }
                 
              else
               { 
                flag2=1;
                strcpy(cr1[1].fileservername[z],"File_Server1");
                cr1[1].costs[z]=c1[1].f[0];   


               }
             }
             else if(strstr(c,"File_Server2")!=NULL)
            {
 //printf("2");
                if(strcmp(buffer3,"doc1")==0)
               {
                flag1=1;
               strcpy(cr1[0].fileservername[z],"File_Server2");
               
               cr1[0].costs[z]=c1[0].f[1];
               }
                 
              else
               { 
                flag2=1;
                strcpy(cr1[1].fileservername[z],"File_Server2");
                cr1[1].costs[z]=c1[1].f[1];   


               }
             }
             else if(strstr(c,"File_Server3")!=NULL)
            {
 //printf("3");
               
               if(strcmp(buffer3,"doc1")==0)
               {
                flag1=1;
               strcpy(cr1[0].fileservername[z],"File_Server3");
               
               cr1[0].costs[z]=c1[0].f[2];
               }
                 
              else
               { 
                flag2=1;
                strcpy(cr1[1].fileservername[z],"File_Server3");
                cr1[1].costs[z]=c1[1].f[2];   


               }
             }
           
         //puts(cr1[0].fileservername[z]);
         //printf("1  %d\n\n\n\n",cr1[0].costs[z]);
         ++z;
      }
      
    }


/*Stores the count of number of entries present in the structure object*/
if(flag1 == 1)
cr1[0].count=z;

if(flag2 ==1)
cr1[1].count=z;


flag1=flag2=0;
z=0;
strcpy(c,"");



/*Checking all those file servers which has the document buffer4 and storing their details in a structute object*/
fp=fopen("resource.txt","r");
  if(!fp)
  return 1;
  
   while(fgets(c,1000,fp)!=NULL)
   { 
      //printf("%s",c);
      if(strstr(c,buffer4)!=NULL)
      {       //puts(c);
            if(strstr(c,"File_Server1")!=NULL)
            {
               if(strcmp(buffer4,"doc2")==0)
               {
                flag2=1;
               strcpy(cr1[1].fileservername[z],"File_Server1");
               
               cr1[1].costs[z]=c1[1].f[0];
               }
                 
              else
               { 
                flag1=1;
                strcpy(cr1[0].fileservername[z],"File_Server1");
                cr1[0].costs[z]=c1[0].f[0];   


               }
             }
             else if(strstr(c,"File_Server2")!=NULL)
            {
               if(strcmp(buffer4,"doc2")==0)
               {
               flag2=1;
               strcpy(cr1[1].fileservername[z],"File_Server2");
               
               cr1[1].costs[z]=c1[1].f[1];
               }
                 
              else
               { flag1=1;
                strcpy(cr1[0].fileservername[z],"File_Server2");
                cr1[0].costs[z]=c1[0].f[1];   


               }
             }
             else if(strstr(c,"File_Server3")!=NULL)
            {
              if(strcmp(buffer4,"doc2")==0)
               {flag2=1;

               strcpy(cr1[1].fileservername[z],"File_Server3");
               
               cr1[1].costs[z]=c1[1].f[2];
               }
                 
              else
               { flag1=1;
                strcpy(cr1[0].fileservername[z],"File_Server3");
                cr1[0].costs[z]=c1[0].f[2];   


               }    
             }
           
         //puts(cr1[1].fileservername[z]);
         //printf("2  %d\n\n\n",cr1[1].costs[z]);
         ++z;
      }
      
    }

/*End of code to obtain the file servers haveing the documents requested by client1 and client2*/





if(flag2==1)
cr1[1].count=z;

 if(flag1==1)
 cr1[0].count=z;
 
/*
int j;
 for(j=0;j<2;j++)
 {
 for(i=0;i<cr1[j].count;i++)
 {
 printf("%s:%d",cr1[j].fileservername[i],cr1[j].costs[i]);
 printf("\n\n");
 }
 //printf("\n\n\n\n\n\n end");
 }
*/

 int min[2];
 char minname[2][100];
 min[0]=cr1[0].costs[0];
 min[1]=cr1[1].costs[0];
 strcpy(minname[0],cr1[0].fileservername[0]);
 strcpy(minname[1],cr1[1].fileservername[0]);


 /*Determing the file server having the least cost of all file servers if there are multiple file servers from which client can receive the documents requested*/
 for(i=1;i<cr1[0].count;i++)
 if(cr1[0].costs[i] < min[0])
 {
 min[0]=cr1[0].costs[i];
 strcpy(minname[0],cr1[0].fileservername[i]);
 }

 for(i=1;i<cr1[1].count;i++)
 if(cr1[1].costs[i] < min[1])
 {
 min[1]=cr1[1].costs[i];
 strcpy(minname[1],cr1[1].fileservername[i]);
 }
  /*The minimum cost file servers to be contacted by clients along with their costs are stored in minname and cost array respectively*/




 /*Printing the file server names which has the least cost and their costs */
// printf("\n\nMin for Client1 to retrieve Doc1 = Server Name :%s and associated cost =%d",minname[0],min[0]);
 //printf("\n\n MIn for Client2 to retrieve to Doc2 = Server name :%s and its associated cost=%d",minname[1],min[1]);
 strcpy(c,"");



 char t1[20],t2[20];
 strcpy(t1,"");
 strcpy(t2,"");
 char filename[3][30];
 int portno[3];
 int minportno[2];
 i=0;


 FILE *fp1;
 fp1=fopen("directory.txt","r");
 if(!fp1 )
  {
 printf("Error : Sorry cannot open file directory.txt");
 return 1;
  }

 /*Code to read from directory.txt and store the files servernames and their respective ports into a memory location */
 while(fgets(c,1000,fp1)!=NULL)
      {
       sscanf(c,"%s %d",filename[i],&portno[i]);
       ++i;
      }
  fclose(fp1);
 
/*Code to obrain the port numbers of the file servers having the least cost , which each client has to contact*/
 for(i=0;i<3;i++)
 { 
// printf("\n\n%s%d",filename[i],portno[i]);
 if(strcmp(minname[0],filename[i])==0)
 minportno[0]=portno[i];
 
 if(strcmp(minname[1],filename[i])==0)
 minportno[1]=portno[i];
 }
 


 char tosend[2000]="";
 strcpy(tosend,"Client1 ");
 strcat(tosend,minname[0]);
 strcat(tosend," ");
 sprintf(t1,"%d",minportno[0]);
 strcat(tosend,t1);
 
 strcat(tosend,"\n"); 
 strcat(tosend,"Client2 ");
 strcat(tosend,minname[1]);
 strcat(tosend," "); 
 sprintf(t2,"%d",minportno[1]);
 strcat(tosend,t2);
 
 //puts(tosend);

/*Sending the details to the client*/
len4=sizeof(client4);
if(sendto(sd1,tosend,sizeof(tosend),0,(struct sockaddr*)&client4,len4)==-1)
perror("send error");
if(strcmp(buffer3,"doc1") == 0)
printf("\n\nPHASE 2 : File Server details has been sent to Client1");
else if(strcmp(buffer3,"doc2") == 0)
printf("\n\nPHASE 2 : File server details has been sent to Client2");



/*Sending the details to the client */
len5=sizeof(client5);
if(sendto(sd1,tosend,sizeof(tosend),0,(struct sockaddr*)&client5,len5)==-1)
perror("send error");
if(strcmp(buffer4,"doc1") == 0)
printf("\n\nPHASE 2 : File Server details has been sent to Client1");
else if(strcmp(buffer4,"doc2") == 0)
printf("\n\nPHASE 2 : File server details has been sent to Client2");

printf("\n\nPHASE 2 :End of phase2 for Directory Server");
printf("\n\n\n****************************PHASE 2 ENDS ********************************");

close(sd1);
/*END OF PHASE 2*/
return 0;
}
