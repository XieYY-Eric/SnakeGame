#include "BorderMap.h"
#include "C:\Users\xyy14\OneDrive\Desktop\Study\FALL 2020\CS 20A\Project\FourthProject\point.h"
#include<iostream>
BorderMap::BorderMap()
{
	_maps = new char* [_height];
	for (int i = 0; i < _height; i++) {
		_maps[i] = new char[_width];
	}

	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			if (i == 0 || i == _height - 1) {
				_maps[i][j] = borderElement;
			}else if (j == 0 || j == _width - 1) {
				_maps[i][j] = borderElement;
			}
			else {
				_maps[i][j] = ' ';
			}
		}
	}
}

BorderMap::BorderMap(int width, int height)
{
	_width = width;
	_height = height;
	_maps = new char* [_height];
	for (int i = 0; i < _height; i++) {
		_maps[i] = new char[_width];
	}
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			if (i == 0 || i == _height - 1) {
				_maps[i][j] = borderElement;
			}
			else if (j == 0 || j == _width - 1) {
				_maps[i][j] = borderElement;
			}
			else {
				_maps[i][j] = ' ';
			}
		}
	}
}

BorderMap::~BorderMap()
{
	for (int i = 0; i < _height; i++) {
		delete [] _maps[i];
	}
	delete[] _maps;
}

int BorderMap::setElement(int x, int y, char e)
{
	if (x == 0 || x == _width - 1 || y == 0 || y == _height - 1) {
		return 0;
	}
	_maps[y][x] = e;
	return 1;
}

int BorderMap::setElement(Point &point, char e)
{
	int x = point.x();
	int y = point.y();
	if (x == 0 || x == _width - 1 || y == 0 || y == _height - 1) {
		return 0;
	}
	_maps[y][x] = e;
	return 1;
}

int BorderMap::setElements(Point points[], int size, char e)
{
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (setElement(points[i], e)) {
			count++;
		}
	}
	return count;
}

char BorderMap::getElement(int x, int y) const
{
	if (_maps == nullptr || x < 0 || x > _width - 1 || y < 0 || y > _height - 1) {
		return '?';
	}
	return _maps[y][x];
}

void BorderMap::draw()
{
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			std::cout << _maps[i][j];
		}
		std::cout << std::endl;
	}
}

void BorderMap::getInfo()
{
	std::cout << "Border Width: " << _width << "\nBorder Height: " << _height << std::endl;
}

int BorderMap::get_width()
{
	return _width;
}

int BorderMap::get_height()
{
	return _height;
}
