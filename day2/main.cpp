#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> split(
    const std::string &ids, const std::string &delimiter)
{
    std::vector<std::string> elfIds;
    size_t start = 0;
    size_t end = ids.find(delimiter);

    // spilt with delimiter
    while (end != std::string::npos)
    {
        elfIds.push_back(ids.substr(start, end - start));
        start = end + delimiter.length();
        end = ids.find(delimiter, start);
    }

    elfIds.push_back(ids.substr(start));

    return elfIds;
}

std::vector<std::vector<int>> splitVectorWithSize(size_t size, std::vector<int> digits)
{
    std::vector<std::vector<int>> outVector;
    std::vector<int> tempVector;

    for (size_t i = 0; i < digits.size(); i++)
    {
        if ((i + 1) % size == 0)
        {
            // std::cout << "splited" << std::endl;
            tempVector.push_back(digits[i]);
            outVector.push_back(tempVector);
            tempVector.clear();
        }
        else
        {
            // std::cout << "added" << std::endl;
            tempVector.push_back(digits[i]);
        }
    }

    return outVector;
}

int checkNumberEqual(long origial, int x, int y, std::vector<int> digits)
{
    if (digits.size() == 1 || digits[x] != digits[y])
    {
        return 0;
    }

    if (y == digits.size() - 1)
    {
        return origial;
    }

    return checkNumberEqual(origial, x + 1, y + 1, digits);
}

bool isEvenSize(int size)
{
    return size % 2 == 0;
}

int sumOf(std::vector<int> numbers)
{
    int result = 0;
    for (int number : numbers)
    {
        result += number;
    }

    return result;
}

bool compare(std::vector<int> firstHalf, std::vector<int> secondHalf)
{
    for (size_t i = 0; i < firstHalf.size(); i++)
    {
        if (firstHalf[i] != secondHalf[i])
        {
            return false;
        }
    }

    return true;
}

long checkFakeId(long start, long end)
{
    long password = 0;
    // std::cout << "start: " << start << std::endl;
    while (start != end + 1)
    {
        std::vector<int> digits;
        long idToCheck = start;
        // std::cout << "checking id: " << idToCheck << std::endl;
        // split int into digits
        if (idToCheck > 0)
        {
            while (idToCheck > 0)
            {
                int digit = idToCheck % 10;
                digits.push_back(digit);
                idToCheck = idToCheck / 10;
            }
        }

        // check if all numbers are the same and add it up
        if (false)
        {
            // compares even number after the initial check, split even number apart and see if they are the same
            // part 1
            if (isEvenSize(digits.size()))
            {
                size_t middleIndex = digits.size() / 2;
                std::vector<int> firstHalf(digits.begin(), digits.begin() + middleIndex);
                std::vector<int> secondHalf(digits.begin() + middleIndex, digits.end());

                if (sumOf(firstHalf) == sumOf(secondHalf) && compare(firstHalf, secondHalf))
                {
                    password += start;
                }
            }
        }
        else
        {
            // part 2
            if (checkNumberEqual(start, 0, 1, digits))
            {
                password += start;
            }
            else
            {
                for (size_t i = 2; i < digits.size(); i++)
                {
                    bool foundSame = false;
                    // splitable will split vector into small vector and compare
                    if (digits.size() % i == 0)
                    {
                        std::vector<std::vector<int>> vectors;
                        vectors = splitVectorWithSize(i, digits);
                        // once split, compare each vector till the end, see if they repeated
                        for (size_t j = 0; j < vectors.size() - 1; j++)
                        {
                            if (!compare(vectors[j], vectors[j + 1]))
                            {
                                break;
                            }
                            // if compared to the last one and its the same, add this original number up
                            if (j + 1 == vectors.size() - 1 && compare(vectors[j], vectors[j + 1]))
                            {
                                password += start;
                                foundSame = true;
                                break;
                            }
                        }

                        if (foundSame)
                        {
                            break;
                        }
                    }
                }
            }
        }
        start++;
    }

    return password;
}

int main()
{
    std::string idGroups;
    std::ifstream inputFile("input.txt");

    if (inputFile.fail())
    {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        try
        {
            idGroups.append(line);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "file has error at: " << line << std::endl;
        }
    }

    std::string delimiter = ",";
    std::vector<std::string> ids = split(idGroups, delimiter);

    long password = 0;
    for (const std::string &id : ids)
    {
        std::vector<std::string> startEnd = split(id, "-");

        long start = std::abs(std::stol(startEnd[0]));
        long end = std::abs(std::stol(startEnd[1]));

        if (start < end)
        {
            password += checkFakeId(start, end);
        }
        else if (end < start)
        {
            password += checkFakeId(end, start);
        }
    }
    std::cout << "fake ids: " << password << std::endl;
    // 55647141923
    return 0;
}