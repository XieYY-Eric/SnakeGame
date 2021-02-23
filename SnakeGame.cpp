#include "SnakeGame.h"
#include "BorderMap.h"
#include "point.h"
#include "list.h"
#include<windows.h>
#include<iostream>
#include<random>
#include<conio.h>
#include<string>
#include<fstream>

SnakeGame::SnakeGame()
{
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    message = "Press to go";
    maps = new BorderMap(colomn, row);
    headx = row / 2, heady = colomn / 2;
    dir = Dir::STOP;
    Point head(headx, heady);
    body.push_rear(head);
    maps->setElement(headx, heady, 'O');
    fruitx = rand() % (colomn - 2) + 1;
    fruity = rand() % (row - 2) + 1;
    maps->setElement(fruitx, fruity, 'E');
    speed = 200;
    goal = 300;
}

SnakeGame::SnakeGame(std::string filename)
{
    std::ifstream fin(filename);
    if (fin.fail()) {
        std::cerr << filename << " couldn't be located!";
		std::cin.get();
        exit(1);
    }
    //get setting from the setting file
    std::string field, value,line;
    while (std::getline(fin, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), [](char c) {return c == ' ' || c == '\n'; }), line.end());
        
        int parseSign = line.find('=');
        field = line.substr(0, parseSign);
        value = line.substr(parseSign+1);
        if (field == "width") {
            colomn = std::stoi(value);
        }
        else if (field == "heigth") {
            row = std::stoi(value);
        }
        else if (field == "score") {
            goal = std::stoi(value);
        }
        else if (field == "difficulty") {
            int difficulty = std::stoi(value);
            speed = (difficulty <= 3) ? difficulty * 100 : 300;
        }
    }
    //create our map based on our pre-define value and handle
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    
    maps = new BorderMap(colomn, row);
    message = "Press to go";
    headx = row / 2, heady = colomn / 2;
    dir = Dir::STOP;
    Point head(headx, heady);
    body.push_rear(head);
    maps->setElement(headx, heady, 'O');
    fruitx = rand() % (colomn - 2) + 1;
    fruity = rand() % (row - 2) + 1;
    maps->setElement(fruitx, fruity, 'E');

}

void SnakeGame::printMap()
{
    system("cls");
    this->maps->draw();
}


void SnakeGame::input() {
    if (_kbhit()) {
        message = "begin!";
        switch (_getch())
        {
        case 'w':
            dir = (dir != Dir::DOWN)?Dir::UP : dir;
            message = "moving up";
            break;
        case 'a':
            dir = (dir != Dir::RIGHT) ? Dir::LEFT : dir;
            message = "moving left";
            break;
        case 's':
            dir = (dir != Dir::UP) ? Dir::DOWN : dir;
            message = "moving down";
            break;
        case 'd':
            dir = (dir != Dir::LEFT) ? Dir::RIGHT : dir;
            message = "moving right";
            break;
        case 'x':
            dir = Dir::STOP;
            message = "Exit The Game";
            gameover = true;
            break;
        }
    }
}

void SnakeGame::logic()
{
    int nextx = headx;
    int nexty = heady;
    Point next(nextx, nexty);
    switch (dir) {
    case Dir::LEFT:
        nextx -= 1;
        break;
    case Dir::RIGHT:
        nextx += 1;
        break;
    case Dir::DOWN:
        nexty += 1;
        break;
    case Dir::UP:
        nexty -= 1;
        break;
    case Dir::STOP:
        break;
    }
    if (dir == Dir::STOP) {
        return;
    }
    //hit bound
    if (nextx == 0 || nextx == colomn - 1 || nexty == 0 || nexty == row - 1) {
        dir = Dir::STOP;
        gameover = true;
        message = "I hit the bound!!";
    }

    //eat itself
    if (dir != Dir::STOP && maps->getElement(nextx, nexty) == 'o') {
        message = "Ouch, I eat myself";
        gameover = true;
    }

    if (gameover) {
        return;
    }
    //eat the fruits
    bool increase = false;
    if (nextx == fruitx && nexty == fruity) {
        score += 10;
        maps->setElement(fruitx, fruity, ' ');
        fruitx = rand() % (colomn - 2) + 1;
        fruity = rand() % (row - 2) + 1;
        increase = true;
        //each 50 points ,increase 10% speed;
        if (score != 0 && score % 50 == 0) {
            speed = (int)((speed>100)? speed * 0.9 : speed);
        }
    }
    //check win condition
    if (score == goal){
        message = "Congradulation, you won the game";
        gameover = true;
    }
    //update snake
    Point curPo(nextx, nexty);
    body.push_front(curPo);
    Point tailPo = body.rear();
    if (!increase) {
        body.pop_rear();
    }
    //update the map
    this->maps->setElement(tailPo.x(), tailPo.y(), ' ');
    //get rid of the new tail
    drawAtPostion(tailPo.x(), tailPo.y(), ' '); 

    maps->setElement(body.front().x(), body.front().y(), 'O');
    drawAtPostion(body.front().x(), body.front().y(), 'O');
    if (body.size() > 1) {
        for (int i=1; i<body.size(); ++i) {
            this->maps->setElement(body.get(i).x(),body.get(i).y(), 'o');
            //draw the body
            drawAtPostion(body.get(i).x(), body.get(i).y(), 'o');
        }
        
    }
    //create new fruits
    if (maps->getElement(fruitx, fruity) == ' ') {
        maps->setElement(fruitx, fruity, 'E');
        drawAtPostion(fruitx, fruity, 'E');
    }
    headx = body.front().x();
    heady = body.front().y();
}

void SnakeGame::say() {
    setCursorPosition(0, row);
    std::cout << "                                        ";
    std::cout << "\n                                        ";
    std::cout << "\n                                        ";
    std::cout << "\n                                        ";
    setCursorPosition(0, row);
    std::cout << "Current Score: " << score << std::endl;
    std::cout << "Result: " << message << std::endl;
    std::cout << "Speed: " << speed;
   /* std::cout << "\nsnakePostion: (" << headx << "," << heady << ")";
    std::cout << "\nfruitsPostion: (" << fruitx << "," << fruity << ")";*/
}

void SnakeGame::game()
{
    printMap();
    while (!gameover) {
        //printMap();
        input();
        logic();
        say();
        Sleep(speed);
    }
}

void SnakeGame::setCursorPosition(int x, int y)
{
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hout, coord);
}

void SnakeGame::drawAtPostion(int x, int y, char c)
{
    setCursorPosition(x, y);
    std::cout << c;
}

