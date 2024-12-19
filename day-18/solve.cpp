#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>

std::pair<int, int> operator +(const std::pair<int, int>& x, const std::pair<int, int>& y)
{
    return std::make_pair(x.first + y.first, x.second + y.second);
}

std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up, right, down, left

std::vector<std::vector<int>> create_distance_map(std::vector<std::string> memory_space, std::pair<int, int> end_pos)
{
    int rows = memory_space.size();
    int cols = memory_space[0].size();

    std::vector<std::vector<int>> distance_map(rows, std::vector<int>(cols, -1));
    std::queue<std::pair<int, int>> qu;

    distance_map[end_pos.first][end_pos.second] = 0;
    qu.push(end_pos);

    while (!qu.empty())
    {
        int curr_row = qu.front().first;
        int curr_col = qu.front().second;
        qu.pop();

        for (auto direction : directions)
        {
            int new_row = curr_row + direction.first;
            int new_col = curr_col + direction.second;

            if (new_row >= 0 && new_row < rows &&
                new_col >= 0 && new_col < cols &&
                memory_space[new_row][new_col] != '#' &&
                distance_map[new_row][new_col] == -1)
            {
                distance_map[new_row][new_col] = distance_map[curr_row][curr_col] + 1;
                qu.push({new_row, new_col});
            }
        }
    }

    return distance_map;
}

int flood_fill(std::vector<std::string> memory_space, std::pair<int, int> start_pos, std::pair<int, int> end_pos)
{
    int rows = memory_space.size();
    int cols = memory_space[0].size();
    int steps = 0;
    std::vector<std::vector<int>> distance_map = create_distance_map(memory_space, end_pos);
    std::pair<int, int> curr_pos = start_pos;

    while (curr_pos != end_pos)
    {
        int curr_val = distance_map[curr_pos.first][curr_pos.second];

        for (auto direction : directions)
        {
            std::pair<int, int> new_pos = curr_pos + direction;

            if (new_pos.first >= 0 && new_pos.first < rows && new_pos.second >= 0 && new_pos.second < cols)
            {
                int new_val = distance_map[new_pos.first][new_pos.second];

                if (new_val < curr_val && new_val != -1)
                {
                    curr_pos = new_pos;
                    steps++;
                    break;
                }
            }
        }
    }

    return steps;
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

    int simulate_bytes = 1024;
    int memory_range = 70;
    std::pair<int, int> start_pos = {0, 0};
    std::pair<int, int> end_pos = {memory_range, memory_range};
    std::vector<std::string> memory_space;

    for (int i = 0; i <= memory_range; i++)
    {
        std::string temp;
        for (int j = 0; j <= memory_range; j++)
        {
            temp += ".";
        }
        memory_space.push_back(temp);
    }

    int count = 0;
    while (std::getline(input_file, text))
    {
        if (count == simulate_bytes)
            break;

        std::stringstream ss(text);
        std::vector<int> coord;

        for (int i; ss >> i;)
        {
            coord.push_back(i); 
            if (ss.peek() == ',')
                ss.ignore();
        }

        memory_space[coord[1]][coord[0]] = '#';
        count++;
    }

    int steps = flood_fill(memory_space, start_pos, end_pos);

    std::cout << "Lowest number of steps: " << steps << std::endl;

    input_file.close();
    return 0;
}
