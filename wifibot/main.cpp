#include "WifibotClient.h"

#include <ncurses.h>
#include <unistd.h>

#define IP_ADDRESS "192.168.1.182"
#define CONTROL_PORT 15020
#define VIDEO_PORT 8080

WifibotClient robot;

int kbhit(void) {
	int ch = getch();

	if (ch != ERR) {
		ungetch(ch);
		return 1;
	} else {
		return 0;
	}
}

int main(void)
{
	//initscr();
	//cbreak();
	//noecho();
	//nodelay(stdscr, TRUE);

	bool err;
	err = robot.ConnectToRobot((char*)IP_ADDRESS, CONTROL_PORT);
	if (err == true){
		printf("Connection established.\n");
	}
	else{
		printf("ERROR Connection failed.\n");
	}
	while(1){
		robot.avancer(100,100);
		usleep(1000000);
		robot.reculer(100,100);
		usleep(1000000);
	}

	/*while(1)
	{
		if(kbhit()) {
			switch(getch()){
				case 122: // z : Move forward
					robot.avancer(100,100);
					printf("Forward");
					break;
				case 115: // s : Move backward
					robot.reculer(100,100);
					printf("Backward");
					break;
				case 113: // q : Rotation to the left
					robot.tourner_gauche(100);
					printf("Left");
					break;
				case 100: // d : Rotation to the right
					robot.tourner_droite(100);
					printf("Right");
					break;
				default:
					break;
				}
				flushinp();
		}else{
			robot.arret();
		}
	}*/
}
