#pragma once
#define MAP_WIDTH (100) //‰¡‚ÌÅ‘å–‡”
#define MAP_HEIGHT (40)  //c‚ÌÅ‘å–‡”
class CSV
{
public:
	int LoadCSV(int map[MAP_HEIGHT][MAP_WIDTH], const char* FilePath, int LoadStopNumber = -1);
private:
};

