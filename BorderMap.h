#ifndef BorderMap_H
#define BorderMap_H

class Point;

class BorderMap
{
public:
	//generate a 10x20 map by default with border #
	BorderMap();
	//generate a map with corresponding width and height
	BorderMap(int width, int height);
	~BorderMap();
	//1: set successfully
	//0: border invalid set
	int setElement(int x, int y,char e);
	int setElement(Point &point, char e);
	//return the total number of element that is been set
	int setElements(Point points[],int size, char e);

	//return the element at the index location
	char getElement(int x, int y) const;

	//draw the map with element in it
	void draw();
	
	void getInfo();
	int get_width();
	int get_height();
private:
	int _width = 10;
	int _height = 20;
	char** _maps;
	char borderElement = '#';
};

#endif
