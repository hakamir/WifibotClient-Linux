#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



class WifibotClient
{
public:
	WifibotClient(void);
	~WifibotClient(void);
	bool ConnectToRobot(char* ip, int port);
	void SendCommand(int left_speed, int right_speed, unsigned char flags);
	void avancer(int vitesse_gauche, int vitesse_droite);
	void reculer(int vitesse_gauche, int vitesse_droite);
	void tourner_gauche(int vitesse);
	void tourner_droite(int vitesse);
	void arret();
	short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);

private:
	int sockfd, port, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
};
