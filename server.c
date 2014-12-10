#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>


void error (char *msg)
{
    perror(msg);
    exit(0);
}



int execCommand(char* command){

    int i=0;
    int words=0;
    int subcommand[20];
    int didWhile=0;
    int word=0;
    //command analysis
    //find end position

    char delimiter[2]=",";
    char *token;

    token=strtok(command,delimiter);

    while (token!=NULL) {
         didWhile=1;
         subcommand[words]=strtol(token,NULL,16);//convert from ascii hex to int
         words++;
         token = strtok(NULL,delimiter);
    }
    printf("WORDS= %d => ",words);
    for (word=0;word<words;word++){
       printf("%0x,",subcommand[word]);
    }
    printf("\n\n");

}


int main (int argc, char *argv[])
{

    printf("\nCIS CNA-1 TCP/IP >> 2 X Serial\n");

    //Variable declarations
    //fd= file descriptors
    int sockfd, portno, readStatus, writeStatus;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
	if (argc<3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if (sockfd<0){
         error("ERROR opening socket");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    }
    printf("Sending permission string");
    bzero(buffer,256);
    char permission[]="0b,90,01,00\n";
    int i;
    for (i=0;i<strlen(permission);i++){
        buffer[i]=permission[i];
    }
    //fgets(buffer,255,stdin);
    //writeStatus= write (sockfd,buffer,strlen(buffer));
    if (writeStatus<0){
      //  error("ERROR writing to socket");
    }
    bzero(buffer,256);
    char command[30];
    bzero(command,31);
    int bytePosition=0,byte;
    i=0;
while (1){
    readStatus = read(sockfd,buffer,1);
    if (readStatus<0) {
        error("ERROR reading from socket");
    }
    if (i<30){
        command[i]=buffer[0];
        if (command[i]==10){ //decimal 10 is new line
            execCommand(command);
            bzero(buffer,256);
            bzero(command,31);
            i=0;
        }else{
            i++;
        }
    }else {
        printf("COMMAND OVERFLOW\n");
        bzero(buffer,256);
        bzero(command,31);
        i=0;
    }
    readStatus=0;

}
    return 0;
}
