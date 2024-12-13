#include <iostream>
#include <fstream>
#include <vector>
#include <set>

void search_trailhead(std::vector<std::string> topo_map, int i, int j, int prev_val, std::set<std::vector<int>>& visited_pos)
{
    // out of bound or was visited before
    if (i < 0 || i > topo_map.size() || j < 0 || j > topo_map[0].size() || visited_pos.find({i, j}) != visited_pos.end())
    {
        visited_pos.insert({-1, -1});
        return;
    }

    // not valid trail
    if (topo_map[i][j] - '0' != prev_val + 1)
    {
        visited_pos.insert({-1, -1});
        return;
    }

    // reached end pos
    if (topo_map[i][j] - '0' == 9)
    {
        visited_pos.insert({i, j});
        return;
    }

    // recursion search
    search_trailhead(topo_map, i - 1, j, topo_map[i][j] - '0', visited_pos); // up
    search_trailhead(topo_map, i, j + 1, topo_map[i][j] - '0', visited_pos); // right
    search_trailhead(topo_map, i + 1, j, topo_map[i][j] - '0', visited_pos); // down
    search_trailhead(topo_map, i, j - 1, topo_map[i][j] - '0', visited_pos); // left
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
    int trailhead_scores = 0;
    std::vector<std::string> topo_map;

    while (std::getline(input_file, text))
        topo_map.push_back(text);

    for (int i = 0; i < topo_map.size(); i++)
    {
        for (int j = 0; j < topo_map[0].size(); j++)
        {
            // found start of trail
            if (topo_map[i][j] == '0')
            {
                std::set<std::vector<int>> visited_pos; // contains all valid trailheads end pos
                search_trailhead(topo_map, i, j, -1, visited_pos);
                trailhead_scores += visited_pos.size() - 1;
            }
        }
    }

    std::cout << "Sum of trailhead scores: " << trailhead_scores << std::endl;

    input_file.close();
    return 0;
}
