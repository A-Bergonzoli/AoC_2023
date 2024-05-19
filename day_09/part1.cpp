#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "pypp.hpp"

using vectors = std::vector<std::vector<int>>;

constexpr auto expected { 1974913025 };

class Solution {
public:
    void Parse(const std::string& file_name)
    {
        auto lines = pypp::splitFileLines(file_name);
        for (const auto& line : lines) {
            std::vector<int> history_entries {};
            auto entries_as_string = pypp::split(line, ' ');
            for (const auto& elem : entries_as_string)
                history_entries.push_back(std::stoi(elem));

            histories_.push_back(history_entries);
        }
    }

    int ExtrapolateNext(const std::vector<int>& elems)
    {
        // base case
        if (std::ranges::all_of(elems, [](auto elem) { return elem == 0; }))
            return elems[elems.size() - 1];

        std::vector<int> new_elems {};
        for (int i = 1; i < elems.size(); ++i)
            new_elems.push_back(elems[i] - elems[i - 1]);

        return elems[elems.size() - 1] + ExtrapolateNext(new_elems);
    }

    vectors histories_ {};
};

int main()
{
    int result { 0 };

    Solution solution {};
    solution.Parse("input.txt");
    for (auto history : solution.histories_)
        result += solution.ExtrapolateNext(history);

    std::cout << "Sum of extrapolated values: " << result << "\n";

    assert(expected == result);
    return 0;
}