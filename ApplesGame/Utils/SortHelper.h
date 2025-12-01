#pragma once
#include <vector>

namespace ApplesGame
{
    template <typename T>
    void BubbleSort(std::vector<T>& vector)
    {
        for (size_t i = 0; i < vector.size(); i++)
        {
            for (size_t j = i + 1; j < vector.size(); j++)
            {
                if (vector[i].score < vector[j].score)
                {
                    std::swap(vector[i], vector[j]);
                }
            }
        }
    }
}
