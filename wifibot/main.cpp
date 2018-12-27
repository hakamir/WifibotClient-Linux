#include "client.h"


WifibotClient robot;

void main(void)
{
	err = robot.ConnectToRobot(IP_ADDRESS, CONTROL_PORT);
	if (err == true){
		printf("Connection established.");
	}
	else{
		printf("ERROR Connection failed.");
	}
}