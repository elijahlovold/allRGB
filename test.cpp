#include "rgb.h"


int main()
{
    std::srand(static_cast<unsigned>(std::time(0)));

    vector<vector<vector<bool>>> available_colors(255, vector<vector<bool>>(255, vector<bool>(255, true)));

    vector<vector<vector<int>>> target = load_ppm("tar.ppm");
    

    int height = target.size();
    int width = (height > 0) ? target[0].size() : 0;
    
    vector<vector<vector<int>>> result(height, vector<vector<int>>(width, vector<int>(3, 0)));
    int max = width * height;

    vector<vector<int>> availableCoors;


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            vector<int> test = {x, y};
            availableCoors.push_back(test);
        }
    }
    cout << availableCoors.size() << endl;

    cout << "2\n";
    for (int i = 0; i < max; i++) {
        int rand = std::rand() % availableCoors.size();  //
        // int rand = getRandomNumber(0, availableCoors.size());
        
        vector<int> coord = availableCoors[rand];
        
        available_colors.erase(available_colors.begin() + rand);

        vector<int> color = target[coord[0]][coord[1]];
        // cout << "built\n";
        vector<int> result_color = find_closest(color, available_colors);
        // cout << "found\n";

        result[coord[0]][coord[1]] = result_color;
        if (!(i%1000)){
            cout << "still working!:)\n";
            cout << coord[0] << " " << coord[1] << endl;
            cout << rand << endl;
        }
    }

    write_ppm("test.ppm", result);
}

