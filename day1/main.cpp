#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Utils/LinkedList.h"

int main()
{
    // init dial
    LinkedList<int> dial;
    for (size_t i = 0; i < 100; i++)
    {
        dial.add_back(i);
    }

    std::vector<std::string> instructions;
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
            instructions.push_back(line);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "file has error at: " << line << std::endl;
        }
    }

    int password;
    Node<int> *current = dial.head;
    // go to starting position
    while (current->data != 50)
    {
        current = current->next;
    }

    for (std::string instruction : instructions)
    {
        char direction = instruction.at(0);
        int move = stoi(instruction.substr(1));
        std::cout << "direction: " << direction << " moves: " << move << std::endl;

        if (direction == 'L')
        {
            // move left
            for (size_t i = 0; i < move; i++)
            {
                current = current->prev;
                if (current->data == 0)
                {
                    password++;
                }
            }
        }
        else if (direction == 'R')
        {
            // move right
            for (size_t i = 0; i < move; i++)
            {
                current = current->next;
                if (current->data == 0)
                {
                    password++;
                }
            }
        }

        std::cout << "moved to: " << current->data << std::endl;
    }

    std::cout << "password: " << password << std::endl;

    dial.~LinkedList();

    return 0;
}
