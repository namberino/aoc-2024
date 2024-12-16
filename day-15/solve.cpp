#include <iostream>
#include <fstream>
#include <vector>

std::pair<int, int> operator +(const std::pair<int, int>& x, const std::pair<int, int>& y)
{
    return std::make_pair(x.first + y.first, x.second + y.second);
}

std::pair<int, int> operator -(const std::pair<int, int>& x, const std::pair<int, int>& y)
{
    return std::make_pair(x.first - y.first, x.second - y.second);
}

void make_move(std::pair<int, int>& curr_coord, std::pair<int, int> move_coord, std::vector<std::string>& warehouse_map)
{
    std::pair<int, int> to_coord = curr_coord + move_coord;

    if (warehouse_map[to_coord.first][to_coord.second] == '#')
        return;

    if (warehouse_map[to_coord.first][to_coord.second] == '.')
    {
        warehouse_map[to_coord.first][to_coord.second] = warehouse_map[curr_coord.first][curr_coord.second];
        warehouse_map[curr_coord.first][curr_coord.second] = '.';
        curr_coord = to_coord;
        return;
    }

    // find all obstacles in current move direction
    std::pair<int, int> next_coord = to_coord;
    while (warehouse_map[next_coord.first][next_coord.second] == 'O')
    {
        next_coord = next_coord + move_coord;

        if (warehouse_map[next_coord.first][next_coord.second] == '#')
            return;
    }

    // if it gets to this point of the code, there's an empty tile behind all of the obstacles
    // move all obstacles in the current move direction
    while (next_coord != curr_coord)
    {
        warehouse_map[next_coord.first][next_coord.second] = 'O';
        next_coord = next_coord - move_coord;
    }

    warehouse_map[to_coord.first][to_coord.second] = warehouse_map[curr_coord.first][curr_coord.second];
    warehouse_map[curr_coord.first][curr_coord.second] = '.';
    curr_coord = to_coord;
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
    std::vector<std::string> warehouse_map;
    std::string move_list;
    std::pair<int, int> robot_coord;
    int curr_row = 0;

    // get map
    while (std::getline(input_file, text))
    {
        if (text == "")
            break;

        int pos = text.find('@');
        if (pos != std::string::npos)
            robot_coord = {curr_row, pos};

        
        warehouse_map.push_back(text);
        curr_row++;
    }

    // get movement list
    while (std::getline(input_file, text))
        move_list += text;

    for (auto move : move_list)
    {
        std::pair<int, int> move_coord;

        switch (move)
        {
            case '^': move_coord = {-1, 0}; break;
            case '>': move_coord = {0, 1}; break;
            case 'v': move_coord = {1, 0}; break;
            case '<': move_coord = {0, -1}; break;
            default: break;
        }

        make_move(robot_coord, move_coord, warehouse_map);
    }

    int box_gps = 0;

    for (int i = 0; i < warehouse_map.size(); i++)
    {
        for (int j = 0; j < warehouse_map[0].size(); j++)
        {
            if (warehouse_map[i][j] == 'O')
                box_gps += 100 * i + j;
        }
    }

    std::cout << "Sum of box GPS coords: " << box_gps << std::endl;

    input_file.close();
    return 0;
}
