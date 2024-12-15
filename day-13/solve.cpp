#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

double get_2x2_determinant(double a, double b, double c, double d)
{
    return (a * d) - (c * b);
}

// cramer's rule for 2x2 matrix (AX = B)
std::pair<double, double> solve_sys_equations(std::vector<int> equation1, std::vector<int> equation2)
{
    double D = get_2x2_determinant(equation1[0], equation1[1], equation2[0], equation2[1]);
    double Dx = get_2x2_determinant(equation1[2], equation1[1], equation2[2], equation2[1]);
    double Dy = get_2x2_determinant(equation1[0], equation1[2], equation2[0], equation2[2]);

    if (D == 0)
        return {std::nan(""), std::nan("")};
    
    double x = Dx / D;
    double y = Dy / D;

    return {x, y};
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
    std::string button1, button2, prize, empty_line;

    int a_tokens = 3;
    int b_tokens = 1;
    int max_press = 100;

    int token_cost = 0;
    std::regex re("(\\d+).*(?:\\+|=)(\\d+)");

    while (std::getline(input_file, button1) && std::getline(input_file, button2) && std::getline(input_file, prize))
    {
        std::getline(input_file, empty_line);
        if (!empty_line.empty() && !(empty_line.compare("\n") == 0)) // handle last line and empty lines
            break;

        std::vector<int> equation1, equation2;
        std::smatch matches;

        // parse the equations
        while (regex_search(button1, matches, re))
        {
            equation1.push_back(stoi(matches[1]));
            equation2.push_back(stoi(matches[2]));
            button1 = matches.suffix();
        }
        while (regex_search(button2, matches, re))
        {
            equation1.push_back(stoi(matches[1]));
            equation2.push_back(stoi(matches[2]));
            button2 = matches.suffix();
        }
        while (regex_search(prize, matches, re))
        {
            equation1.push_back(stoi(matches[1]));
            equation2.push_back(stoi(matches[2]));
            prize = matches.suffix();
        }

        std::pair<double, double> solution = solve_sys_equations(equation1, equation2);

        // if not valid solution
        if (std::isnan(solution.first) || std::isnan(solution.second) ||
            solution.first >= max_press || solution.second >= max_press ||
            (int)solution.first != solution.first || (int)solution.second != solution.second
        )
            continue;

        token_cost += (solution.first * a_tokens) + (solution.second * b_tokens);
    }

    std::cout << "Total token cost: " << token_cost << std::endl;

    input_file.close();
    return 0;
}
