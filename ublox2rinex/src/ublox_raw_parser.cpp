#include <ros/ros.h>
#include "ublox2rinex/RxmRAWX.h"
#include <stdio.h>
#include "../../src/ublox2rinex/include/ublox2rinex/rtklib.h"
void printspace(char* str, int n)
{
	for(int i = 0; i < n; i++)
		str[i] = ' ';
	str[n] = 0;
}

void epochCallback(const ublox2rinex::RxmRAWX::ConstPtr& msg)
{
    
    gtime_t obstime = gpst2time(msg->week, msg->rcvTOW);
    char timestr[1024];
    time2str2(obstime, timestr, 6);
    int datelen = strlen(timestr);
    int flagidx = 31 - datelen - 2;
    //ROS_INFO("%d", flagidx);
    int numidx = flagidx + 1;
    if((flagidx < 0) || (numidx >= 6)) return;
    char flagnumstr[8]={' ', ' ', ' ', ' ',' ',' ', ' ', ' '};
    
    flagnumstr[flagidx] = '0';
    //ROS_INFO("%s", flagnumstr);
    sprintf(flagnumstr + numidx, "%3d", msg->numMeas);
    //ROS_INFO("%s", flagnumstr);

    for(int i = 0; i < msg->numMeas; i++)
    {
		FILE* fp = fopen("rinex_CA_20190828184706.obs", "a");
		if(i == 0)
		{
			fprintf(fp, "> %s%s\n", timestr, flagnumstr);
		}
		char satstr[8];
		if(msg->meas[i].gnssId == 0)
			sprintf(satstr, "G%02d", msg->meas[i].svId);
		else if(msg->meas[i].gnssId == 2)
			sprintf(satstr, "E%02d", msg->meas[i].svId);
		else if(msg->meas[i].gnssId == 3)
			sprintf(satstr, "C%02d", msg->meas[i].svId);
		else if((msg->meas[i].gnssId == 6) && (msg->meas[i].svId < 100))
			sprintf(satstr, "R%02d", msg->meas[i].svId);
		else continue;
		fprintf(fp, "%s%14.3lf  %14.3lf3 %14.3lf  %14.3lf  \n", satstr, msg->meas[i].prMes, msg->meas[i].cpMes, msg->meas[i].doMes, (double)msg->meas[i].cno);
		fclose(fp);
	}
    //ROS_INFO("Subcribe Person Info: name:%d  age:%lf  sex:%lf", 
	//		 msg->meas[i].gnssId, msg->meas[i].prMes, msg->meas[i].doMes);
}

int main(int argc, char **argv)
{
    
    FILE* fp = fopen("rinex_CA_20190828184706.obs", "w");
    char strversion[64];
    printspace(strversion, 60);
    memcpy(strversion + 5, "3.03", 4);
    memcpy(strversion + 20, "OBSERVATION DATA", 16);
    memcpy(strversion + 40, "M: Mixed", 8);
    fprintf(fp, "%sRINEX VERSION / TYPE\n", strversion);
	char strsys[64];
	printspace(strsys, 60);
	strsys[0] = 'G';
	memcpy(strsys + 5, "4 C1C L1C D1C S1C", 17);
	fprintf(fp, "%sSYS / # / OBS TYPES\n", strsys);
	strsys[0] = 'R';
	fprintf(fp, "%sSYS / # / OBS TYPES\n", strsys);
	strsys[0] = 'E';
	fprintf(fp, "%sSYS / # / OBS TYPES\n", strsys);
	strsys[0] = 'J';
	fprintf(fp, "%sSYS / # / OBS TYPES\n", strsys);
	strsys[0] = 'C';
	memcpy(strsys + 5, "4 C2I L2I D2I S2I", 17);
	fprintf(fp, "%sSYS / # / OBS TYPES\n", strsys);
	char strtsys[64];
	printspace(strtsys, 60);
	memcpy(strtsys + 48, "GPS", 3);
	fprintf(fp, "%sTIME OF FIRST OBS\n", strtsys);
	char strblank[64];
	printspace(strblank, 60);
	fprintf(fp, "%sEND OF HEADER\n", strblank);
    fclose(fp);
    
    ros::init(argc, argv, "ublox_raw_parser");

    
    ros::NodeHandle n;

    
    ros::Subscriber person_info_sub = n.subscribe("/ublox_gps_node/rxmraw", 10, epochCallback);

    
    ros::spin();

    return 0;
}
