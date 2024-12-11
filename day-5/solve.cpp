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
    int sum_mid = 0;

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

    // thank god it continues reading where it left off in the file
    while (std::getline(input_file, text))
    {
        std::vector<int> update_pages;

        // again, a bit hacky but there's only 2 digits in the page number soooooo
        for (int i = 1; i < text.size(); i += 3)
        {
            std::string num;
            num.push_back(text[i - 1]);
            num.push_back(text[i]);

            update_pages.push_back(stoi(num));
        }

        int mid_index = update_pages.size() / 2;
        bool valid_update_list = true;

        // no need to check the last element
        for (int i = 0; i < update_pages.size() - 1; i++)
        {
            int current_num = update_pages[i];
            std::vector<std::string> curr_page_rules = ordering_rules[std::to_string(current_num)];

            // iterate through the rest of the vector
            for (int j = i + 1; j < update_pages.size(); j++)
            {
                // check if current page number is in the map
                if (std::find(curr_page_rules.begin(), curr_page_rules.end(), std::to_string(update_pages[j])) == curr_page_rules.end())
                {
                    valid_update_list = false;
                    break;
                }
            }

            if (!valid_update_list)
                break;
        }

        if (valid_update_list)
            sum_mid += update_pages[mid_index];
    }

    std::cout << "Sum of middle page in update lists: " << sum_mid << std::endl;

    input_file.close();
    return 0;
}
