#include "client.h"

#define udpnew
#define MIN_RANGE_CAPT 120
#define MAX_RANGE_CAPT 180

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

WifibotClient::WifibotClient(void)
{
	int sockfd, port;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
}

WifibotClient::~WifibotClient(void)
{
}

bool WifibotClient::ConnectToRobot(char* ip, int port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
	{
        error("ERROR opening socket");
		return 0;
	}
    server = gethostbyname(ip);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        return 0;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(port);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
        error("ERROR connecting");
		return 0;
	}
	return 1;
}

void WifibotClient::SendCommand(int left_speed, int right_speed, unsigned char flags)
{
	unsigned char sbuf[30];
	sbuf[0] = 255;
	sbuf[1] = 0x07;
	sbuf[2] = left_speed;
	sbuf[3] = 0;
	sbuf[4] = right_speed;
	sbuf[5] = 0;
	sbuf[6] = flags;
	short mycrcsend = Crc16((unsigned char*)sbuf + 1, 6);
	sbuf[7] = (unsigned)mycrcsend;
	sbuf[8] = (unsigned)(mycrcsend >> 8);
	if (!socketnotok) send(socktcp, (char*)sbuf, 9, 0);
	odometry = true;
}

short WifibotClient::Crc16(unsigned char *Adresse_tab, unsigned char Taille_max)
{
	unsigned int Crc = 0xFFFF;
	unsigned int Polynome = 0xA001;
	unsigned int CptOctet = 0;
	unsigned int CptBit = 0;
	unsigned int Parity = 0;

	Crc = 0xFFFF;
	Polynome = 0xA001;
	for (CptOctet = 0; CptOctet < Taille_max; CptOctet++)
	{
		Crc ^= *(Adresse_tab + CptOctet);

		for (CptBit = 0; CptBit <= 7; CptBit++)
		{
			Parity = Crc;
			Crc >>= 1;
			if (Parity % 2 == true) Crc ^= Polynome;
		}
	}
	return(Crc);
}

void WifibotClient::avancer(int vitesse_gauche, int vitesse_droite)
{
	unsigned char flags = 128 + 32 + 16 + 64 + 1;
	SendCommand(vitesse_gauche, vitesse_droite, flags);
}

void WifibotClient::reculer(int vitesse_gauche, int vitesse_droite)
{
	unsigned char flags = 128 + 32 + 1;
	SendCommand(vitesse_gauche, vitesse_droite, flags);
}

void WifibotClient::tourner_gauche(int vitesse)
{
	unsigned char flags = 128 + 32 + 16 + 1;
	SendCommand(vitesse, vitesse, flags);
}

void WifibotClient::tourner_droite(int vitesse)
{
	unsigned char flags = 128 + 32 + 64 + 1;
	SendCommand(vitesse, vitesse, flags);
}

void WifibotClient::arret()
{
	unsigned char flags = 1;
	SendCommand(0, 0, flags);
}

