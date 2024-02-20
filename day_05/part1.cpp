#include "pypp.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

std::string ReadData()
{
    std::fstream input("data.txt", std::ios::in);

    if (input.is_open()) {
        std::stringstream buffer;
        buffer << input.rdbuf();
        return buffer.str();
    } else {
        std::cerr << "Error: could not open file." << std::endl;
    }
}

int Parse(std::string file)
{
    // Retrieve the seeds
    auto tmp_seed_string = pypp::split(pypp::splitLines(file)[0], ':')[1];
    auto seeds_collection = pypp::split(tmp_seed_string, ' ');
    std::vector<long> seeds {};
    seeds.reserve(seeds_collection.size());
    for (const auto& seed_as_string : seeds_collection)
        seeds.push_back(std::stol(seed_as_string));

    // Retrieve the mappings as raw blocks (std::string) of text
    auto raw_maps = pypp::split(file, ':');

    // For Every Seed
    for (auto& seed : seeds) {

        for (int i { 2 }; i < raw_maps.size(); ++i) {
            // clang-format off
            auto current_mapping = pypp::split(
                pypp::strip(raw_maps[i], [](char ch){
                    return !std::isdigit(ch);})
                , '\n'
            );
            // clang-format on
            for (auto& line : current_mapping) {
                auto range_str = pypp::split(line, ' ');
                std::array<long, 3> ranges;
                for (int i = 0; i < 3; ++i)
                    ranges[i] = std::stol(range_str[i]);

                auto dest_start = ranges[0];
                auto src_start = ranges[1];
                auto range_len = ranges[2];

                if (src_start <= seed && seed < src_start + range_len) {
                    seed = dest_start + (seed - src_start);
                    break;
                }
            }
        }
    }

    return *std::ranges::min_element(seeds);
}

int main()
{
    auto file_content = ReadData();
    std::cout << "Lowest location number: " << Parse(file_content);

    return 0;
}