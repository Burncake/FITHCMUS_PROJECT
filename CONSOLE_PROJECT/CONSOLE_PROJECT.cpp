#include "game.h"
#include "menu.h"
#include "common.h"
int main()
{
	//game::game_pvp();
	system("color F0");
	common::setUpConsole();
	menu::menuSelection();
	return 0;
}

