#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "pypp.hpp" // https://github.com/A-Bergonzoli/pypp

constexpr int8_t kMaxRed = 12;
constexpr int8_t kMaxGreen = 13;
constexpr int8_t kMaxBlue = 14;

using strings = std::vector<std::string>;
using maps = std::vector<std::unordered_map<std::string, int>>;

strings Parse()
{
    strings lines = pypp::splitFileLines("input.txt");
    for (int8_t i { 0 }; i < lines.size(); ++i) {
        // remove "Game xx: "
        lines[i] = pypp::lstrip(lines[i], [](unsigned char ch) { return ch != ':'; });
        lines[i] = pypp::lstrip(lines[i], [](unsigned char ch) { return !std::isdigit(ch); });
        // Remove commas and semicolons
        std::replace(std::begin(lines[i]), std::end(lines[i]), ',', ' ');
        std::replace(std::begin(lines[i]), std::end(lines[i]), ';', ' ');
    }

    return lines;
}

int Max(const std::string& color, const std::string& line)
{
    int max { 0 };
    const auto& tmp_s = pypp::split(line, ' ');
    for (int i = 0; i < tmp_s.size(); ++i) {
        if (i + 1 % 2 != 0 && tmp_s[i + 1] == color && max < std::stoi(tmp_s[i]))
            max = std::stoi(tmp_s[i]);
    }

    return max;
}

maps ComputeMaxAllGames(const strings& lines)
{
    maps map_vector {};

    for (int i = 0; i < lines.size(); ++i) {
        int max_red = Max("red", lines[i]);
        int max_green = Max("green", lines[i]);
        int max_blue = Max("blue", lines[i]);
        std::unordered_map<std::string, int> map {
            std::make_pair("red", max_red),
            std::make_pair("green", max_green),
            std::make_pair("blue", max_blue)
        };
        map_vector.push_back(map);
    }

    return map_vector;
}

int PowerSetOfCubes(std::unordered_map<std::string, int>& map)
{
    return map["red"] * map["green"] * map["blue"];
}

int main()
{
    strings lines = Parse();

    maps color_to_max_mappings = ComputeMaxAllGames(lines);

    int sum { 0 };
    for (auto& map : color_to_max_mappings)
        sum += PowerSetOfCubes(map);

    std::cout << "Result: " << sum << std::endl;
    return 0;
}
