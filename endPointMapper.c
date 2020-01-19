#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
struct Smap{
	char guid[9];
	char address[4];
};

static void runcomm(const char *address, const char *command) {
char *arguments[] = {"/home/pi/scripts/lockercall", "50", (char *) command, NULL};
execvp(arguments[0], arguments);
}

int main(int argc,char *argv[])
{
openlog(NULL, 0 , LOG_USER);
struct Smap rdata;
syslog(LOG_INFO, "Opening mapper file. \n");
FILE* input;
input = fopen("data.bin", "rb");

volatile char compare[8];
volatile uint8_t found = 0;
while(fread(&rdata, sizeof(struct Smap), 1, input))
{
	printf("Command: %s \r\nAddress: %s \n", rdata.guid,rdata.address);
	if(strcmp(argv[1],rdata.guid)==0)
	{
		syslog(LOG_NOTICE, "Found valid guid. \n");
		found = 1;
		runcomm(rdata.address, argv[2]);
	}
	else
	{
		syslog(LOG_INFO, "Guid doesnt match. \n");
	}
}
fclose(input);
if(!found)
{
syslog(LOG_ERR, "Iterated through list but could not find any matching ID's. \n");
}
closelog();
return 0;
}
