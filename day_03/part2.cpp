#include "pypp.hpp" // https://github.com/A-Bergonzoli/pypp

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct Number;

using Numbers = std::vector<Number>;
using pairs = std::vector<std::pair<int, int>>;
using strings = std::vector<std::string>;

struct Number {
    std::string number {};
    std::pair<int, int> start_position {};
    int sz {};
    std::vector<int> range_over_x {};
    std::vector<int> range_over_y {};

    Number(std::string& number, int x, int y)
        : number(number)
        , start_position(std::make_pair(x, y))
        , sz(number.length())
    {
        for (int i = start_position.first - 1; i < start_position.first + 2; ++i)
            range_over_x.push_back(i);
        for (int j = start_position.second - 1; j < start_position.second + sz + 1; ++j)
            range_over_y.push_back(j);
    };

    int GetNumberAsInt() const { return std::stoi(number); }
};

void RemoveNonStarsSymbols(strings& lines)
{
    for (auto& line : lines) {
        for (std::uint32_t i { 0 }; i < line.length(); ++i)
            if (!std::isdigit(line[i]) && line[i] != '*')
                line[i] = '.';
    }
}

strings Parse()
{
    strings lines = pypp::splitFileLines("input.txt");
    RemoveNonStarsSymbols(lines);

    return lines;
}

Numbers GetNumbers(const strings& lines)
{
    Numbers numbers {};
    std::string buf {};

    for (int i { 0 }; i < lines.size(); ++i) {
        for (int j { 0 }; j < lines[0].length(); ++j) {
            if (std::isdigit(lines[i][j]))
                buf.push_back(lines[i][j]);
            else {
                if (!buf.empty()) {
                    numbers.push_back(Number { buf, i, static_cast<int>(j - buf.length()) });
                    buf.clear();
                }
            }
        }
    }

    return numbers;
}

pairs GetMaybeGearsCoordinates(const strings& lines)
{
    pairs maybe_gears_coordinates {};

    for (int i = 0; i < lines.size(); ++i) {
        for (int j = 0; j < lines[0].length(); ++j) {
            if (lines[i][j] == '*')
                maybe_gears_coordinates.push_back(std::make_pair(i, j));
        }
    }

    return maybe_gears_coordinates;
}

bool IsPartNumber(const Number& number, const std::pair<int, int>& maybe_gear)
{
    bool same_row { false };
    bool same_col { false };

    return std::ranges::any_of(number.range_over_x, [maybe_gear](const int x) { return x == maybe_gear.first; })
        && std::ranges::any_of(number.range_over_y, [maybe_gear](const int y) { return y == maybe_gear.second; });
}

int main()
{
    // Parse
    strings lines = Parse();

    // Collect all numbers
    const auto& numbers = GetNumbers(lines);

    // Collect coordinates of all potential gears
    const auto& maybe_gears_coordinates = GetMaybeGearsCoordinates(lines);

    // Compute gear ratios and their total
    Numbers part_number_per_maybe_gear {};
    int sum { 0 };
    for (const auto& maybe_gear_xy : maybe_gears_coordinates) {
        for (const auto& number : numbers) {
            if (IsPartNumber(number, maybe_gear_xy)) {
                part_number_per_maybe_gear.push_back(number);
            }
        }

        if (part_number_per_maybe_gear.size() > 1)
            // maybe_gear is a gear
            sum += part_number_per_maybe_gear[0].GetNumberAsInt() * part_number_per_maybe_gear[1].GetNumberAsInt();
        part_number_per_maybe_gear.clear();
    }

    std::cout << "Sum of gear ratios: " << sum << std::endl;

    return 0;
}