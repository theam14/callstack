#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

int minimumProcessorCount(std::vector<std::vector<int> > &data)
{
    size_t result = 0;

    if (!data.empty())
    {
        std::sort(std::begin(data), std::end(data),
                  [](const std::vector<int> &left, const std::vector<int> &right)
                  {
                      return (left[0] < right[0]) ||
                             ((left[0] == right[0]) && (left[1] < right[1]));
                  });

        std::list<std::vector<int> > callstack;

        for (const auto& task: data)
        {
            auto callstack_it = std::begin(callstack);

            while (callstack_it != std::end(callstack))
            {
                if ( (task[0] > (*callstack_it)[1]) ||
                     (task[1] < (*callstack_it)[0]) )
                {
                    callstack_it = callstack.erase(callstack_it);
                }
                else
                {
                    ++callstack_it;
                }
            }

            callstack.emplace_back(task);

            result = std::max(callstack.size(), result);
        }
    }

    return static_cast<int>(result);
}

int main(int argc, char** argv) 
{
    std::ifstream input_file(argv[1], std::ios::in);

    std::vector<std::vector<int> > data;

    int begin = 0;
    int end = 0;
    while (input_file >> begin >> end)
    {
        data.emplace_back(std::vector<int>(2));
        data.back()[0] = begin;
        data.back()[1] = end;
    }

    std::cout << "Result: "
              << minimumProcessorCount(data)
              << std::endl;

    return EXIT_SUCCESS;
}
