#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>

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
    int count = 0;

    while (std::getline(input_file, text))
    {
        std::stringstream ss(text);
        std::string word;
        std::vector<int> report;

        // turn report into vector
        while (ss >> word)
            report.push_back(stoi(word));

        bool increasing = report[1] > report[0];
        bool valid_report = true;

        // check for invalid report
        for (int i = 1; i < report.size(); i++)
        {
            int diff = std::abs(report[i] - report[i - 1]);

            if (diff < 1 || diff > 3)
            {
                valid_report = false;
                break;
            }

            if (report[i] > report[i - 1] && !increasing)
            {
                valid_report = false;
                break;
            } 

            if (report[i] < report[i - 1] && increasing)
            {
                valid_report = false;
                break;
            }
        }

        if (valid_report)
            count++;
    }

    std::cout << "Total safe reports: " << count << std::endl;

    input_file.close();
    return 0;
}
