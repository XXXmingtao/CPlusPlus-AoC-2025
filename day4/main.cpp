#include "../Utils/Util.h"
#include <string>
#include <algorithm>
#include <utility>
#include <vector>

int checkRollPaper(int direction, int x, int y, std::vector<std::vector<char>> printingDeparment)
{
    int xSize = printingDeparment.size();
    int ySize = printingDeparment[0].size();
    switch (direction)
    {
    case 7:
        if (x - 1 < 0 || y - 1 < 0)
        {
            return 0;
        }
        return printingDeparment[x - 1][y - 1] == '@';
    case 8:
        if (x - 1 < 0)
        {
            return 0;
        }
        return printingDeparment[x - 1][y] == '@';
    case 9:
        if (x - 1 < 0 || y + 1 >= ySize)
        {
            return 0;
        }
        return printingDeparment[x - 1][y + 1] == '@';
    case 6:
        if (y + 1 >= ySize)
        {
            return 0;
        }
        return printingDeparment[x][y + 1] == '@';
    case 3:
        if (x + 1 >= xSize || y + 1 >= ySize)
        {
            return 0;
        }
        return printingDeparment[x + 1][y + 1] == '@';
    case 2:
        if (x + 1 >= xSize)
        {
            return 0;
        }
        return printingDeparment[x + 1][y] == '@';
    case 1:
        if (x + 1 >= xSize || y - 1 < 0)
        {
            return 0;
        }
        return printingDeparment[x + 1][y - 1] == '@';
    case 4:
        if (y - 1 < 0)
        {
            return 0;
        }
        return printingDeparment[x][y - 1] == '@';
    default:
        return 8;
        break;
    }
}

int clean(int originalSize, std::vector<std::pair<int, int>> unremoveable, int finalCleaned, std::vector<std::vector<char>> printingDepartment, std::vector<int> directions)
{
    originalSize = unremoveable.size();

    for (auto itera = unremoveable.begin(); itera != unremoveable.end();)
    {
        // std::cout << " latest size: " << unremoveable.size() << std::endl;

        int aroundPaper = 0;
        for (int direction : directions)
        {
            aroundPaper += checkRollPaper(direction, itera->first, itera->second, printingDepartment);
        }

        if (aroundPaper < 4)
        {
            printingDepartment[itera->first][itera->second] = 'X';
            finalCleaned += 1;
            itera = unremoveable.erase(itera);
        }
        else //
        {
            itera++;
        }
    }

    if (unremoveable.size() == originalSize)
    {
        return finalCleaned;
    }

    return clean(originalSize, unremoveable, finalCleaned, printingDepartment, directions);
}

int main()
{
    // 8 of directions
    std::vector<int> directions{7, 8, 9, 6, 3, 2, 1, 4};

    std::ifstream inputFile("input.txt");
    if (inputFile.fail())
    {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 0;
    }

    std::string line;
    // collecting roll of papers
    std::vector<std::vector<char>> printingDepartment;
    while (std::getline(inputFile, line))
    {
        std::vector<char> row;
        try
        {
            for (char character : line)
            {
                row.push_back(character);
            }
            printingDepartment.push_back(row);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "file has error at: " << line << std::endl;
        }
    }

    // department content
    std::vector<std::pair<int, int>> unremoveable;

    int totalRollPaper = 0;
    for (size_t i = 0; i < printingDepartment.size(); i++)
    {
        for (size_t j = 0; j < printingDepartment[i].size(); j++)
        {
            // checking around paper
            int aroundPaper = 0;

            if (printingDepartment[i][j] == '@')
            {
                for (int direction : directions)
                {
                    aroundPaper += checkRollPaper(direction, i, j, printingDepartment);
                }
                if (aroundPaper < 4)
                {
                    totalRollPaper += 1;
                    printingDepartment[i][j] = 'X';
                }
                else
                {
                    // push back this unremoveable for later use
                    unremoveable.push_back(std::pair(i, j));
                }
            }
        }
    }

    totalRollPaper += clean(unremoveable.size(), unremoveable, 0, printingDepartment, directions);

    for (size_t i = 0; i < printingDepartment.size(); i++)
    {
        for (size_t j = 0; j < printingDepartment[i].size(); j++)
        {
            // std::cout << printingDepartment[i][j];
        }
        // std::cout << std::endl;
        /* code */
    }

    std::cout << totalRollPaper << std::endl;
}
