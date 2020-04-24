#include "Graph_list.h"


void Graph_list::fillGraph(const bool allowLoops) const
{
	if (this->main_density == 1) 
	{
		int flag = 0;
		for(int iterNodeStart=0; iterNodeStart<this->main_amountOfNodes;iterNodeStart++)
		{
			for (int iterNodeEnd=0;iterNodeEnd<this->main_amountOfNodes;iterNodeEnd++) 
			{
				if (iterNodeStart != iterNodeEnd)
				{	
					int valueOfConnection = rand() % 50 - regulatingValue;
					while (valueOfConnection==0)
					{
						valueOfConnection = rand() % 50 - regulatingValue;
					}
					addEdge(iterNodeStart, iterNodeEnd, valueOfConnection, flag);
					flag++;
				}

			}
		}
	}
	else
	{
		for (int iterEdges = 0; iterEdges < this->main_amountOfEges; iterEdges++) 
		{
			int randStartNode = rand() % this->main_amountOfNodes;
			int randEndNode = rand() % this->main_amountOfNodes;
			if(!this->isExisting(randStartNode,randEndNode))
			{
				int valueOfConnection = rand() % 50 - regulatingValue;
				while (valueOfConnection == 0)
				{
					valueOfConnection = rand() % 50 - regulatingValue;
				}
				if (randStartNode != randEndNode)
				{
					addEdge(randStartNode, randEndNode, valueOfConnection, iterEdges);
				}
				else if (allowLoops)
				{
					addEdge(randStartNode, randEndNode, valueOfConnection, iterEdges);
				}
			}
		}
	}
}

void Graph_list::printGraph() const
{
	std::cout << " \n \n List representation of Graph \n \n ";
	for (int iterStartNode = 0; iterStartNode < this->main_amountOfNodes; iterStartNode++)
	{
		std::cout << iterStartNode;
		for (int iterEdge = 0; iterEdge < this->main_amountOfEges; iterEdge++)
		{
			if (this->in_Edge[iterEdge].nodeStart==iterStartNode)
			{
				std::cout << "->" << in_Edge[iterEdge].nodeEnd << "|" << in_Edge[iterEdge].value << "]";
			}
			
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

const int Graph_list::readFile(const std::string fileName) 
{
	std::ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		std::cerr << "File is not open" << std::endl;
		return -1; //error code
	}
	int startingAlgNode, startNode, endNode, value;
	inFile >> main_amountOfEges >> main_amountOfNodes >> startingAlgNode;
	this->in_Edge = new Edge[main_amountOfEges];

	for (int iterEdge = 0; iterEdge < this->main_amountOfEges; iterEdge++)
	{
		inFile >> startNode >> endNode >> value;
		addEdge(startNode, endNode, value, iterEdge);
	}
	inFile.close();
	return startingAlgNode;
}

void Graph_list::createInput(const int startNode) const
{
	std::ofstream out_file("out_input.txt");
		if (!out_file.is_open)
		{
			std::cerr << "File not open" << std::endl;
			return;
		}
		out_file << this->main_amountOfEges << this->main_amountOfNodes << startNode << std::endl;
		for (int iterEdge = 0; iterEdge < main_amountOfEges; iterEdge++)
		{
			out_file << in_Edge[iterEdge].nodeStart << " " << in_Edge[iterEdge].nodeEnd << " " << in_Edge[iterEdge].value << "\n";
		}
		out_file.close();
}

void Graph_list::addEdge(int nodeStart, int nodeEnd, int value, int whereflag) const
{
	this->in_Edge[whereflag].nodeStart = nodeStart;
	this->in_Edge[whereflag].nodeEnd = nodeEnd;
	this->in_Edge[whereflag].value = value;


}

bool Graph_list::isExisting(int nodeStart, int nodeEnd) const
{
	for (int iterEdges = 0;iterEdges<this->main_amountOfEges;iterEdges++ )
	{
		if (this->in_Edge[iterEdges].nodeStart == nodeStart && this->in_Edge[iterEdges].nodeEnd == nodeEnd)
		{
			return true;
		}
	}
	return false;
}
