#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

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
    int antinode_num = 0;
    int map_y_pos = 0;
    std::vector<std::string> city_map;
    std::map<char, std::vector<std::vector<int>>> antenna_map; // holds antenna frequency and different locations of antenna

    while (std::getline(input_file, text))
    {
        city_map.push_back(text);

        for (int i = 0; i < text.size(); i++)
        {
            if (text[i] != '.')
            {
                std::vector<int> curr_pos = {map_y_pos, i};

                if (antenna_map.find(text[i]) == antenna_map.end())
                {
                    std::vector<std::vector<int>> positions;
                    positions.push_back(curr_pos);
                    antenna_map[text[i]] = positions;
                }
                else
                {
                    antenna_map[text[i]].push_back(curr_pos);
                }
            }
        }

        map_y_pos++;
    }

    // calculate x and y difference between each antenna then check if antinode pos is valid
    for (auto entry : antenna_map)
    {
        for (int i = 0; i < entry.second.size(); i++)
        {
            for (int j = 0; j < entry.second.size(); j++)
            {
                // if the same antenna, skip
                if (entry.second[i][0] == entry.second[j][0] && entry.second[i][1] == entry.second[j][1])
                    continue;
                
                int x_diff = entry.second[j][1] - entry.second[i][1];
                int y_diff = entry.second[j][0] - entry.second[i][0];

                int antinode_coord_x = entry.second[j][1] + x_diff;
                int antinode_coord_y = entry.second[j][0] + y_diff;

                // is valid antinode pos
                if (antinode_coord_x < 0 || antinode_coord_y < 0 || antinode_coord_x >= city_map[0].size() || antinode_coord_y >= city_map.size())
                    continue;

                // is unique antinode pos
                if (city_map[antinode_coord_y][antinode_coord_x] != '#')
                    antinode_num++;

                city_map[antinode_coord_y][antinode_coord_x] = '#';
            }
        }
    }

    std::cout << "Number of unique antinode locations: " << antinode_num << std::endl;

    input_file.close();
    return 0;
}
