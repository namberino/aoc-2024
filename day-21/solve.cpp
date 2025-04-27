#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

static std::string cache_key(const std::string& seq, int depth)
{
    // unique key for each sequence and depth
    return seq + "|" + std::to_string(depth);
}

// map of all the best moves from 1 location to another
static const std::map<std::pair<char,char>, std::string> paths = {
    {{'A','0'}, "<A"},    {{'0','A'}, ">A"},
    {{'A','1'}, "^<<A"},  {{'1','A'}, ">>vA"},
    {{'A','2'}, "<^A"},   {{'2','A'}, "v>A"},
    {{'A','3'}, "^A"},    {{'3','A'}, "vA"},
    {{'A','4'}, "^^<<A"}, {{'4','A'}, ">>vvA"},
    {{'A','5'}, "<^^A"},  {{'5','A'}, "vv>A"},
    {{'A','6'}, "^^A"},   {{'6','A'}, "vvA"},
    {{'A','7'}, "^^^<<A"},{{'7','A'}, ">>vvvA"},
    {{'A','8'}, "<^^^A"}, {{'8','A'}, "vvv>A"},
    {{'A','9'}, "^^^A"},  {{'9','A'}, "vvvA"},
    {{'0','1'}, "^<A"},   {{'1','0'}, ">vA"},
    {{'0','2'}, "^A"},    {{'2','0'}, "vA"},
    {{'0','3'}, "^>A"},   {{'3','0'}, "<vA"},
    {{'0','4'}, "^<^A"},  {{'4','0'}, ">vvA"},
    {{'0','5'}, "^^A"},   {{'5','0'}, "vvA"},
    {{'0','6'}, "^^>A"},  {{'6','0'}, "<vvA"},
    {{'0','7'}, "^^^<A"}, {{'7','0'}, ">vvvA"},
    {{'0','8'}, "^^^A"},  {{'8','0'}, "vvvA"},
    {{'0','9'}, "^^^>A"}, {{'9','0'}, "<vvvA"},
    {{'1','2'}, ">A"},    {{'2','1'}, "<A"},
    {{'1','3'}, ">>A"},   {{'3','1'}, "<<A"},
    {{'1','4'}, "^A"},    {{'4','1'}, "vA"},
    {{'1','5'}, "^>A"},   {{'5','1'}, "<vA"},
    {{'1','6'}, "^>>A"},  {{'6','1'}, "<<vA"},
    {{'1','7'}, "^^A"},   {{'7','1'}, "vvA"},
    {{'1','8'}, "^^>A"},  {{'8','1'}, "<vvA"},
    {{'1','9'}, "^^>>A"}, {{'9','1'}, "<<vvA"},
    {{'2','3'}, ">A"},    {{'3','2'}, "<A"},
    {{'2','4'}, "<^A"},   {{'4','2'}, "v>A"},
    {{'2','5'}, "^A"},    {{'5','2'}, "vA"},
    {{'2','6'}, "^>A"},   {{'6','2'}, "<vA"},
    {{'2','7'}, "<^^A"},  {{'7','2'}, "vv>A"},
    {{'2','8'}, "^^A"},   {{'8','2'}, "vvA"},
    {{'2','9'}, "^^>A"},  {{'9','2'}, "<vvA"},
    {{'3','4'}, "<<^A"},  {{'4','3'}, "v>>A"},
    {{'3','5'}, "<^A"},   {{'5','3'}, "v>A"},
    {{'3','6'}, "^A"},    {{'6','3'}, "vA"},
    {{'3','7'}, "<<^^A"}, {{'7','3'}, "vv>>A"},
    {{'3','8'}, "<^^A"},  {{'8','3'}, "vv>A"},
    {{'3','9'}, "^^A"},   {{'9','3'}, "vvA"},
    {{'4','5'}, ">A"},    {{'5','4'}, "<A"},
    {{'4','6'}, ">>A"},   {{'6','4'}, "<<A"},
    {{'4','7'}, "^A"},    {{'7','4'}, "vA"},
    {{'4','8'}, "^>A"},   {{'8','4'}, "<vA"},
    {{'4','9'}, "^>>A"},  {{'9','4'}, "<<vA"},
    {{'5','6'}, ">A"},    {{'6','5'}, "<A"},
    {{'5','7'}, "<^A"},   {{'7','5'}, "v>A"},
    {{'5','8'}, "^A"},    {{'8','5'}, "vA"},
    {{'5','9'}, "^>A"},   {{'9','5'}, "<vA"},
    {{'6','7'}, "<<^A"},  {{'7','6'}, "v>>A"},
    {{'6','8'}, "<^A"},   {{'8','6'}, "v>A"},
    {{'6','9'}, "^A"},    {{'9','6'}, "vA"},
    {{'7','8'}, ">A"},    {{'8','7'}, "<A"},
    {{'7','9'}, ">>A"},   {{'9','7'}, "<<A"},
    {{'8','9'}, ">A"},    {{'9','8'}, "<A"},
    {{'<','^'}, ">^A"},   {{'^','<'}, "v<A"},
    {{'<','v'}, ">A"},    {{'v','<'}, "<A"},
    {{'<','>'}, ">>A"},   {{'>','<'}, "<<A"},
    {{'<','A'}, ">>^A"},  {{'A','<'}, "v<<A"},
    {{'^','v'}, "vA"},    {{'v','^'}, "^A"},
    {{'^','>'}, "v>A"},   {{'>','^'}, "<^A"},
    {{'^','A'}, ">A"},    {{'A','^'}, "<A"},
    {{'v','>'}, ">A"},    {{'>','v'}, "<A"},
    {{'v','A'}, "^>A"},   {{'A','v'}, "<vA"},
    {{'>','A'}, "^A"},    {{'A','>'}, "vA"}
};

int get_seq_len(const std::string& seq, int depth);

// get cost to move from current->next at given depth
int get_move_count(char current, char next, int depth)
{
    if (current == next)
        return 1;

    auto it = paths.find({current, next});

    if (it == paths.end())
    {
        std::cerr << "No path for " << current << "->" << next << "\n";
        exit(1);
    }

    return get_seq_len(it->second, depth - 1);
}

int get_seq_len(const std::string& seq, int depth)
{
    std::string key = cache_key(seq, depth);

    int length = 0;
    if (depth == 0)
    {
        length = static_cast<int>(seq.size());
    }
    else
    {
        char current = 'A';
        for (char next : seq)
        {
            length += get_move_count(current, next, depth);
            current = next;
        }
    }

    return length;
}

int code_to_int(const std::string& code)
{
    std::string digits;

    for (char c : code)
    {
        if (std::isdigit(static_cast<unsigned char>(c)))
            digits += c;
    }
    
    return digits.empty() ? 0 : std::stoi(digits);
}

int calc_score(const std::string& code, int robots)
{
    int numeric = code_to_int(code);
    int length  = get_seq_len(code, robots);
    return numeric * length;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Unspecified input file\n";
        return -1;
    }

    std::ifstream input_file(argv[1]);
    std::string line;

    std::vector<std::string> codes;
    int complexity_sum = 0;

    while (std::getline(input_file, line))
        codes.push_back(line);

    for (const auto& code : codes)
        complexity_sum += calc_score(code, 3);

    std::cout << "Sum of the complexities of the five codes: " << complexity_sum << std::endl;

    input_file.close();
    return 0;
}
