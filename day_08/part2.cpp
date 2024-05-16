#include "pypp.hpp"

#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

using tuple_str = std::tuple<std::string, std::string>;

tuple_str AsTuple(const std::string& tuple_as_string)
{
    const auto left_option = pypp::splitThenGetAt(tuple_as_string, ',', 0);
    const auto right_option = pypp::splitThenGetAt(tuple_as_string, ',', 1);

    return std::make_tuple(
        left_option.substr(2, left_option.size()),
        right_option.substr(1, right_option.size() - 2));
}

class Solution {

public:
    void Parse(const std::string& file)
    {
        auto lines = pypp::splitFileLines(file);
        instructions_ = lines[0];

        for (int i = 1; i < lines.size(); ++i) {
            const auto key = pypp::splitThenGetAt(lines[i], ' ', 0);
            const auto rest = pypp::splitThenGetAt(lines[i], '=', 1);

            map_.insert({ key, AsTuple(rest) });

            if (key.ends_with('A'))
                starts_.push_back(key);
        }
    }

    char AdvanceInstructions()
    {
        instructions_idx_++;

        if (instructions_idx_ >= instructions_.length())
            instructions_idx_ = 0;

        return instructions_.at(instructions_idx_);
    }

    void ResetInstructions()
    {
        instructions_ = -1;
    }

    int GetHowManySteps(char move, std::string& key)
    {
        int steps { 0 };

        while (!key.ends_with('Z')) {
            key = (move == 'L') ? std::get<0>(map_[key]) : std::get<1>(map_[key]);
            move = this->AdvanceInstructions();
            steps++;
        }

        return steps;
    }

    std::string instructions_ {};
    std::vector<std::string> starts_ {};
    std::unordered_map<std::string, tuple_str> map_ {};
    int instructions_idx_ { -1 };
};

int main()
{
    Solution solution {};
    solution.Parse("input.txt");

    std::vector<int> steps {};
    for (auto start : solution.starts_) {
        steps.push_back(solution.GetHowManySteps(solution.AdvanceInstructions(), start));
        solution.ResetInstructions();
    }

    long prev_lcm { steps.front() };
    for (int i = 1; i < steps.size(); ++i)
        prev_lcm = std::lcm(steps[i], prev_lcm);

    std::cout << prev_lcm << std::endl;

    return 0;
}
