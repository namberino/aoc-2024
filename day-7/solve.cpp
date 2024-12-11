#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

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
    long long int total_calibs = 0;

    while (std::getline(input_file, text))
    {
        std::stringstream ss(text);
        std::string number;
        std::vector<int> equation_nums;
        long long int calib_val;

        while (ss >> number)
        {
            if (number[number.size() - 1] == ':')
            {
                number.erase(number.end() - 1);
                calib_val = stol(number);
                continue;
            }

            equation_nums.push_back(stoi(number));
        }

        // permutate each possibilities
        // might use bitmask to permutate
        // 0 = '+', 1 = '*'

        // there's n - 1 operators in an equation with n operands
        // 2 operators '+' and '*' means there's 2 ^ (n - 1) permutations
        for (int i = 0; i < std::pow(2, (equation_nums.size() - 1)); i++) // loop through each permutation
        {
            long long int op_res = equation_nums[0];
            int tnum = i;

            // bitwise thing-a-ma-jig here
            for (int j = 1; j < equation_nums.size(); j++) // loop through each operand
            {
                bool is_add = (tnum & 1) == 0;

                if (is_add)
                    op_res += equation_nums[j];
                else
                    op_res *= equation_nums[j];
                
                tnum >>= 1;
            }

            // found valid equation
            if (op_res == calib_val)
            {
                total_calibs += op_res;
                break;
            }
        }
    }

    std::cout << "Total calibration result: " << total_calibs << std::endl;

    input_file.close();
    return 0;
}
