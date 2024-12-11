#include <iostream>
#include <fstream>
#include <vector>
#include <map>

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
    std::map<std::string, std::vector<std::string> > ordering_rules;

    while (std::getline(input_file, text))
    {
        if (text.compare("") == 0)
            break;

        std::string page1;
        std::string page2;

        // little hacky but works because all pages are only 2 digits
        // if they aren't all 2 digits then use loops to split the string
        page1.push_back(text[0]);
        page1.push_back(text[1]);
        page2.push_back(text[3]);
        page2.push_back(text[4]);

        // append or create new item in map
        if (ordering_rules.find(page1) == ordering_rules.end())
        {
            std::vector<std::string> associate_pages;
            associate_pages.push_back(page2);
            ordering_rules[page1] = associate_pages;
        }
        else
        {
            ordering_rules[page1].push_back(page2);
        }
    }

    for (auto item : ordering_rules)
    {
        std::cout << item.first << " : ";
        for (auto element : item.second)
            std::cout << element << " ";
        std::cout << "\n";
    }

    input_file.close();
    return 0;
}
