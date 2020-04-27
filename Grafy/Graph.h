#pragma once
#include "KrawêdŸ.h"
#include "Wierzcho³ek.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

#include <ctime>
#include <string>


class Graph
{
protected:
	int main_amountOfNodes;
	int main_amountOfEges;
	double main_density;
public:
	const int nodesGetter()
	{
		return this->main_amountOfNodes;
	}
	const int edgesGetter() 
	{
		return this->main_amountOfEges;
	}

	virtual void fillGraph(const bool allowLoops) const =0;
	virtual void printGraph() const =0;
	virtual const int readFile(const std::string fileName)  = 0;
	virtual void createInput(const int startNode) const =0;

	virtual ~Graph() {};
	Graph(int in_amountOfNodes, int in_amountOfEdges, int in_density) : main_amountOfNodes(in_amountOfNodes), main_amountOfEges(in_amountOfEdges), main_density(in_density) {};
	Graph() {};

};

