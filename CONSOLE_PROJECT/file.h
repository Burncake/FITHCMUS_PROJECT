#pragma once
#include "menu.h"
#define f_manager "f_manager.txt"
#define maxSave 30
#define display 10

class file
{
	file() {
		string location = loc;
		ifstream in(location + f_manager);
		if (!in) {
			in.close();
			return;
		}
		while (!in.eof()) {
			getline(in, save[numOfSave++]);
		}
		in.close();
		numOfSave--;
	}
public:
	string save[maxSave];
	int numOfSave = 0;
	static void saveScreen(game g);
	static bool loadScreen(game& g);
	static void fileRewind(fstream& in);
	static bool checkExisted(fstream& in, string name);
	void displaySave(int posx, int posy, int pos[], int select);
};

void fixArr(int pos[], bool increase);