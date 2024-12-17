#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

// move forward = 1 point
// rotate (but not move forward) = 1000 points

// north, east, south, west
const int dir_row[] = {-1, 0, 1, 0};
const int dir_col[] = {0, 1, 0, -1};

// best-first search (prioritizes straight movement)
int dijkstra(std::vector<std::string>& maze, std::pair<int, int>& start, std::pair<int, int>& end)
{
    int rows = maze.size();
    int cols = maze[0].size();

    // priority queue to store the state (cost, row, col, direction)
    // direction is encoded as an integer from 0 to 3 (0 = north, 1 = east, 2 = south, 3 = west)
    // ensure the path with least cost is on top -> always explore the path with the least cost first
    std::priority_queue<std::tuple<int, int, int, int>, std::vector<std::tuple<int, int, int, int>>, std::greater<std::tuple<int, int, int, int>>> pq; // smallest first element will be on top of the queue

    // dist 3d vector to store the cost to get from the starting position to the row and col specified in the 3d vector
    // distances initialized to infinity (except the starting point for each direction)
    std::vector<std::vector<std::vector<int>>> dist(rows, std::vector<std::vector<int>>(cols, std::vector<int>(4, std::numeric_limits<int>::max())));

    // all 4 directions the starting position could be facing (0 to 3) has a cost of 0
    for (int i = 0; i < 4; i++)
    {
        dist[start.first][start.second][i] = 0;
        pq.push({0, start.first, start.second, i});
    }

    while (!pq.empty())
    {
        // get least costly state from pq
        auto [current_cost, curr_row, curr_col, dir] = pq.top();
        pq.pop();

        // if at the end, return the cost
        if (std::make_pair(curr_row, curr_col) == end)
            return current_cost;

        // move forward
        int new_row = curr_row + dir_row[dir];
        int new_col = curr_col + dir_col[dir];
        if (new_row > 0 && new_row < rows && new_col > 0 && new_col < cols && maze[new_row][new_col] != '#')
        {
            // valid move, add new cost and new position to dist and pq
            int new_cost = current_cost + 1;
            dist[new_row][new_col][dir] = new_cost;
            pq.push({new_cost, new_row, new_col, dir});
        }

        // rotate clockwise (90 degrees)
        int new_dir = (dir + 1) % 4;
        if (current_cost + 1000 < dist[curr_row][curr_col][new_dir]) // previously calculated cost in the new direction is higher (meaning cheaper way to get to curr_pos while facing new_dir)
        {
            dist[curr_row][curr_col][new_dir] = current_cost + 1000;
            pq.push({current_cost + 1000, curr_row, curr_col, new_dir});
        }

        // rotate counterclockwise (90 degrees)
        new_dir = (dir + 3) % 4;
        if (current_cost + 1000 < dist[curr_row][curr_col][new_dir])
        {
            dist[curr_row][curr_col][new_dir] = current_cost + 1000;
            pq.push({current_cost + 1000, curr_row, curr_col, new_dir});
        }
    }

    return -1; // no path exists
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

    std::vector<std::string> maze;
    std::pair<int, int> start_tile;
    std::pair<int, int> end_tile;
    int curr_row = 0;

    while (std::getline(input_file, text))
    {
        int start_pos = text.find('S');
        if (start_pos != std::string::npos)
            start_tile = {curr_row, start_pos};

        int end_pos = text.find('E');
        if (end_pos != std::string::npos)
            end_tile = {curr_row, end_pos};

        maze.push_back(text);

        curr_row++;
    }

    int min_score = dijkstra(maze, start_tile, end_tile) + 1000;
    std::cout << "Lowest score: " << min_score << std::endl;

    input_file.close();
    return 0;
}
