#include "Vertex.h"


Vertex::Vertex(char v) {
	label = v; 
	distance = -1;
}

char Vertex::getLabel() {
	return label;
}

void Vertex::setLabel(char inLabel) {
	label = inLabel;
}

int Vertex::getDistance() {
	return distance;
}

void Vertex::setDistance(int d) {
	distance = d;
}