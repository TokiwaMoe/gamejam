#pragma once
#define MAP_WIDTH (100) //���̍ő喇��
#define MAP_HEIGHT (40)  //�c�̍ő喇��
class CSV
{
public:
	int LoadCSV(int map[MAP_HEIGHT][MAP_WIDTH], const char* FilePath, int LoadStopNumber = -1);
private:
};

