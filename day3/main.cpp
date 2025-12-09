#include "../Utils/Util.h"
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

int findBiggestJoltage(std::vector<int> batteries)
{
    std::vector<int> firstVector(batteries.begin(), batteries.end() - 1);
    int max = firstVector[0];
    int indexOfMax = 0;
    for (size_t i = 0; i < firstVector.size(); i++)
    {
        if (firstVector[i] > max)
        {
            max = firstVector[i];
            indexOfMax = i;
        }
    }

    std::vector<int> secondVector(batteries.begin() + (indexOfMax + 1), batteries.end());
    int secMax = secondVector[0];
    for (size_t i = 0; i < secondVector.size(); i++)
    {
        if (secondVector[i] > secMax)
        {
            secMax = secondVector[i];
        }
    }

    char firstMax = max + '0';
    char secondMax = secMax + '0';
    std::string joltage = "";
    // add up together
    joltage += firstMax;
    joltage += secondMax;

    return stoi(joltage);
}

bool contains(std::vector<std::pair<int, int>> array, std::pair<int, int> target)
{
    for (std::pair<int, int> element : array)
    {
        if (element.first == target.first)
        {
            return true;
        }
    }

    return false;
}

std::vector<std::pair<int, int>> findMax12(std::vector<int> list, int reducableSize, int startIndex, std::vector<std::pair<int, int>> finalList)
{
    if (finalList.size() == 12)
    {
        return finalList;
    }

    if (reducableSize == 0)
    {
        finalList.push_back(std::pair<int, int>(startIndex, list[startIndex]));
        startIndex += 1;
    }
    else
    {
        std::cout << "start1: " << startIndex << " reducable: " << reducableSize << std::endl;
        // std::vector<int> sliced(list.begin() + startIndex, list.begin() + startIndex + reducableSize - 1);
        std::pair<int, int> maxPair(startIndex, list[startIndex]);
        for (size_t i = startIndex; i < startIndex + reducableSize + 1; i++)
        {
            std::cout << "index: " << i << std::endl;
            // && !contains(finalList, std::pair<int, int>(i, list[i]))
            /* code */
            if (list[i] > maxPair.second)
            {

                maxPair.first = i;
                maxPair.second = list[i];

                if (reducableSize < 0)
                {
                    reducableSize = 0;
                }
            }
        }
        int difference = maxPair.first - startIndex;
        reducableSize = reducableSize - difference;
        std::cout << "reduce: " << reducableSize << std::endl;
        startIndex = maxPair.first;
        std::cout << "difference: " << difference << std::endl;

        if (!contains(finalList, maxPair))
        {
            finalList.push_back(maxPair);
            startIndex += 1;
        }
    }

    std::cout << "start: " << startIndex << " reducable: " << reducableSize << std::endl;

    return findMax12(list, reducableSize, startIndex, finalList);
}

int main()
{
    std::vector<std::vector<int>> banks;
    std::ifstream inputFile("input.txt");
    if (inputFile.fail())
    {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 0;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        std::vector<int> batteries;
        try
        {
            for (char digital : line)
            {
                // std::cout << digital - '0' << std::endl;
                batteries.push_back(digital - '0'); // conver to int not ASCII
            }

            // sort array
            // std::sort(batteries.begin(), batteries.end(), std::greater<int>());
            banks.push_back(batteries);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "file has error at: " << line << std::endl;
        }
    }

    // output banks
    long finalJoltage = 0;
    for (std::vector<int> battery : banks)
    {
        std::vector<std::pair<int, int>> numbers;

        for (int number : battery)
        {
            std::cout << number << ", ";
        }
        std::cout << std::endl;

        numbers = findMax12(battery, battery.size() - 12, 0, numbers);
        std::sort(numbers.begin(), numbers.end());
        std::string str = "";
        for (std::pair<int, int> number : numbers)
        {
            char num = number.second + '0';
            str += num;
            /* code */
            std::cout << number.second << ", ";
        }

        long realNum = stol(str);
        std::cout << "number long: " << realNum << std::endl;

        finalJoltage += realNum;
        std::cout << std::endl;
    }

    std::cout << "final: " << finalJoltage << std::endl;

    return 0; // finished
}