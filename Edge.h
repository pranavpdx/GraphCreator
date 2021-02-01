#pragma once
#include "Vertex.h"
class Edge
{
public: 
	Vertex* start;
	Vertex* end;
	int weight; 
	Edge();
	~Edge();
	Vertex* getStart();
	Vertex* getEnd();
	void setStart(Vertex* s);
	void setEnd(Vertex* s);
	void setWeight(int w);
	int getWeight();

};

