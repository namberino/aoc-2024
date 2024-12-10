#include <iostream>
#include <fstream>
#include <vector>

std::string match1 = "XMAS";
std::string match2 = "SAMX";

// match for "XMAS" pattern on row
int match_row(std::vector<std::vector<char> > words)
{
    int count = 0;

    for (int i = 0; i < words.size(); i++)
    {
        for (int j = 3; j < words[i].size(); j++)
        {
            std::string curr_word = "";

            for (int k = match1.size() - 1; k >= 0; k--)
                curr_word.push_back(words[i][j - k]);
            
            if (curr_word.compare(match1) == 0 || curr_word.compare(match2) == 0)
                count++;
        }
    }

    return count;
}

// match for "XMAS" pattern on columns
int match_col(std::vector<std::vector<char> > words)
{
    int count = 0;

    for (int i = 0; i < words[0].size(); i++)
    {
        for (int j = 3; j < words.size(); j++)
        {
            std::string curr_word = "";

            for (int k = match1.size() - 1; k >= 0; k--)
                curr_word.push_back(words[j - k][i]);
            
            if (curr_word.compare(match1) == 0 || curr_word.compare(match2) == 0)
                count++;
        }
    }

    return count;
}

// match for "XMAS" pattern on diagonals
int match_diag(std::vector<std::vector<char> > words)
{
    int count = 0;

    // "- 3" to avoid segfaults (because array out of bounds)
    for (int i = 0; i < words.size() - 3; i++)
    {
        for (int j = 0; j < words[0].size() - 3; j++)
        {
            std::string curr_word1 = "";
            std::string curr_word2 = "";

            // "\" diagonal (every 4 words)
            curr_word1.push_back(words[i][j]);
            curr_word1.push_back(words[i + 1][j + 1]);
            curr_word1.push_back(words[i + 2][j + 2]);
            curr_word1.push_back(words[i + 3][j + 3]);

            // "/" diagonal (every 4 words)
            curr_word2.push_back(words[i][j + 3]);
            curr_word2.push_back(words[i + 1][j + 2]);
            curr_word2.push_back(words[i + 2][j + 1]);
            curr_word2.push_back(words[i + 3][j]);

            if (curr_word1.compare(match1) == 0 || curr_word1.compare(match2) == 0)
                count++;

            if (curr_word2.compare(match1) == 0 || curr_word2.compare(match2) == 0)
                count++;
        }
    }

    return count;
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
    std::vector<std::vector<char> > words;

    // create 2d vector
    while (std::getline(input_file, text))
    {
        std::vector<char> line;
        for (int i = 0; i < text.size(); i++)
        {
            line.push_back(text[i]);
        }

        words.push_back(line);
    }

    int matches_row = match_row(words);
    int matches_col = match_col(words);
    int matches_diag = match_diag(words);

    std::cout << "Total \"XMAS\" occurences: " << matches_row + matches_col + matches_diag << std::endl;

    input_file.close();
    return 0;
}
