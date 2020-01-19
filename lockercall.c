#include <iostream>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <cstring>
#include <syslog.h>
#include <cstddef>
#include <syslog.h>

#define TIMEOUT 20
#define DBG 1
#define CALL_GUID 0xA1
#define CALL_CLAIM 0xA2
#define CALL_ENDCLAIM 0xA3
#define CALL_UNLOCK 0xA4

volatile uint8_t device_id;
int main (int argc, char *argv[])
{
	openlog(NULL, 0, LOG_USER);
	syslog(LOG_NOTICE, "%s called with %d arguments\n", argv[0], argc);
	for(int arguments=1;arguments<argc;arguments++)
	{
		syslog(LOG_NOTICE, "Argument %s \n", argv[arguments]);
	}
	if (argc < 3 || argc > 3)
	{
		syslog(LOG_ERR, "Incorrect amount of arguments");
		return 0;
	}
	else
	{
		syslog(LOG_INFO, "Checking address. \n");
		long inputaddress = strtol(argv[1], NULL, 10);
		if(inputaddress < 0 || inputaddress > 255)
		{
			syslog(LOG_ERR, "Address unavailable");
			return -1;
		}
		device_id = inputaddress;
		//
		syslog(LOG_NOTICE, "I2C init. \n");
		if(!strcmp(argv[2], "claim"))
		{
                        int fd = wiringPiI2CSetup(device_id);
			syslog(LOG_NOTICE, "Starting claim call. \n");
			int received_data = 0xFF;
			uint8_t data_to_send = CALL_CLAIM;
			int count = 0;
			while(received_data != 0xAC)
			{
				wiringPiI2CWrite(fd, data_to_send);
				sleep(0.1);
				received_data = wiringPiI2CRead(fd);
			        syslog(LOG_INFO, "Retrying claim call. \n");
				count++;
				if(count > TIMEOUT) {syslog(LOG_WARNING,"Claim call took too many tries. \n"); break;}
			}
		}
		else if(!strcmp(argv[2], "endclaim"))
		{
			int fd = wiringPiI2CSetup(device_id);
			syslog(LOG_NOTICE, "Starting endclaim call. \n");
			int received_data = 0xFF;
			uint8_t data_to_send = CALL_ENDCLAIM;
			int count = 0;
			while(received_data != 0xAC)
			{
				wiringPiI2CWrite(fd, data_to_send);
				sleep(0.1);
				received_data = wiringPiI2CRead(fd);
				syslog(LOG_INFO, "Retrying endclaim call. \n");
				count++;
				if(count > TIMEOUT) { syslog(LOG_WARNING, "Endclaim call took too many tries. \n"); break;}
			}
		}
		else if(!strcmp(argv[2], "unlock"))
		{
			int fd = wiringPiI2CSetup(device_id);
			syslog(LOG_NOTICE, "Starting unlock call. \n");
			int received_data = 0xFF;
			uint8_t data_to_send = CALL_UNLOCK;
			int count = 0;
			while(received_data != 0xAC)
			{
				wiringPiI2CWrite(fd, data_to_send);
				sleep(0.1);
				received_data = wiringPiI2CRead(fd);
				syslog(LOG_INFO, "Retrying unlock call. \n");
				count++;
				if(count > TIMEOUT) { syslog(LOG_WARNING, "Unlock call took too many tries. \n"); break;}
			}
		}

	}
	syslog(LOG_NOTICE, "Script finished. \n");
	closelog();
	return 0;
}
