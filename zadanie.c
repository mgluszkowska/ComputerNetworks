#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

char buf[BUFFER_SIZE];

int main(void) {
 char adres[14];
 struct sockaddr_in adr;
 unsigned int port;
 int gniazdo;
 in_addr_t siec;
 long indeks = 434690;
 long random;
 
 printf("Podaj adres IP odbiorcy: ");
 scanf("%s", adres);
 port = 14444;
 gniazdo = socket(PF_INET, SOCK_STREAM, 0);
 adr.sin_family = AF_INET;
 adr.sin_port = htons(port);
 adr.sin_addr.s_addr = inet_addr(adres);
 if (connect(gniazdo, (struct sockaddr*) &adr,
 sizeof(adr)) < 0) 
 {
 printf("Nawiazanie polaczenia nie powiodlo sie.\n");
 return 1;
 }
 printf("Polaczenie nawiazane.");
 indeks = htonl(indeks);

if (send(gniazdo, &indeks, sizeof(long), 0) 
 != sizeof(long)) {
 printf("send nie powiodl sie\n");
 //close(gniazdo);
 }

if (recv(gniazdo, &random, sizeof(long), 0) 
 != sizeof(long)) {
 printf("recv nie powiodl sie\n");
 //close(gniazdo);
 }

random = ntohl(random);
random = random + 1;
random = htonl(random);

if (send(gniazdo, &random, sizeof(long), 0) 
 != sizeof(long)) {
 printf("send nie powiodl sie\n");
 //close(gniazdo);
 }
 
 close(gniazdo);
 return 0;
}
