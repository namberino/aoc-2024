#include <iostream>
#include <fstream>
#include <vector>

void move_guard(std::vector<std::string>& area_map, int& distinct_visited_pos, int guard_i, int guard_j)
{
    // mark starting pos as visited
    area_map[guard_i][guard_j] = 'x';
    distinct_visited_pos++;

    int move_index = 0;
    std::vector<std::vector<int> > move_dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up, right, down, left
    std::vector<int> move_dir = move_dirs[0];

    // move simulation
    while (true)
    {
        // make move
        guard_i += move_dir[0];
        guard_j += move_dir[1];

        // move out of the area
        if (guard_i < 0 || guard_j < 0 || guard_i >= area_map.size() || guard_j >= area_map[0].size())
            break;

        // run into obstacle
        if (area_map[guard_i][guard_j] != '#')
        {
            if (area_map[guard_i][guard_j] != 'x')
            {
                area_map[guard_i][guard_j] = 'x';
                distinct_visited_pos++;
            }
            
            continue;
        }

        // backtrack
        guard_i -= move_dir[0];
        guard_j -= move_dir[1];

        // change direction
        move_dir = move_dirs[++move_index % move_dirs.size()];
    }
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
    
    // area map
    std::vector<std::string> area_map;

    // for getting the guard index
    int counter = 0;
    int guard_index_i;
    int guard_index_j;

    // counter for the output
    int distinct_visited_pos = 0;

    while (std::getline(input_file, text))
    {
        if (text.find("^") != -1)
        {
            guard_index_j = text.find("^");
            guard_index_i = counter;
        }

        area_map.push_back(text);
        counter++;
    }

    move_guard(area_map, distinct_visited_pos, guard_index_i, guard_index_j);

    std::cout << "Number of distinct visited positions: " << distinct_visited_pos << std::endl;

    input_file.close();
    return 0;
}
