#include "../Utils/Util.h"
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <regex>

long mathIt(long first, long second, std::string op)
{
    if (op == "*")
    {
        return first * second;
    }

    if (op == "+")
    {
        return first + second;
    }

    return 0;
}

long operating(std::vector<std::string> numbers, size_t index, std::string op, long result)
{
    if (index == numbers.size() - 1)
    {
        return result;
    }

    std::cout << result << op << numbers[index + 1] << std::endl;

    result = mathIt(result, stol(numbers[index + 1]), op);

    return operating(numbers, index + 1, op, result);
}

int main()
{
    std::vector<std::vector<std::string>> outputs;
    std::vector<std::string> operators;
    std::ifstream inputFile("input.txt");

    // std::string test = "123";
    // std::cout << test[3] << std::endl;

    if (inputFile.fail())
    {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> wholeFile;
    while (std::getline(inputFile, line))
    {
        wholeFile.push_back(line);

        try
        {
            std::vector<std::string> numbers;
            std::string temp = "";
            int startIndex = 0;
            char c = line[startIndex];
            while (c == ' ')
            {
                startIndex++;
                c = line[startIndex];
            }

            // std::cout << "start index: " << startIndex << std::endl;
            for (size_t i = startIndex; i < line.size(); i++)
            {
                // push digit
                if (line[i] == ' ')
                {
                    continue;
                }
                else
                {
                    temp += line[i];
                }

                // see if next is ' '
                if (line[i + 1] == ' ')
                {
                    numbers.push_back(temp);
                    // std::cout << temp << std::endl;
                    temp = "";
                }

                if (i == line.size() - 1 && line[i] != ' ')
                {
                    numbers.push_back(temp);
                    // std::cout << temp << std::endl;
                }
            }
            outputs.push_back(numbers);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "file has error at: " << line << std::endl;
        }
    }

    //  assign opeartors
    operators = outputs[outputs.size() - 1];
    outputs.pop_back();
    std::vector<std::vector<std::string>> part2Array;
    std::cout << "whole file: " << std::endl;
    std::regex number_pattern("^ +$");
    std::vector<std::string> columNumber;

    for (size_t i = 0; i < wholeFile[0].size(); i++)
    {
        std::string number = "";
        for (size_t j = 0; j < wholeFile.size() - 1; j++)
        {
            number += wholeFile[j][i];
        }

        if (std::regex_match(number, number_pattern))
        {
            part2Array.push_back(columNumber);
            columNumber.clear();
            std::cout << std::endl;
        }
        else
        {
            number.erase(std::remove_if(number.begin(), number.end(), ::isspace), number.end());
            columNumber.push_back(number);
            std::cout << stol(number) << ", ";
        }

        if (i == wholeFile[0].size() - 1 && !std::regex_match(number, number_pattern))
        {
            part2Array.push_back(columNumber);
            std::cout << std::endl;
        }
    }

    for (std::vector<std::string> numbers : part2Array)
    {
        for (std::string number : numbers)
        {
            std::cout << number << ", ";
        }
        std::cout << std::endl;
        /* code */
    }

    std::cout << "size of part 2: " << part2Array.size() << std::endl;

    // for (size_t i = 0; i < outputs[2].size(); i++)
    // {
    //     std::cout << outputs[2][i] << ", ";
    // }
    // std::cout << std::endl;

    // size_t column = 0;
    std::vector<std::vector<std::string>> numberMap;
    size_t length = 0;
    std::cout << "length: " << outputs[1].size() << std::endl;

    // TODO why replace column with 0, would only add up to 10 columns???
    for (size_t column = 0; column < outputs[0].size(); column++)
    {
        std::vector<std::string> inputNumber;
        for (size_t row = 0; row < outputs.size(); row++)
        {
            std::cout << stol(outputs[row][column]) << ", ";
            inputNumber.push_back(outputs[row][column]);
        }
        std::cout << std::endl;
        numberMap.push_back(inputNumber);
    }

    std::cout << "map size: " << numberMap.size() << std::endl;

    // for (size_t i = 0; i < numberMap.size(); i++)
    // {
    //     std::
    //     /* code */
    // }

    int operatorIndex = 0;
    long final = 0;
    for (std::vector<std::string> numbers : part2Array)
    {
        long result;
        result = stol(numbers[0]);

        std::cout << "operating: ";
        for (std::string number : numbers)
        {
            std::cout << number << ", ";
        }
        std::cout << std::endl;

        result = operating(numbers, 0, operators[operatorIndex], result);
        final += result;
        std::cout << "result: " << result << std::endl;
        operatorIndex++;
    }

    std::cout << "final result: " << final << std::endl;
}