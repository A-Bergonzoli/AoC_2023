#include "pypp.hpp" // https://github.com/A-Bergonzoli/pypp

#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

strings Parse()
{
    return pypp::splitFileLines("input.txt");
}

int ComputeTotalPoints(strings lines)
{
    int counter { 0 };
    int sum { 0 };

    for (auto& line : lines) {
        std::vector<int> winning_numbers_int {};
        std::vector<int> numbers_int {};

        line = pypp::split(line, ':')[1];
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
                counter++;
        }

        if (counter > 0) {
            sum += pow(2, counter - 1);
            counter = 0;
        }
    }

    return sum;
}

int main()
{
    auto lines = Parse();

    std::cout << "Total points: " << ComputeTotalPoints(lines) << std::endl;

    return 0;
}