#include <iostream>
#include <fstream>
#include <cstring>
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
    int sum = 0;

    while (std::getline(input_file, text))
    {
        // capture mul pattern
        // capture the numbers into 2 capture groups
        std::regex re("mul\\((\\d+),(\\d+)\\)");
        std::smatch matches;

        while (regex_search(text, matches, re))
        {
            // 1st capture group is the mul pattern
            // 2nd and 3rd capture groups are the individual numbers
            sum += stoi(matches[1]) * stoi(matches[2]);
            text = matches.suffix(); // move to succeeding part of the match
        }
    }

    std::cout << "Result of muls: " << sum << std::endl;

    input_file.close();
    return 0;
}
