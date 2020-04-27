#include "Graph_martix.h"
#include "Graph_list.h"

Graph_matrix::Graph_matrix(int nodesAmount, int density):Graph(nodesAmount,static_cast<int>(density*nodesAmount*(nodesAmount-1)), density), matrix(std::make_unique<std::unique_ptr<int[]>[]>(nodesAmount))
{
	/*Look of matrix
	  1 2 3 4 5 6 ->nodes
	1 0 x x x x x	
	2 x	0 x x x x
	3 x	x 0 x x x
	4 x x x 0 x x
	5 x x x x 0 x
	6 x x x x x 0
	|
	v
	nodes
	where x is value
	*/
	for (int iterNodesCell = 0; iterNodesCell < this->main_amountOfNodes; iterNodesCell++)
	{
		matrix[iterNodesCell] = std::make_unique<int[]>(nodesAmount);
		for (int iterNodesCollumn = 0; iterNodesCollumn < this->main_amountOfNodes; iterNodesCollumn++)
		{
			if (iterNodesCell==iterNodesCollumn)
			{
				matrix[iterNodesCell][iterNodesCollumn] = 0;
			}
			else
			{
				matrix[iterNodesCell][iterNodesCollumn] = infinity;
			}
		}
	}

}


void Graph_matrix::fillGraph(const bool allowLoops) const
{
	if (this->main_density==1)
	{
		for (int iterNodesCell = 0; iterNodesCell < this->main_amountOfNodes; iterNodesCell++)
		{
			for (int iterNodesCollumn = 0; iterNodesCollumn < this->main_amountOfNodes; iterNodesCollumn++)
			{
				if (iterNodesCell!=iterNodesCollumn)
				{
					int randValue = rand() % 50 - regulatingValue;
					while (randValue==0)
					{
						randValue = rand() % 50 - regulatingValue;
					}
					matrix[iterNodesCell][iterNodesCollumn] = randValue;
				}
			}
		}
	}
	else
	{
		int iterEdges = this->main_amountOfEges;
		while (iterEdges!=0)
		{
			int cellNode = rand() % this->main_amountOfNodes;
			int collumnNode = rand() % this->main_amountOfNodes;
			if (matrix[cellNode][collumnNode]==0||matrix[cellNode][collumnNode]==infinity)
			{
				int randValue = rand() % 50 - regulatingValue;
				while (randValue == 0)
				{
					randValue = rand() % 50 - regulatingValue;
				}

				if(cellNode!=collumnNode)
				{
					matrix[cellNode][collumnNode] = randValue;
					--iterEdges;
				}
				else if(allowLoops)
				{
					matrix[cellNode][collumnNode] = randValue;
					--iterEdges;
				}
			}
		}

	}
}

void Graph_matrix::printGraph() const
{
	std::cout << "\n Matrix represetation of Graph \n\n";
	for (int nodeIter = 0; nodeIter < this->main_amountOfNodes; nodeIter++)
	{
		std::cout << "  " << nodeIter;
	}
	std::cout << std::endl << std::endl;
	for (int nodeCell = 0; nodeCell<this->main_amountOfNodes;nodeCell++)
	{
		std::cout << nodeCell << " *";
		for (int nodeCollumn=0; nodeCollumn<this->main_amountOfNodes; nodeCollumn++)
		{
			int temporaryMatrixValue = matrix[nodeCell][nodeCollumn];
			if (temporaryMatrixValue==infinity)
			{
				std::cout << "#";
			}
			else
			{
				std::cout << temporaryMatrixValue;
			}
			std::cout << "  ";
			
		}
		std::cout << "*" << std::endl;

	}
	std::cout << std::endl;
}

const int Graph_matrix::readFile(const std::string fileName) 
{
	std::ifstream inFile(fileName);
	if(!inFile.is_open())
	{
		std::cerr << " Input file is not open" << std::endl;
		return -1;
	}
	int startingNode, nodeStart, nodeEnd, value;
	inFile >> this->main_amountOfEges >> this->main_amountOfNodes >> startingNode;
	matrix = std::make_unique<std::unique_ptr<int[]>[]>(this->main_amountOfNodes);
	for (int iterNodesCell = 0; iterNodesCell < this->main_amountOfNodes; iterNodesCell++)
	{
		matrix[iterNodesCell] = std::make_unique<int[]>(this->main_amountOfNodes);
		for (int iterNodesCollumn = 0; iterNodesCollumn < this->main_amountOfNodes; iterNodesCollumn++)
		{
			if (iterNodesCell == iterNodesCollumn)
			{
				matrix[iterNodesCell][iterNodesCollumn] = 0;
			}
			else
			{
				matrix[iterNodesCell][iterNodesCollumn] = infinity;
			}
		}
	}
	for (int iterEdge = 0; iterEdge < this->main_amountOfEges; iterEdge++)
	{
		inFile >> nodeStart >> nodeEnd >> value;
		matrix[nodeStart][nodeEnd] = value;
	}
	inFile.close();
	return startingNode;
}

void Graph_matrix::createInput(const int startNode) const
{
	std::ofstream outFile("OutInput.txt");
	if (!outFile.is_open())
	{
		std::cerr << " Output File not Created";
		return;
	}
	
	outFile << this->main_amountOfEges << " " << this->main_amountOfNodes << " " << startNode<< std::endl;
	for (int iterNodesCell = 0; iterNodesCell < this->main_amountOfNodes; iterNodesCell++)
	{		
		for (int iterNodesCollumn = 0; iterNodesCollumn < this->main_amountOfNodes; iterNodesCollumn++)
		{
			if (matrix[iterNodesCell][iterNodesCollumn] != infinity && matrix[iterNodesCell][iterNodesCollumn] != 0)
			{
				outFile << iterNodesCell << " " << iterNodesCollumn << " " << matrix[iterNodesCell][iterNodesCollumn] << std::endl;
			}
		}
	}
	outFile.close();
}
