#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define IP_ADDRESS "192.168.1.182"
#define CONTROL_PORT 15020
#define VIDEO_PORT 8080

class WifibotClient
{
public:
	WifibotClient(void);
	~WifibotClient(void);
	bool ConnectToRobot(char* ip, int port);
	void avancer(int vitesse_gauche, int vitesse_droite);
	void reculer(int vitesse_gauche, int vitesse_droite);
	void tourner_gauche(int vitesse);
	void tourner_droite(int vitesse);
	void arret();
	short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);
}