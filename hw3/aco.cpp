#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <set>
#include <algorithm>
#include <chrono>
using namespace std;

struct Location {
    int id;
    double x;
    double y;
};

struct Individual {
    vector<int> order;
    double distance;
};

vector<Location> parse(const string& filename) {
    vector<Location> locations;
    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "error opening file";
        exit(1);   
    }

    Location temp;
    while (inputFile >> temp.id >> temp.x >> temp.y) {
        locations.push_back(temp);
    }

    inputFile.close();

    return locations;
}