#pragma once
class Vertex
{
public: 
	char label; 
	int distance;
	Vertex(char v);
	//~Vertex();
	char getLabel();
	void setLabel(char v);
	int getDistance();
	void setDistance(int d);
};

