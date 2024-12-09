#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <cmath>

int partition(std::vector<int>& vect, int low, int high)
{
    int pivot = vect[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (vect[j] <= pivot)
        {
            i++;
            std::swap(vect[i], vect[j]);
        }
    }

    std::swap(vect[i + 1], vect[high]);

    return i + 1;
}

void quicksort(std::vector<int>& vect, int low, int high)
{
    if (low < high)
    {
        int pi = partition(vect, low, high);

        quicksort(vect, low, pi - 1);
        quicksort(vect, pi + 1, high);
    }
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
    std::vector<int> v1;
    std::vector<int> v2;

    // get the input file data and put them into 2 vectors
    while (std::getline(input_file, text))
    {
        std::stringstream ss(text);
        std::string word;
        int c = 1;
        
        while (ss >> word)
        {
            if (c % 2 != 0)
                v1.push_back(stoi(word));
            else
                v2.push_back(stoi(word));

            c++;
        }
    }
    
    quicksort(v1, 0, v1.size() - 1);
    quicksort(v2, 0, v2.size() - 1);

    int distance = 0;

    for (int i = 0; i < v2.size(); i++)
    {
        distance += std::abs(v1[i] - v2[i]);
    }

    std::cout << "Total distance: " << distance << std::endl;

    input_file.close();
    return 0;
}
