#include <iostream>
#include "Graph.h"
#include"Bellmanalgorythm.h"
template<typename T>
std::string Driver(int(&verticlesStorage)[5],double(&densityStorage)[4],int loops)
{
	std::string result;
	for (auto density:densityStorage)
	{
		for (auto verticles : verticlesStorage)
		{
			double accumulatedTime = 0;
			for (int iterLoops = 0; iterLoops < loops; iterLoops++)
			{
				std::shared_ptr<T> graph = std::make_shared<T>(verticles, density);
				int startingNode = rand() % verticles;

				graph->fillGraph(true);

				accumulatedTime += bellmanAlg(std::move(graph), startingNode);
			}
			
			result+=std::to_string((accumulatedTime * 100 / loops) + 1);
			result += ",";
			
			std::cout << verticles << " verticles done " << std::endl;
		}
		std::cout << density << " density done " << std::endl;
	}
	return result;
}
int main()
{
	int verticesStorage[5] = { 5,10,20,60,100 };
	double densityStorage[4] = { 0.25,0.5,0.75,1 }; 
	int loop = 100;

	int verticesStoragetest[1] = { 5 };
	double densityStoragetest[1] = { 0.25 };
	int looptest = 10;

	std::ofstream file("Times.txt");
	if (!file.is_open()) {

		std::cerr << "output not open" << std::endl;
		return 1;
	}

	file<<Driver<Graph_list>(verticesStorage, densityStorage, loop); //testing for List
	std::cout << "LIST DONE\n" << std::endl;
	std::cout << " ";
	file<<Driver<Graph_matrix>(verticesStorage, densityStorage, loop);	//testing for Matrix
	std::cout << "MATRIX DONE" << std::endl;

	file.close();
	return 0;

	
}