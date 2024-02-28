#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <set>
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

vector<int> shuffler(const vector<int>& default_order) {
    vector<int> shuffled_order = default_order; 
    srand(time(0));

    for (int i = shuffled_order.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1); 
        swap(shuffled_order[i], shuffled_order[j]); 
    }

    return shuffled_order;
}

 double fitness_score(const vector<int>& order, const vector<Location>& locations) {
    double score = 0;
    for (int i = 0; i < order.size() - 1; ++i) {
        score += sqrt(pow(locations[order[i]].x - locations[order[i + 1]].x, 2) + pow(locations[order[i]].y - locations[order[i + 1]].y, 2));
    }
    return 1/score;

 }



Individual tournament(const std::vector<Individual>& population, std::vector<Location>& locations) {
    int k = 5;
    Individual best;
    bool flag = true;
    std::set<int> selectedIndexes;

    for (int i = 0; i < k; ++i) {
        int index;
        do {
            index = std::rand() % population.size();
        } while (selectedIndexes.count(index) > 0); 

        selectedIndexes.insert(index);

        if (flag || population[index].distance < best.distance) {
            best = population[index];
            flag = false;
        }
    }

    return best;
}

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

vector<Individual> initPopulation(const vector<int>& default_order, int n, vector<Location>& locations, Individual& best) {
    vector<Individual> population;
     double distance, best_distance = 10000;

    for (int i = 0; i < n; ++i) {
        vector<int> new_order = shuffler(default_order);
        distance = fitness_score(new_order, locations); 
        if(distance < best_distance) {
            best_distance = distance;
            best.order = new_order;
            best.distance = distance;
        };
        population.push_back({new_order, distance});
    }

    return population;
}

int main() {
    vector<Location> locations = parse("input.txt");

    for (const auto& location : locations) {
        cout << "ID: " << location.id << ", X: " << location.x << ", Y: " << location.y << endl;
    }

    vector<int> default_order(locations.size());
    for (int i = 0; i < locations.size(); ++i) {
        default_order[i] = i;
    }
    Individual best;
    vector<Individual> population = initPopulation(default_order, 10, locations, best);

    int generation = 0;
    return 0;
}

