#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;


#define X_IMAG 1000
#define Y_IMAG 1000

void write_ppm(const string& filename, vector<vector<vector<int>>> image);

vector<vector<vector<int>>> load_ppm(const string& filename);

vector<int> find_closest(vector<int> pixel, vector<vector<vector<bool>>>& available);
double compute_dist(vector<int> p1, vector<int> p2);
int find_smallest_i(vector<double> x);
int getRandomNumber(int min, int max);