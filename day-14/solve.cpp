#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

int main(int argc, char* argv[])
{
    // check if input file is specified or not
    if (argc != 2)
    {
        std::cerr << "Unspecified input file\n";
        return -1;
    }

    std::ifstream input_file(argv[1]);
    std::string text;

    // map size
    int map_width = 101;
    int map_height = 103;

    // robot in each quadrant count
    int quadrant1 = 0;
    int quadrant2 = 0;
    int quadrant3 = 0;
    int quadrant4 = 0;

    std::regex re("(-?\\d+),(-?\\d+).*=(-?\\d+),(-?\\d+)");

    while (std::getline(input_file, text))
    {
        std::smatch matches;
        regex_search(text, matches, re);

        int px = stoi(matches[1]);
        int py = stoi(matches[2]);
        int vx = stoi(matches[3]);
        int vy = stoi(matches[4]);

        // bot's position after 100s
        int x = (px + vx * 100) % map_width;
        int y = (py + vy * 100) % map_height;

        // convert negative results to positive
        if (x < 0) x += map_width;
        if (y < 0) y += map_height;

        // robot cannot be in the middle of the map
        // - 1 because the map width and height is always odd
        if (x < (map_width - 1) / 2) // robot on left side of map
        {
            quadrant1 += y < (map_height - 1) / 2;
            quadrant3 += y > (map_height - 1) / 2;
        }
        else if (x > (map_width - 1) / 2) // robot on right side of map
        {
            quadrant2 += y < (map_height - 1) / 2;
            quadrant4 += y > (map_height - 1) / 2;
        }
    }

    std::cout << "Safety factor after 100s: " << quadrant1 * quadrant2 * quadrant3 * quadrant4 << std::endl;

    input_file.close();
    return 0;
}
