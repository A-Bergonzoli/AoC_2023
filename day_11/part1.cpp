#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "pypp.hpp"

strings TransposeMatrix(const strings& original)
{
    const int cols = original[0].length();
    const int rows = original.size();

    std::string some_row(rows, 'x');
    strings transposed { cols, some_row };

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            transposed[j][i] = original[i][j];

    return transposed;
}

class Solution {
public:
    void Parse(const std::string& file_name)
    {
        auto og_universe = pypp::splitFileLines(file_name);

        auto partially_expanded_universe = ExpandUniverse(og_universe);

        auto transposed = TransposeMatrix(partially_expanded_universe);
        expanded_universe_ = TransposeMatrix(ExpandUniverse(transposed));
    }

    strings ExpandUniverse(const strings& current_universe)
    {
        strings parsed_input {};

        for (auto& row : current_universe) {
            bool all_empty_space { true };
            for (auto& elem : row) {
                if (elem == '#') {
                    all_empty_space = false;
                    parsed_input.push_back(row);
                    break; // skip rest of line
                }
            }
            if (all_empty_space) {
                // here we add row
                parsed_input.push_back(std::string(row.length(), '.'));
                parsed_input.push_back(row);
            }
        }

        return parsed_input;
    }

    long ComputeSumOfShortestPathsBetweenGalaxiesPairs()
    {
        unsigned long result { 0UL };

        // put the galaxy in an hash map:
        // - key : ID
        // - value : coordinate (x, y)
        int counter { 0 };
        std::unordered_map<int, std::pair<int, int>> galaxy_map {};
        for (int i = 0; i < expanded_universe_.size(); ++i) {
            for (int j = 0; j < expanded_universe_[i].length(); ++j) {
                if (expanded_universe_[i][j] == '#')
                    galaxy_map.insert({ ++counter, std::make_pair(i, j) });
            }
        }

        // cycle through unique pair of IDs and find the shortest path
        for (int i = 0; i < galaxy_map.size(); ++i) {
            for (int j = i + 1; j < galaxy_map.size(); ++j) {
                const auto key_1 = i + 1;
                const auto key_2 = j + 1;
                const auto dy = std::abs(galaxy_map.at(key_2).second - galaxy_map.at(key_1).second);
                const auto dx = std::abs(galaxy_map.at(key_2).first - galaxy_map.at(key_1).first);
                result += dy + dx;
            }
        }

        return result;
    }

private:
    strings expanded_universe_;
};

int main()
{
    Solution solution {};

    solution.Parse("input.txt");
    std::cout << solution.ComputeSumOfShortestPathsBetweenGalaxiesPairs() << std::endl;

    return 0;
}