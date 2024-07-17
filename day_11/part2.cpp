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
        og_universe_ = pypp::splitFileLines(file_name);

        empty_rows_indexes_ = GetEmptyRowIndexes(og_universe_);
        empty_cols_indexes_ = GetEmptyRowIndexes(TransposeMatrix(og_universe_));
    }

    std::vector<int> GetEmptyRowIndexes(const strings& universe)
    {
        std::vector<int> indexes {};

        for (int i = 0; i < universe.size(); ++i) {
            bool empty_flag { true };

            for (const auto& elem : universe[i])
                if (elem == '#') {
                    empty_flag = false;
                    break; // skip rest of line
                }

            if (empty_flag)
                indexes.push_back(i);
        }

        return indexes;
    }

    void FillGalaxyMap()
    {
        long counter { 0L };

        for (long i = 0; i < og_universe_.size(); ++i)
            // cycle tru rows
            for (long j = 0; j < og_universe_[0].size(); ++j)
                // cycle tru cols
                if (og_universe_[i][j] == '#') {
                    auto real_row { i };
                    auto real_col { j };
                    for (const auto index : empty_rows_indexes_)
                        if (index < i)
                            real_row += 999999;
                    for (const auto index : empty_cols_indexes_)
                        if (index < j)
                            real_col += 999999;

                    galaxy_map.insert({ ++counter, std::make_pair(real_row, real_col) });
                }
    }

    long
    ComputeSumOfShortestPathsBetweenGalaxiesPairs()
    {
        unsigned long result { 0UL };

        FillGalaxyMap();

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
    strings og_universe_;
    std::vector<int> empty_cols_indexes_;
    std::vector<int> empty_rows_indexes_;
    std::unordered_map<long, std::pair<long, long>> galaxy_map {};
};

int main()
{
    Solution solution {};

    solution.Parse("input.txt");
    std::cout << solution.ComputeSumOfShortestPathsBetweenGalaxiesPairs() << std::endl;

    return 0;
}