#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <cmath>

// instruction opcodes
#define ADV 0
#define BXL 1
#define BST 2
#define JNZ 3
#define BXC 4
#define OUT 5
#define BDV 6
#define CDV 7

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

    std::vector<int> reg_file;
    std::vector<int> program;
    std::string output_str;
    std::regex re("(\\d+)");

    while (std::getline(input_file, text))
    {
        if (text == "")
            break;

        std::smatch matches;
        regex_search(text, matches, re);
        reg_file.push_back(stoi(matches[1]));
    }

    while (std::getline(input_file, text))
    {
        std::smatch matches;
        while (regex_search(text, matches, re))
        {
            program.push_back(stoi(matches[0]));
            text = matches.suffix();
        }
    }

    for (int i = 0; i < program.size() - 1; i += 2)
    {
        int opcode = program[i];
        int operand = program[i + 1];
        int combo_op;

        // combo operand
        switch (operand)
        {
            // literal values
            case 0: combo_op = 0; break;
            case 1: combo_op = 1; break;
            case 2: combo_op = 2; break;
            case 3: combo_op = 3; break;

            // registers
            case 4: combo_op = reg_file[0]; break; // A
            case 5: combo_op = reg_file[1]; break; // B
            case 6: combo_op = reg_file[2]; break; // C

            // reserved
            case 7: break;

            default: break;
        }

        // opcode instructions
        switch (opcode)
        {
            // divide A with 2 raised to the power of combo operand and store to A
            case ADV:
            {
                int numerator = reg_file[0];
                int denominator = std::pow(2, combo_op);
                reg_file[0] = (int)(numerator / denominator);
                break;
            }
            
            // bitwise XOR B with literal operand and store to B
            case BXL:
            {
                int B_val = reg_file[1];
                reg_file[1] = B_val ^ operand;
                break;
            }

            // modulo combo operand with 8 and store to B
            case BST:
            {
                reg_file[1] = combo_op % 8;
                break;
            }

            // do nothing if A == 0
            // else, set instruction pointer to literal operand
            case JNZ:
            {
                if (reg_file[0] != 0)
                    i = operand - 2;
                break;
            }

            // bitwise XOR of B and C and store in B (ignores operand)
            case BXC:
            {
                reg_file[1] ^= reg_file[2];
                break;
            }

            // modulo combo operand with 8 and output the value
            case OUT:
            {
                output_str += std::to_string(combo_op % 8);
                output_str += ",";
                break;
            }

            // just like ADV but store in B
            case BDV:
            {
                int numerator = reg_file[0];
                int denominator = std::pow(2, combo_op);
                reg_file[1] = (int)(numerator / denominator);
                break;
            }

            // just like ADV but store in C
            case CDV:
            {
                int numerator = reg_file[0];
                int denominator = std::pow(2, combo_op);
                reg_file[2] = (int)(numerator / denominator);
                break;
            }
            
            default: break;
        }
    }

    output_str[output_str.size() - 1] = '\0';
    std::cout << "Computer output: " << output_str << std::endl;

    input_file.close();
    return 0;
}
