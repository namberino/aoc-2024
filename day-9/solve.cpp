#include <iostream>
#include <fstream>
#include <vector>

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
    long int fs_checksum = 0;
    int id_counter = 0;
    std::vector<std::string> disk_map; // store the layout of the filesystem

    while (std::getline(input_file, text))
    {
        for (int i = 0; i < text.size(); i++)
        {
            for (int j = 0; j < text[i] - '0'; j++)
                disk_map.push_back((i % 2 == 0) ? std::to_string(id_counter) : ".");

            if (i % 2 == 0)
                id_counter++;
        }
    }

    int left_off_pos = disk_map.size() - 1;

    for (int i = 0; i <= left_off_pos; i++)
    {
        // free space found
        if (disk_map[i].compare(".") == 0)
        {
            // find valid block from back
            for (int j = left_off_pos; j > i; j--)
            {
                // valid block
                if (disk_map[j].compare(".") != 0)
                {
                    // swap into free space
                    disk_map[i] = disk_map[j];
                    disk_map[j] = ".";

                    // save left off position
                    left_off_pos = --j;
                    break;
                }
            }
        }
    }

    // calculate checksum
    for (int i = 0; i < disk_map.size(); i++)
    {
        if (disk_map[i].compare(".") == 0)
            break;
        fs_checksum += i * stoi(disk_map[i]);
    }

    std::cout << "Filesystem checksum: " << fs_checksum << std::endl;

    input_file.close();
    return 0;
}
