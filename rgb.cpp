#include "rgb.h"

vector<vector<vector<int>>> load_ppm(const string& filename) {
    ifstream fin;
    fin.open(filename);

    string magic;
    int width, height;
    fin >> magic >> width >> height;

    int maxColor;
    fin >> maxColor;

    cout << "Type: " << magic << "\nWidth: " << width << "\nHeight: " << height << "\nMaxC: " << maxColor << endl;

    if (magic != "P3" || maxColor != 255) {
        cerr << "Invalid PPM file format." << endl;
        exit(1);
    }

    vector<vector<vector<int>>> image;
    for (int i = 0; i < height; ++i) {
        vector<vector<int>> row;
        for (int j = 0; j < width; ++j) {
            vector<int> pixel(3, 0);
            for (int k = 0; k < 3; ++k) {
                fin >> pixel[k];
            }
            row.push_back(pixel);
        }
        image.push_back(row);
    }


    fin.close();

    cout << filename << " done reading\n";
    return image;
}

void write_ppm(const string& filename, vector<vector<vector<int>>> image) {

    ofstream fout;
    fout.open (filename);

    // Get the dimensions
    size_t height = image.size();
    size_t width = (height > 0) ? image[0].size() : 0;

    fout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fout << image[i][j][0] << ' ' << image[i][j][1] << ' ' << image[i][j][2] << '\n';
        }
    }

    fout.close();
    cout << filename << " done writing\n";
}

double dist_from_origin(vector<int> p1){
    vector<int> origin = {0,0,0};
    if(p1 == origin) {
        return 0;
    }
    return sqrt(
        pow(0 - p1[0], 2) +
        pow(0 - p1[1], 2) +
        pow(0 - p1[2], 2)
    );
}

void printVector(const std::vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

vector<vector<int>> proximity_list(int r) {
    vector<pair<double, vector<int>>> offsets;
    for (int x = -r; x < r; x++){
        for (int y = -r; y < r; y++){
            for (int z = -r; z < r; z++){
                double dist = dist_from_origin({x,y,z});
                offsets.push_back(make_pair(dist, vector<int>{x,y,z}));
            }
        }
    }
    sort(offsets.begin(), offsets.end());
    vector<vector<int>> result;
    for (const auto& element : offsets) {
        result.push_back(element.second);
    }

    return result;
}

vector<int> find_closest(vector<int> pixel, vector<vector<vector<bool>>>& available, vector<vector<int>>& offsets){
    bool found = false;
    //largest offset radius
    int r = 10;
    bool check_bounds = true;
    // bool check_bounds = false;
    // for (const auto& c : pixel) {
    //     if(c - r < 0 || c + r > 255 ) {
    //         check_bounds = true;
    //         break;
    //     }
    // }
    int x,y,z;
    for (int i = 0; !found && i < offsets.size(); i++) {
        x = pixel[0] + offsets[i][0];
        y = pixel[1] + offsets[i][1];
        z = pixel[2] + offsets[i][2];
        bool out_of_bounds = false;
        if(check_bounds) {
            if(x < 0 || x > 255 ) {
                out_of_bounds = true;
            }
            if(y < 0 || y > 255 ) {
                out_of_bounds = true;
            }
            if(z < 0 || z > 255 ) {
                out_of_bounds = true;
            }
        }
        if(!out_of_bounds) {
            if (available[x][y][z]) {
                available[x][y][z] = false;
                break;
            }

        }

    }
    return {x,y,z};
}
