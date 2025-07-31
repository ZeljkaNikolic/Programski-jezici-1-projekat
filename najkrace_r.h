#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>

#include "nodes.h"

void floyd(TrafficGraph g, double d[6][6], int t[6][6]);

void putanja(int i, int j, TrafficGraph g, int t[6][6], int dest);
void initT(TrafficGraph g, int t[6][6]);

void initD(TrafficGraph g, double d[6][6]);


