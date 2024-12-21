#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <stack>

std::vector<std::string> filter_towels(std::vector<std::string> available_towels, std::string design)
{
    std::vector<std::string> result;
    
    for (auto towel : available_towels)
    {
        if (design.find(towel) != std::string::npos)
            result.push_back(towel);
    }
    
    return result;
}

bool check_if_possible(std::vector<std::string> available_towels, std::string design)
{
    int upper_limit = available_towels.size();
    int count = 0;

    // filter for towels that fit in the design
    std::vector<std::string> fit_towels = filter_towels(available_towels, design);
    if (fit_towels.size() < 1)
        return false;

    std::stack<std::string> st;
    st.push(design);

    // DFS
    while (!st.empty())
    {
        if (count == upper_limit)
            break;

        std::string curr_design = st.top();
        st.pop();

        for (auto towel : fit_towels)
        {
            if (curr_design == towel)
                return true;

            std::string curr_sub_design = curr_design.substr(0, towel.size());

            if (curr_sub_design == towel)
            {
                std::string curr_design_end = curr_design.substr(towel.size());
                st.push(curr_design_end);
            }
        }
        
        count++;
    }

    return false;
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
    std::vector<std::string> available_towels;
    std::vector<std::string> desired_designs;

    int possible_designs = 0;

    if (std::getline(input_file, text))
    {
        std::stringstream ss(text);
        std::string word;
        while (ss >> word)
        {
            if (word[word.size() - 1] == ',')
                word.pop_back();
            available_towels.push_back((std::string)word);
        }
    }

    std::getline(input_file, text); // skip empty line

    while (std::getline(input_file, text))
        desired_designs.push_back(text);

    for (int i = 0; i < desired_designs.size(); i++)
    {
        if (check_if_possible(available_towels, desired_designs[i]))
            possible_designs++;
    }

    std::cout << "Number of possible designs: " << possible_designs << std::endl;

    input_file.close();
    return 0;
}
