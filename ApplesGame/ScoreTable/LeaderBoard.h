#pragma once
#include <string>
#include <vector>

namespace ApplesGame
{
    struct Record
    {
        std::string name;
        int score;
    };

    void BubbleSort(std::vector<Record> vector);
}
