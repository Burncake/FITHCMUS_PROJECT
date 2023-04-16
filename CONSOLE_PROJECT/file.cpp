#include "file.h"

void file::saveScreen(game g)
{
	clearConsole();
	common::setColor(DarkCyan);
	printLogo();
	int left = 14, top = 12, width = 86, height = 13;
	common::setColor(Black);
	printRectangle(left, top, width, height);
	int posx = 22, posy = 15;
	printText("SAVE GAME", 53, 12);
	string location = loc;
	fstream manager(location + f_manager);
	if (!manager) {
		string error = "Error! Cannot find ";
		printText(error + f_manager + "!\n", posx, posy);
		return;
	}
	string name;
	common::showCursor(TRUE);
	do {
		printText("Enter save name: ", posx, posy);
		getline(cin, name);
		if (name.length() > 30) {
			printText("                                                                               ", posx, posy);
			printText("Error! File name length cannot exceed 30!", posx, posy + 1);
		}
	} while (name.length() > 30);
	common::showCursor(FALSE);
	printText("                                                                               ", posx, ++posy);
	posy++;
	bool flag = checkExisted(manager, name);
	if (flag) printText("Save existed. Override save? (Y/N)", posx, posy++);
	else {
		string temp = "File will be save as: \"" + name + "\"";
		printText(temp, posx, posy++);
		printText("Continue? (Y/N)", posx, posy++);
	}
	while (false == false) {
		common::gotoXY(posx, posy);
		int key = getInput();
		if (key == 9) {
			manager.seekg(0, ios::end);
			if (!flag) manager << name << endl;
			g.saveGame("saves/" + name + ".txt");
			printText("Saved successfully! Press ESC to get back to game.", posx, ++posy);
			break;
		}
		if (key == 10) {
			printText("Cancelled. Press ESC to get back to game.", posx, ++posy);
			break;
		}
	}
	common::gotoXY(posx, ++posy);
	while (getInput() != 6);
	manager.close();
}

bool file::loadScreen(game& g)
{
	clearConsole();
	common::setColor(DarkCyan);
	printLogo();
	int left = 14, top = 12, width = 86, height = 13;
	common::setColor(Black);
	printRectangle(left, top, width, height);
	int posx = 22, posy = 14;
	file temp;
	printText("LOAD GAME", 53, 12);
	printText("Press ESC to go back", 48, 28);
	if (temp.numOfSave == 0) {
		printText("NO SAVE FOUND", 51, 18);
		while (getInput() != 6);
		return false;
	}
	else {
		int pos[display]{ 0,1,2,3,4,5,6,7,8,9 };
		int select = 0;
		int key = 0;
		do {
			if (key == 1 || key == 2) {
				if (select > 0) {
					select--;
					if (select < pos[0]) fixArr(pos, false);
				}
			}
			if (key == 3 || key == 4) {
				if (select < maxSave && select < temp.numOfSave - 1) {
					select++;
					if (select > pos[display - 1]) fixArr(pos, true);
				}
			}
			if (key == 6) return false;
			temp.displaySave(posx, posy, pos, select);
			key = getInput();
			common::playSound(Move);
		} while (key != 5);
		for (int i = 0; i < display; i++) printText("                                ", posx, posy + i);
		printText("The following save will be load: \"" + temp.save[select] + "\"", posx, posy + 2);
		printText("Continue? (Y/N)", posx, posy + 4);
		printText("                    ", 48, 28);
		common::gotoXY(posx, posy + 5);
		while (key != 9 && key != 10) key = getInput();
		if (key == 9) {
			g.loadGame("saves/" + temp.save[select] + ".txt");
			return true;
		}
		printText("Cancelled. Press ESC to get back to menu.", posx, posy + 6);
		common::gotoXY(posx, posy + 7);
		while (getInput() != 6);
		return false;
	}
}

void file::fileRewind(fstream& in)
{
	in.clear();
	in.seekg(0);
}

bool file::checkExisted(fstream& in, string name)
{
	string temp;
	while (!in.eof()) {
		getline(in, temp);
		if (temp == name) {
			fileRewind(in);
			return true;
		}
	}
	fileRewind(in);
	return false;
}

void file::displaySave(int posx, int posy, int pos[], int select)
{
	for (int i = 0; i < display; i++) {
		if (save[pos[i]].length() == 0) break;
		printText("                              ", posx + 2, posy);
		if (pos[i] == select) {
			common::setColor(DarkRed);
			printText("> " + save[pos[i]], posx, posy++);
			common::setColor(Black);
		}
		else printText("  " + save[pos[i]], posx, posy++);
	}
}

void fixArr(int pos[], bool increase)
{
	if (pos[0] <= 0 && !increase) return;
	if (pos[display - 1] >= maxSave && increase) return;
	for (int i = 0; i < display; i++) {
		if (increase) pos[i]++;
		else pos[i]--;
	}
}

