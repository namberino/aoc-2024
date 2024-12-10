#include <iostream>
#include <fstream>

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

    }

    input_file.close();
    return 0;
}
