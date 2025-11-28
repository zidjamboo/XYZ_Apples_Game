#include "LeaderBoard.h"

#include <iterator>

namespace ApplesGame
{
    void BubbleSort(std::vector<Record> vector)
    {
        for (size_t i = 0; i < vector.size(); i++)
        {
            for (size_t j = i + 1; i < vector.size(); i++)
            {
                if (vector[i].score > vector[j].score)
                {
                    Record& tmp = vector[i];
                    vector[i] = vector[j];
                    vector[j] = tmp;
                }
            }
        }
    }
}
