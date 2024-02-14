#include "pypp.hpp" // https://github.com/A-Bergonzoli/pypp

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

strings Parse()
{
    return pypp::splitFileLines("input.txt");
}

int GetWinningNumbers(typename std::vector<std::string>::reverse_iterator& it)
{
    int wins { 0 };
    std::vector<int> winning_numbers_int {};
    std::vector<int> numbers_int {};

    auto line = pypp::split(*it, ':')[1];
    const auto winning_numbers_s = pypp::split(pypp::split(line, '|')[0], ' ');
    const auto numbers_s = pypp::split(pypp::split(line, '|')[1], ' ');

    winning_numbers_int.reserve(winning_numbers_s.size());
    numbers_int.reserve(numbers_s.size());
    for (const auto& num : winning_numbers_s)
        winning_numbers_int.push_back(std::stoi(num));
    for (const auto& num : numbers_s)
        numbers_int.push_back(std::stoi(num));

    std::set<int> winning_numbers_set(winning_numbers_int.begin(), winning_numbers_int.end());
    for (const auto number : numbers_int) {
        if (winning_numbers_set.contains(number))
            wins++;
    }

    return wins;
}

int ComputeTotalNumScratchCards(strings lines)
{
    collections::Counter<int> map {};
    int card_id { lines.size() - 1 };

    for (auto it = std::rbegin(lines); it != std::rend(lines); ++it, --card_id) {

        std::cout << "Analyzing stracth card #: " << card_id << std::endl;

        map[card_id] = 1;

        auto wins = GetWinningNumbers(it);

        for (; wins > 0; --wins)
            map[card_id] += map[card_id + wins];
    }
    return map.total();
}

int main()
{
    auto lines = Parse();

    std::cout << ComputeTotalNumScratchCards(lines) << std::endl;

    return 0;
}