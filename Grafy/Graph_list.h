#pragma once
#include "Graph.h"
static int regulatingValue = 2; // value that helps to change value next to rand

class Graph_list :
	public Graph
{
private:
	Edge* in_Edge;
public:
	void fillGraph(const bool allowLoops) const override;
	void printGraph() const override;
	const int readFile(const std::string fileName)  override;
	void createInput(const int startNode) const override;
	const Edge* edgeGetter() { return this->in_Edge; }
	void addEdge(int nodeStart,int nodeEnd,int value,int whereflag) const ;
	bool isExisting(int nodeStart, int nodeEnd) const;
	~Graph_list() { delete[] in_Edge; }
	Graph_list() :Graph() {};
	Graph_list(int in_amountOfNodes, int in_density) : Graph(in_amountOfNodes, in_density* in_amountOfNodes* (in_amountOfNodes - 1), in_density), in_Edge(new Edge[in_density * in_amountOfNodes * (in_amountOfNodes - 1)]) {}
};

