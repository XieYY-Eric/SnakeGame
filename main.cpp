#include<iostream>
#include"SnakeGame.h"


using namespace std;
int main() {
	SnakeGame game("setting.ini");
	game.game();
	std::cin.get();
}

