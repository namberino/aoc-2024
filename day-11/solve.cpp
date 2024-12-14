#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

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
    int stone_num = 0;
    std::vector<std::string> stones;

    while (std::getline(input_file, text))
    {
        std::stringstream ss(text);
        std::string stone;

        while (ss >> stone)
            stones.push_back(stone);
    }

    /*
     * Rule (choose first applicable one):
     * - if is number 0, replace with number 1
     * - if has even number of digits, split in half (remove leading 0s)
     * - if the above rules aren't applicable, old number * 2024
     */

    int blink_times;
    std::cout << "Enter blink times: ";
    scanf("%d", &blink_times);

    for (int i = 0; i < blink_times; i++)
    {
        std::cout << "Blink number " << i << std::endl;
        std::vector<std::string> new_stones;
        for (int j = 0; j < stones.size(); j++)
        {
            if (stones[j] == "0")
            {
                new_stones.push_back("1");
            }
            else if (stones[j].size() % 2 == 0)
            {
                std::string left_stone = stones[j].substr(0, stones[j].size() / 2);
                std::string right_stone = stones[j].substr(stones[j].size() / 2);

                // note to self: insert into vectors on these kinds of problems is slow as heck
                new_stones.push_back(std::to_string(std::stoll(left_stone)));
                new_stones.push_back(std::to_string(std::stoll(right_stone)));
            }
            else
            {
                new_stones.push_back(std::to_string(std::stoll(stones[j]) * 2024));
            }
        }

        stones = std::move(new_stones);
    }

    stone_num = stones.size();
    std::cout << "Number of stones after blinking " << blink_times << " times: " << stone_num << std::endl;

    input_file.close();
    return 0;
}
