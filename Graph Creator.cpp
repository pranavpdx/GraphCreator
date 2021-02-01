// Graph Creator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Creates a graph and prints out connections using an adjacency matrix
// Author: Pranav Sharma
// Date: 1/31/21

#include <iostream>
#include <vector>
#include <cstring>
#include "Vertex.h"
#include "Edge.h"
using namespace std; 
// functions used in the program
void addVertex(char v, vector<Vertex*> &vertices);
void addEdge(char start, char end, int weight, vector<Vertex*> &vertices, vector<Edge*> &edges);
void removeEdge(char start, char end, vector<Vertex*> &vertices, vector<Edge*> &edges);
void removeVertex(char v, vector<Vertex*> &vertices, vector<Edge*> &edges);
void printMatrix(vector<Vertex*> &vertices, vector<Edge*> &edges);
void shortestpath(char start, char end, vector<Vertex*> &vertices, vector<Edge*> &edges);




int main()
{
    // both vectors store information about the vertices and edges
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    bool playing = true;
   
    // main program begins
    cout << "This program creates a graph!!\n";
   // loops until user wants to quit
    while (playing) {
        cout << "You can either ADD, REMOVE, PRINT, FIND (the shortest path), or QUIT\n";
        char* input = new char();
        cin.getline(input, 80, '\n');
        // if user wants to add
        if (strcmp(input, "ADD") == 0) {
            // specifies whether a Vertex or edge is added
            cout << "Would you like to add a Vertex (V) or Edge (E)?\n";
            cin.getline(input, 80, '\n');
            // if Vertex
            if (strcmp(input, "V") == 0) {
                // asks for label
                cout << "Enter a label for the vertex: ";
                char v;
                cin >> v;
                cin.get();
                addVertex(v, vertices);
            }
            // if Edge
            else if (strcmp(input, "E") == 0) {
                // asks for labels
                cout << "Enter the label of the starting vertex: ";
                char v;
                cin >> v;
                cin.get();
                cout << "Enter the label of the ending vertex: ";
                char u;
                cin >> u;
                cin.get();
                cout << "Enter the weight of the edge: ";
                int weight;
                cin >> weight;
                cin.get();
                addEdge(v, u, weight, vertices, edges);
            }
            else {
                cout << "Sorry you didn't enter a proper command\n";
            }
        }
        // if user wants to remove 
        else if(strcmp(input, "REMOVE") == 0) {
            // specifies whether a Vertex or edge is removed
            cout << "Would you like to remove a Vertex (V) or Edge (E)?\n";
            cin.getline(input, 80, '\n');
            // if vertex
            if (strcmp(input, "V") == 0) {
                cout << "Enter the label of the vertex you would like to remove: ";
                char v;
                cin >> v;
                cin.get();
                removeVertex(v, vertices, edges);
            }
            // if edge
            else if (strcmp(input, "E") == 0) {
                cout << "Enter the label of the starting vertex: ";
                char v;
                cin >> v;
                cin.get();
                cout << "Enter the label of the ending vertex: ";
                char u;
                cin >> u;
                cin.get();
                removeEdge(v, u, vertices, edges);
            }
        }
        // if user wants to find the shortest path between two vertices
        else if(strcmp(input, "FIND") == 0) {
            // asks for labels
            cout << "Enter the label of the starting vertex: ";
            char v;
            cin >> v;
            cin.get();
            cout << "Enter the label of the ending vertex: ";
            char u;
            cin >> u;
            cin.get();
            shortestpath(v, u, vertices, edges);

        }
        // if user wants to print adjacency matrix
        else if (strcmp(input, "PRINT") == 0) {
            printMatrix(vertices, edges);
        }
        // if user wants to quit
        else if (strcmp(input, "QUIT") == 0) {
            playing = false;
        }
    }
}
// checks to see if the label already exists, if not, the label is added to the vector
void addVertex(char v, vector<Vertex*> &vertices) {
    Vertex* vertex = new Vertex(v);
    bool exists = false; 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == v) {
            exists = true; 
        }
    }

    if (exists == false) {
        vertices.push_back(vertex);
    }
    else {
        cout << "Sorry, this label already exists\n";
        delete vertex;
    }
}

// adds an edge connecting two vertices
void addEdge(char startL, char endL, int weight, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    Edge* edge = new Edge();
    Vertex* start = NULL;
    Vertex* end = NULL;
    bool exists = false;

    // finds starting and end vertices
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == startL) {
            start = *it;
        }

        if ((*it)->getLabel() == endL) {
            end = *it;
        }
    }

    // if start and end are the same node, error message is displayed
    if (start == end) {
        cout << "oops! You can't connect a node to itself\n";
        return;
    }

    // checks to see if the edge already exists
    for (vector<Edge*>::iterator it = (edges).begin(); it != (edges).end(); ++it) {
        if ((*it)->getStart() == start && (*it)->getEnd() == end) {
            exists = true; 
        }
    }

    // if vertices were found and the edge doesn;t already exist, the edge is created and added to the edges vector
    if (start != NULL && end != NULL && exists == false) {
        edge = new Edge();
        edge->setStart(start);
        edge->setEnd(end);
        edge->setWeight(weight);
        edges.push_back(edge);
    }
    // if edge already exists, error message is displayed
    else if (exists == false) {
        cout << "sorry, this edge already exists\n";
        delete edge;
    }
    // else one of the vertices cannot be found
    else {
        cout << "One of the vertices does not exist\n";
        delete edge;
    }
}

// removes and edge between two vertices
void removeEdge(char startL, char endL, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    Vertex* start = NULL;
    Vertex* end = NULL;
    bool exists = false;
    int count = 0;
    int index = -1;

    // finds the start and end vertices of edge 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == startL) {
            start = *it;
        }

        if ((*it)->getLabel() == endL) {
            end = *it;
        }
    }

    // if vertices can't be found, error message is displayed
    if (start == NULL && end == NULL) {
        cout << "Sorry, those vertices do not exist\n";
        return;
    }

    // finds the index of the edge, and checks to see if it exists
    for (vector<Edge*>::iterator it = (edges).begin(); it != (edges).end(); ++it) {
        if ((*it)->getStart() == start && (*it)->getEnd() == end) {
            index = count;
            exists = true;
        }
        count++;
    }

    // if the edge exists, its removed
    if (index != -1) {
        edges.erase(edges.begin() + index);
    }

    // if the edge does not exist, the error is displayed
    if (exists == false) {
        cout << "Sorry this edge does not exist\n";
        return;
    }
}

// removes vertex from the graph
void removeVertex(char v, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    bool hasEdge = false;
    int max = edges.size();
    int count = 0;
    Edge* arr[20];
    int index = 0;
    for (int i = 0; i < 20; i++) {
        arr[i] = NULL;
    }

    // looks through all the vertices to find the vertex to be deleted
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == v) {
            // once found checks to see if vertex has any edges connected to it
            for (vector<Edge*>::iterator it1 = (edges).begin(); it1 != (edges).end(); ++it1) {
                if ((*it1)->getStart() == *it || (*it1)->getEnd() == *it) {
                    hasEdge = true;
                }
            }
            // if true...
            if (hasEdge == true) {
                cout << "This Vertex is connected to an Edge\n";
                bool looped = false;
                    // loops through edges and finds the edges that needs to be deleted. Stores the edges in the array
                    for (vector<Edge*>::iterator it1 = (edges).begin(); it1 != (edges).end(); ++it1) {
                        if (count + 1 == max) {
                            looped = true;
                        }

                        if ((*it1)->getStart() == *it || (*it1)->getEnd() == *it) {
                            
                            arr[index] = *it1;
                            index++;
                            
                        }
                        count++;
                        if (looped == true) {
                            it1 = (edges).end() - 1;
                        }
                    }
                // deletes the edges attached to the vertex
                if (arr[0] != NULL)
                    for (int i = index; i > 0; i--) {
                        Edge* e = arr[i - 1];
                        removeEdge(e->getStart()->getLabel(), e->getEnd()->getLabel(), vertices, edges);
                    }
                    
            }
            // deletes the vertex
            vertices.erase(it);
            return;
        }
    }
}

void printMatrix(vector<Vertex*> &vertices, vector<Edge*> &edges) {
    cout << "\t";
    // prints the top layer with the vertices 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        cout << (*it)->getLabel() << "\t";
    }
    cout << endl;

    // prints the body
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        // prints the side layer with the vertices
        cout << (*it)->getLabel() << "\t";
        // checks edges to see if theres a conection between vertices, if there is, the weight is displayed
        for (vector<Vertex*>::iterator it1 = (vertices).begin(); it1 != (vertices).end(); ++it1) {
            bool connect = false;
            if (it == it1) {
                connect = true;
            }
            else {
                for (vector<Edge*>::iterator ite = (edges).begin(); ite != (edges).end(); ++ite) {
                    if ((*ite)->getStart() == *it && (*ite)->getEnd() == *it1) {
                        cout << (*ite)->getWeight();
                        connect = true;
                    }
                }
            }
            if (connect == false) {
               // cout << "0";
            }
            cout << "\t";

        }
        // new line is started
        cout << endl;
    }
}

// finds the shortest path between any two vertices, ideas taken from omar
void shortestpath(char startL, char endL, vector<Vertex*> &vertices, vector<Edge*> &edges) {
    Vertex* start = NULL;
    Vertex* end = NULL;

    // finds the vertices of the start and end labels 
    for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
        if ((*it)->getLabel() == startL) {
            start = *it;
        }

        if ((*it)->getLabel() == endL) {
            end = *it;
        }
    }

    // if vertices cannot be found or they are the same vertex, error is displayed
    if (start == NULL || end == NULL || start == end) {
        cout << "Sorry! One of the vertices you enteres does not exist or you've entered the same vertex for start and end\n";
        return;
    }

    // if there are any edges in the graph, then the program finds the shortest path 
    if (edges.empty() == false) {
        // visits every unvisited vertex and updates distance form current vertex. After moving through vertex conenction, it current gets replaced by the next closest vertex. This porcess repeats until all the vertex are visited
        vector<Vertex*> visited;
        vector<Vertex*> unvisited = vertices;
        Vertex* current = NULL;

        start->setDistance(0);
        current = start;


        while (unvisited.empty() == false) {
            int distance = current->getDistance();
            for (vector<Vertex*>::iterator it = (unvisited).begin(); it != (unvisited).end(); ++it) {
                if ((*it)->getLabel() != current->getLabel()) {
                    for (vector<Edge*>::iterator ite = (edges).begin(); ite != (edges).end(); ++ite) {
                        Edge* e = *ite;
                        if (e->getStart()->getLabel() == current->getLabel() && e->getEnd()->getLabel() == (*it)->getLabel()) {
                            if ((*it)->getDistance() == -1 || (*it)->getDistance() > distance + e->getWeight()) {
                                (*it)->setDistance(distance + e->getWeight());
                            }
                        }
                    }
                }
            }
            Vertex* curr = NULL;

            //erases current vertex from the vector of unvisted vertexs
            for (vector<Vertex*>::iterator it = (unvisited).begin(); it != (unvisited).end(); ++it) {
                if ((*it)->getLabel() == current->getLabel()) {
                    unvisited.erase(it);
                    visited.push_back(current);
                    break;
                }
            }

            // updates current vertex
            for (vector<Vertex*>::iterator it = (unvisited).begin(); it != (unvisited).end(); ++it) {
                if (curr == NULL) {
                    curr = *it;
                }

                if (curr->getDistance() > (*it)->getDistance() && (*it)->getDistance() > 0) {
                    curr = *it;
                }
                current = curr;
            }

            // finds ending vertex and displayes the shortes distance to the vertex
            for (vector<Vertex*>::iterator it = (visited).begin(); it != (visited).end(); ++it) {
                if ((*it)->getLabel() == endL) {
                    if ((*it)->getDistance() > 0) {
                        cout << "The shortest distance between " << startL << " and " << endL << " is: " << (*it)->getDistance() << endl;
                        return;//look
                    }
                    else if ((*it)->getDistance() == -1) {
                        cout << "it looks like the vertices are not connected :/\n";
                    }
                }
            }
        }

    }
    // if there are no edges
    else if (edges.empty()) {
        cout << "There are no edges\n";
    }
    else {
        // if vertices cannot be found
        cout << "One of the vertices don't exist\n";
        // resets variables
        for (vector<Vertex*>::iterator it = (vertices).begin(); it != (vertices).end(); ++it) {
            (*it)->setDistance(-1);
        }
        start = NULL;
        end = NULL;
    }

}
