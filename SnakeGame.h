#ifndef SnakeGame_H
#define SnakeGame_H

#include<windows.h>
#include<iostream>
#include"list.h"
#include"point.h"

class BorderMap;
class Point;

class SnakeGame {
public:
    SnakeGame();
    SnakeGame(std::string filename);
    void printMap();
    void say();
    void game();
    
private:
    void input();
    void logic();
    void setCursorPosition(int x, int y);
    void drawAtPostion(int x, int y, char c);

    enum class Dir { LEFT = 0, UP, RIGHT, DOWN, STOP }dir;
    BorderMap* maps;
    int headx, heady;
    int speed;
    List<Point> body;
    std::string message;
    int fruitx, fruity;
    int score = 0;
    int goal;
    bool gameover = false;
    int row = 25;
    int colomn = 40;
    HANDLE hout;
};

#endif // !SnakeGame_H




