#include <iostream>
#include <fstream>
#include <cstring>

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

    while (std::getline(input_file, text))
    {
        std::stringstream ss(text);
        std::string word;
        int c = 1;
        
        while (ss >> word)
        {
            if (c % 2 != 0)
                v1.push_back(stoi(word));
            else
                v2.push_back(stoi(word));

            c++;
        }
    }

    input_file.close();
    return 0;
}
