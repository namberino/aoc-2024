#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

std::pair<int, int> operator +(const std::pair<int, int>& x, const std::pair<int, int>& y)
{
    return std::make_pair(x.first + y.first, x.second + y.second);
}

std::map<int, std::vector<std::pair<int, int>>> region_mapping;
std::set<std::pair<int, int>> visited;

void get_region(std::vector<std::string> garden_map, int i, int j, char current_plant, int region_id)
{
    // out of map bounds or has been visited
    if (i < 0 || j < 0 || i >= garden_map.size() || j >= garden_map[0].size() || visited.find({i, j}) != visited.end() || garden_map[i][j] != current_plant)
        return;

    visited.insert({i, j});

    // push coord into region mapping
    if (region_mapping.find(region_id) != region_mapping.end())
    {
        region_mapping[region_id].push_back({i, j});
    }
    else
    {
        std::vector<std::pair<int, int>> new_mapping = {{i, j}};
        region_mapping[region_id] = new_mapping;
    }

    // check adjacent tiles
    get_region(garden_map, i, j + 1, current_plant, region_id);
    get_region(garden_map, i + 1, j, current_plant, region_id);
    get_region(garden_map, i, j - 1, current_plant, region_id);
    get_region(garden_map, i - 1, j, current_plant, region_id);
}

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
    int total_fencing_price = 0;
    std::vector<std::string> garden_map;

    while (std::getline(input_file, text))
        garden_map.push_back(text);

    // backtrack to find regions, maybe a map to store region tiles positions (assign unique IDs to them)

    // obtain tile coords of each region in the map
    int region_id = 1;
    for (int i = 0; i < garden_map.size(); i++)
    {
        for (int j = 0; j < garden_map[0].size(); j++)
            get_region(garden_map, i, j, garden_map[i][j], region_id++);
    }

    // directions
    std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // right, down, left, up

    // calculate price (with area and perimeter)
    for (auto mapping : region_mapping)
    {
        int area = mapping.second.size();
        int perimeter = 0;

        for (int i = 0; i < area; i++)
        {
            // check all 4 adjacent tiles of current tile
            for (auto direction : directions)
            {
                std::pair<int, int> tile_coord = mapping.second[i] + direction;
                char current_region = garden_map[mapping.second[i].first][mapping.second[i].second];
                char tile_to_check = garden_map[tile_coord.first][tile_coord.second];
                
                // if not the same region or out of bounds
                if (tile_to_check != current_region || tile_coord.first < 0 || tile_coord.second < 0 || tile_coord.first > garden_map.size() || tile_coord.second > garden_map[0].size())
                    perimeter++;
            }
        }

        total_fencing_price += area * perimeter;
    }

    std::cout << "Total price of fencing all regions: " << total_fencing_price << std::endl;

    input_file.close();
    return 0;
}
