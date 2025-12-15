#include "../Utils/Util.h"
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

// std::vector<std::string> split(
//     const std::string &ids, const std::string &delimiter)
// {
//     std::vector<std::string> freshIds;
//     size_t start = 0;
//     size_t end = ids.find(delimiter);

//     // spilt with delimiter
//     while (end != std::string::npos)
//     {
//         freshIds.push_back(ids.substr(start, end - start));
//         start = end + delimiter.length();
//         end = ids.find(delimiter, start);
//     }

//     freshIds.push_back(ids.substr(start));

//     return freshIds;
// }

int main()
{
    std::ifstream inputFile("input.txt");
    if (inputFile.fail())
    {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 0;
    }

    std::string line;
    // collecting roll of papers
    std::vector<std::pair<long, long>> freshRange;
    std::vector<long> availableRange;
    std::vector<std::pair<long, long>> *rangePointer = &freshRange;
    bool isFresh = true;
    while (std::getline(inputFile, line))
    {
        try
        {
            if (line == "")
            {
                isFresh = false;
            }
            else
            {
                if (isFresh)
                {
                    std::vector<std::string> freshR = split(line, "-");
                    if (freshR[0] >= freshR[1])
                    {
                        rangePointer->push_back(std::pair<long, long>(stol(freshR[1]), stol(freshR[0])));
                    }
                    else
                    {
                        rangePointer->push_back(std::pair<long, long>(stol(freshR[0]), stol(freshR[1])));
                    }
                }
                else
                {
                    availableRange.push_back(stol(line));
                }
            }
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "file has error at: " << line << std::endl;
        }
    }
    // 9459487872680
    // 1588359778224
    // result
    long freshIngredientsNumber = 0;

    std::vector<long> start;
    std::vector<long> endIndex;

    // sort the freshrange
    std::sort(freshRange.begin(), freshRange.end());

    std::pair<long, long> lastPair(freshRange[0].first, freshRange[0].second);
    long lower = lastPair.first;
    long upper = lastPair.second;
    std::cout << "frist check: " << lower << " end:  " << upper << std::endl;
    freshIngredientsNumber += upper - lower + 1;
    std::cout << "add : " << upper - lower + 1 << " total: " << freshIngredientsNumber << std::endl;
    for (size_t i = 1; i < freshRange.size(); i++)
    {
        std::cout << "current check range start: " << freshRange[i].first << " end:  " << freshRange[i].second << std::endl;
        std::cout << "before => lower: " << lower << " upper: " << upper << std::endl;
        // complete outside of range, add all
        // overlapping case 1 => [1 (2 3 4 5 ] 6 7 8 ), [(1 2 3 4 5] 6 7 8 )
        // freshRange[i].first >= lower &&  dont need
        if ((freshRange[i].second > upper && freshRange[i].first <= upper))
        {
            lower = upper + 1;
            upper = freshRange[i].second;
            std::cout << "start: " << lower << " end: " << upper << std::endl;
            freshIngredientsNumber += upper - lower + 1;
            std::cout << "add : " << upper - lower + 1 << " total: " << freshIngredientsNumber << std::endl;
        }
        // overlapping case 2 => [1 2 3 4 5 6 7 8](9 10 11)
        else if (freshRange[i].first > upper && freshRange[i].second > upper)
        {
            upper = freshRange[i].second;
            lower = freshRange[i].first;
            std::cout << "start: " << lower << " end: " << upper << std::endl;
            freshIngredientsNumber += upper - lower + 1;
            // std::cout << "final number: " << freshIngredientsNumber << std::endl;
            std::cout << "add : " << upper - lower + 1 << " total: " << freshIngredientsNumber << std::endl;
        }
        // overlapping case 3 => [1 (2 3 4 5 6 7 8)], nothing to add
        else if (freshRange[i].first >= lower && freshRange[i].second <= upper)
        {
            lower = upper;
            // upper = freshRange[i].second;
        }
        // edge case []()
        // else if (freshRange[i].first > upper && freshRange[i].second > upper && freshRange[i].first == freshRange[i].second)
        // {
        //     freshIngredientsNumber += 1;
        //     lower = freshRange[i].first;
        //     upper = freshRange[i].second;
        // }

        std::cout << "after => lower: " << lower << " upper: " << upper << std::endl;

        // if (freshRange[i].first > lastPair.first && freshRange[i].second < lastPair.second)
        // {
        //     // update start
        //     lower = freshRange[i].first;
        // }
        //   std::cout << "start: " << freshRange[i].first << " end: " << freshRange[i].second << std::endl;
        
    }
    //351957404557795 is wrong anwser
    //352681648086146
    std::cout << freshIngredientsNumber << std::endl;
}