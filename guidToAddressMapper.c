#include <iostream>
#include <stdio.h>
#include <syslog.h>
struct Smap{
	char guid[9];
	char address[4];
};

int main()
{
	openlog(NULL, 0, LOG_USER);
	syslog(LOG_WARNING, "Creating new mapping structure! \n");
	struct Smap data1 = { "7geohYLV", "50" };
	struct Smap data2 = { "aaa", "51" };
	struct Smap data3 = { "bbb", "52" };
	FILE* output;
	output = fopen("data.bin", "wb");
	fwrite(&data1, sizeof(struct Smap), 1, output);
	fwrite(&data2, sizeof(struct Smap), 1, output);
	fwrite(&data3, sizeof(struct Smap), 1, output);
	fclose(output);
	closelog();
}
