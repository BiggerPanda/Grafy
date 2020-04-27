#pragma once
#include "Graph.h"
#include<memory>


static int infinity = 10000000;// value used in bellman algorythm
static int negInfinity = -10000000;
class Graph_matrix :
	public Graph
{
	std::unique_ptr<std::unique_ptr<int[]>[]> matrix;
public:
	void fillGraph(const bool allowLoops) const override;
	void printGraph() const override;
	const int readFile(const std::string fileName) override;
	void createInput(const int startNode) const override;

	const int getValue(int one, int two) const { return this->matrix[one][two]; }
	
	Graph_matrix(int nodesAmount, double density);

	Graph_matrix() :Graph() {};
};

