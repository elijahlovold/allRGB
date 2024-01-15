#include "rgb.h"
#include <chrono>
#include <algorithm>
#include <random>

int main()
{
    auto prox = proximity_list(10);
    std::srand(static_cast<unsigned>(std::time(0)));

    vector<vector<vector<bool>>> available_colors(256, vector<vector<bool>>(256, vector<bool>(256, true)));

    vector<vector<vector<int>>> target = load_ppm("tar.ppm");

    unsigned int height = target.size();
    unsigned int width = (height > 0) ? target[0].size() : 0;
    
    vector<vector<vector<int>>> result(height, vector<vector<int>>(width, vector<int>(3, 0)));
    int max = width * height;

    vector<vector<int>> availableCoors;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            vector<int> test = {y, x};
            availableCoors.push_back(test);
        }
    }
    cout << "avail size: " << availableCoors.size() << endl << endl << endl;

    int rand_i;
    vector<int> coord;
    vector<int> color;
    vector<int> result_color;
    auto rng = std::default_random_engine {};

    random_device rd;
    mt19937 g(rd());
    shuffle(availableCoors.begin(), availableCoors.end(), g);

    for (int i = 0; i < max; i++) {
        // auto start = std::chrono::high_resolution_clock::now();
        coord = availableCoors[i];
        color = target[coord[0]][coord[1]];
        result_color = find_closest(color, available_colors, prox);
        result[coord[0]][coord[1]] = result_color;
        // auto stop = std::chrono::high_resolution_clock::now();

        // auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        // std::cout << duration.count() << " nanoseconds" << std::endl;

        if (!(i%100)){
            cout << "still working!:)\n";
            cout << coord[0] << " " << coord[1] << endl;
            cout << rand << " index: " << i << endl << endl;
        }
    }

    write_ppm("test.ppm", result);
}

