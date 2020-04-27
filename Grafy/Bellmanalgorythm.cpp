#include "Bellmanalgorythm.h"

double bellmanAlg(std::shared_ptr<Graph_list> workingGraph, int startingNode)
{
	std::string* pathStorage = new std::string[workingGraph->nodesGetter()];
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distanceStorage = new int[workingGraph->nodesGetter()];
	
	for (int iterNodes = 0; iterNodes < workingGraph->nodesGetter(); iterNodes++)
	{
		distanceStorage[iterNodes] = infinity;
	}
	distanceStorage[startingNode] = 0;
	for(int iterNodes=1;iterNodes<workingGraph->nodesGetter();iterNodes++)
	{
		for (int iterEdges = 0; iterEdges < workingGraph->edgesGetter(); iterEdges++)
		{
			int temNodeStart = workingGraph->edgeGetter()[iterEdges].nodeStart;
			int temNodeEnd = workingGraph->edgeGetter()[iterEdges].nodeEnd;
			int temValue = workingGraph->edgeGetter()[iterEdges].value;

			if (distanceStorage[temNodeStart]+temValue < distanceStorage[temNodeEnd])
			{
				distanceStorage[temNodeEnd] = distanceStorage[temNodeStart] + temValue;
			}

			pathStorage[temNodeEnd].clear();
			pathStorage[temNodeEnd].append(pathStorage[temNodeStart] + std::to_string(temNodeStart) + "->");
		}
	}
	for (int iterNodes = 1; iterNodes < workingGraph->nodesGetter(); iterNodes++)
	{
		for (int iterEdges = 0; iterEdges < workingGraph->edgesGetter(); iterEdges++)
		{
			int temNodeStart = workingGraph->edgeGetter()[iterEdges].nodeStart;
			int temNodeEnd = workingGraph->edgeGetter()[iterEdges].nodeEnd;
			int temValue = workingGraph->edgeGetter()[iterEdges].value;

			if (distanceStorage[temNodeStart] + temValue < distanceStorage[temNodeEnd])
			{
				if (distanceStorage[temNodeStart] > infinity / 2)
				{
					distanceStorage[temNodeStart] = infinity;

				}
				else
				{
					distanceStorage[temNodeEnd] = negInfinity;
				}
			}
			else if (distanceStorage[temNodeStart]>infinity/2) 
			{
				distanceStorage[temNodeStart] = infinity;
			}
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();

	resoults(std::move(pathStorage), std::move(distanceStorage), workingGraph->nodesGetter(), startingNode);
	delete[] pathStorage;
	delete[] distanceStorage;

		return std::chrono::duration<double,std::milli>(endTime-startTime).count();
}

double bellmanAlg(std::shared_ptr<Graph_matrix> workingGraph, int startingNode)
{
	std::string* pathStorage = new std::string[workingGraph->nodesGetter()];
	auto startTime = std::chrono::high_resolution_clock::now();
	int* distanceStorage = new int[workingGraph->nodesGetter()];

	for (int iterNodes = 0; iterNodes < workingGraph->nodesGetter(); iterNodes++)
	{
		distanceStorage[iterNodes] = infinity;
	}
	distanceStorage[startingNode] = 0;
	for (int iterNodes = 1; iterNodes < workingGraph->nodesGetter(); iterNodes++)
	{
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->nodesGetter(); iterNodeCell++)
		{
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->nodesGetter(); iterNodeCollumn++)
			{
				int temNodeStart = iterNodeCell;
					int temNodeEnd = iterNodeCollumn;
				int temValue = workingGraph->getValue(iterNodeCell,iterNodeCollumn);
				if (distanceStorage[temNodeStart] + temValue < distanceStorage[temNodeEnd])
				{
					distanceStorage[temNodeEnd] = distanceStorage[startingNode] + temValue;
					pathStorage[temNodeEnd].clear();
					pathStorage[temNodeEnd].append(pathStorage[temNodeStart] + std::to_string(temNodeStart) + "->");
				}
			}
		}
	}
	for (int iterNodes = 1; iterNodes < workingGraph->nodesGetter(); iterNodes++)
	{
		for (int iterNodeCell = 0; iterNodeCell < workingGraph->nodesGetter(); iterNodeCell++)
		{
			for (int iterNodeCollumn = 0; iterNodeCollumn < workingGraph->nodesGetter(); iterNodeCollumn++)
			{
				int temNodeStart = iterNodeCell;
				int temNodeEnd = iterNodeCollumn;
				int temValue = workingGraph->getValue(iterNodeCell, iterNodeCollumn);
				if (distanceStorage[temNodeStart] + temValue < distanceStorage[temNodeEnd])
				{
					if (distanceStorage[temNodeStart]>infinity/2)
					{
						distanceStorage[temNodeStart] = infinity;
					}
					else if (temValue==infinity)
					{
						continue;
					}
					else
					{
						distanceStorage[temNodeEnd] = negInfinity;
					}
				}
				else if(distanceStorage[temNodeStart]>infinity/2)
				{
					distanceStorage[temNodeStart] = infinity;
				}
			}
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();

	resoults(std::move(pathStorage), std::move(distanceStorage), workingGraph->nodesGetter(), startingNode);
	delete[] pathStorage;
	delete[] distanceStorage;

	return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

void resoults(std::string pathString[], int distanceStorage[], int nodesAmount, int startingNode)
{
	std::ofstream resoultsFile("Resoults.txt");
	std::cout << "\n           Results            \n\n";
	std::cout << "Starting node was : " << startingNode << std::endl;
	resoultsFile << "\n           Results            \n\n";
	resoultsFile << "Starting node was : " << startingNode << std::endl;
	for (int itrNodes = 0 ; itrNodes<nodesAmount;itrNodes++)
	{
		if (distanceStorage[itrNodes] == infinity)
		{
			std::cout << itrNodes << "-> inf" << std::endl;
			resoultsFile << itrNodes << "-> inf" << std::endl;
			continue;
		}
		else if (distanceStorage[itrNodes] == negInfinity)
		{
			std::cout << itrNodes << "-> -inf" << std::endl;
			resoultsFile << itrNodes << "-> -inf" << std::endl;
			continue;
		}
		else
		{
			std::cout << itrNodes << "->" << distanceStorage[itrNodes]<< std::endl;
			resoultsFile << itrNodes << "->" << distanceStorage[itrNodes] << std::endl;
		}

		std::cout << "  ";
		resoultsFile << "  ";

		if ((distanceStorage[itrNodes] >= 100 && distanceStorage[itrNodes] < 1000) || (-100 > distanceStorage[itrNodes] && distanceStorage[itrNodes] <= -10)) {

			std::cout << " The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << " The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		else if (0 <= distanceStorage[itrNodes] && distanceStorage[itrNodes] < 10) {

			std::cout << "   The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << "   The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		else if ((distanceStorage[itrNodes] >= 10 && distanceStorage[itrNodes] < 100) || (-10 < distanceStorage[itrNodes] && distanceStorage[itrNodes] < 0)) {

			std::cout << "  The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << "  The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		else { 

			std::cout << "The shortest path: " << pathString[itrNodes] << itrNodes;
			resoultsFile << "The shortest path: " << pathString[itrNodes] << itrNodes;
		}
		std::cout << std::endl;
		resoultsFile << std::endl;
	}
}
