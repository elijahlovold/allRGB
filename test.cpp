#include "rgb.h"


int main()
{
    auto prox = proximity_list(5);
    // return 0;
    std::srand(static_cast<unsigned>(std::time(0)));

    vector<vector<vector<bool>>> available_colors(255, vector<vector<bool>>(255, vector<bool>(255, true)));

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
    for (int i = 0; i < max; i++) {
        rand_i = static_cast<int> ((std::rand() / double(RAND_MAX)) * availableCoors.size());  // scale to proper size...
        coord = availableCoors[rand_i];
        availableCoors.erase(availableCoors.begin() + rand_i);

        // std::swap(availableCoors[rand_i], availableCoors.back());
        // availableCoors.pop_back();

        // cout << "coord: " << coord[0] << " " << coord[1] << endl;

        color = target[coord[0]][coord[1]];
        // cout << "color: " << color[0] << " " << color[1] << " " << color[2] << endl;
        result_color = find_closest(color, available_colors, prox);
        // cout << "found\n";

        result[coord[0]][coord[1]] = result_color;

        if (!(i%100)){
            cout << "still working!:)\n";
            cout << coord[0] << " " << coord[1] << endl;
            cout << rand << " index: " << i << endl << endl;
        }
    }

    write_ppm("test.ppm", result);
}

