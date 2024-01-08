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

vector<int> find_closest(vector<int> pixel, vector<vector<vector<bool>>>& available){
    // cout << pixel[0] << " " << pixel[1] << " " << pixel[2] << endl;

    bool found = false;
    vector<vector<int>> possible_coords;
    for (int r = 0; !found && r < X_IMAG ; r++){

        int lower_i = (pixel[0] - r < 0 ? 0 : pixel[0] - r);
        int upper_i = (pixel[0] + r > 255 ? 255 : pixel[0] + r);
        int lower_j = (pixel[1] - r < 0 ? 0 : pixel[1] - r);
        int upper_j = (pixel[1] + r > 255 ? 255 : pixel[1] + r);
        int lower_k = (pixel[2] - r < 0 ? 0 : pixel[2] - r);
        int upper_k = (pixel[2] + r > 255 ? 255 : pixel[2] + r);

        for (int i = lower_i; i < upper_i; i++){
            for (int j = lower_j; j < upper_j; j++){
                for (int k = lower_k; k < upper_k; k++){
                    // cout << i << " " << j << " " << k << "\n";
                    if (available[i][j][k]) {
                        possible_coords.push_back(vector<int> {i, j, k});
                        found = true;
                    }
                }
            }
        }
    }

    if (!found) {
        cout << "failed";
        throw runtime_error("Pixel not found!");
    }

    int N = possible_coords.size();
    vector<double> distances (N, 0);
    for (int i = 0; i < N; i++){
        distances[i] = compute_dist(possible_coords[i], pixel);
    }

    int i_solution = find_smallest_i(distances);

    available[possible_coords[i_solution][0]][possible_coords[i_solution][1]][possible_coords[i_solution][2]] = false;

    return possible_coords[i_solution];
}

int find_smallest_i(vector<double> x){

    auto minIterator = min_element(x.begin(), x.end());

    if (minIterator != x.end()) {
        int index = distance(x.begin(), minIterator);
        return index;
    } else {
        return -1;
    }
}

double compute_dist(vector<int> p1, vector<int> p2){
    return sqrt(
        pow(p2[0] - p1[0], 2) +
        pow(p2[1] - p1[1], 2) +
        pow(p2[2] - p1[2], 2)
    );
}

int getRandomNumber(int min, int max) {
    // Random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(min, max); // Define the range

    return distr(gen); // Generate a random number within the given range
}
