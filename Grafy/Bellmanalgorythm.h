#pragma once
#include <chrono>
#include <string>

#include "Graph_list.h"
#include "Graph_martix.h"

double bellmanAlg(std::shared_ptr<Graph_list> workingGraph, int startingNode);
double bellmanAlg(std::shared_ptr<Graph_matrix> workingGraph, int startingNode);
void resoults(std::string pathString[], int distanceStorage[], int nodesAmount, int startingNode);