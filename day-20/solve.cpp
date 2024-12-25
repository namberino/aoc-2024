#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int bfs(std::vector<std::string> game_map, int start_x, int start_y)
{
    std::map<std::pair<int, int>, int> visited; // holds cell with distance to cell from starting point
    std::queue<std::pair<std::pair<int, int>, int>> qu;

    qu.push({{start_x, start_y}, 0});

    // BFS for base path
    while (!qu.empty())
    {
        auto [curr_pos, curr_dist] = qu.front();
        qu.pop();

        for (auto direction : directions)
        {
            std::pair<int, int> new_pos = {curr_pos.first + direction.first, curr_pos.second + direction.second};

            // not a wall and hasn't been visited
            if (game_map[new_pos.first][new_pos.second] != '#' && visited.find(new_pos) == visited.end())
            {
                qu.push({new_pos, curr_dist + 1});
                visited[new_pos] = curr_dist + 1;
            }
        }

        visited[curr_pos] = curr_dist;
    }

    int cheat_count = 0;

    // go through correct path
    for (auto [pos, dist] : visited)
    {
        for (auto direction : directions)
        {
            // no collision for 2 cells
            std::pair<int, int> skip_pos = {pos.first + 2 * direction.first, pos.second + 2 * direction.second};

            // if the cell that is 2 cells away has been visited (valid path)
            if (visited.find(skip_pos) != visited.end())
            {
                // dist to skip cell - dist to current cell - 2 (for the 2 skipped cells)
                int dist_saved = visited[skip_pos] - dist - 2;
                if (dist_saved >= 100)
                    cheat_count++;
            }
        }
    }

    return cheat_count;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Unspecified input file\n";
        return -1;
    }

    std::ifstream input_file(argv[1]);
    std::string line;

    std::vector<std::string> game_map;
    std::pair<int, int> start_tile;

    int row = 0;
    while (std::getline(input_file, line))
    {
        int start_pos = line.find('S');
        if (start_pos != std::string::npos)
            start_tile = {row, start_pos};

        game_map.push_back(line);
        row++;
    }

    int cheat_count = bfs(game_map, start_tile.first, start_tile.second);

    std::cout << "Number of cheats that would save at least 100ps: " << cheat_count << std::endl;

    input_file.close();
    return 0;
}
