#include "pypp.hpp" // https://github.com/A-Bergonzoli/pypp

#include <iostream>
#include <optional>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

std::optional<std::pair<int, int>> Search2dGrid(char to_find, const std::string& around, const strings& in_grid, std::pair<int, int> from)
{
    const std::int64_t max_row = std::min(from.first + 1UL, in_grid.size() - 1UL);
    const std::int64_t max_col = std::min(from.second + around.length(), in_grid[0].length() - 1UL);

    for (std::int64_t i { std::max(from.first - 1, 0) }; i <= max_row; ++i) {
        for (std::int64_t j { std::max(from.second - 1, 0) }; j <= max_col; ++j) {
            if (in_grid.at(i).at(j) == to_find) {
                return std::make_pair(i, j);
            }
        }
    }

    return std::nullopt;
}

void ConvertSymbolsToStars(strings& lines)
{
    for (auto& line : lines) {
        for (std::uint32_t i { 0 }; i < line.length(); ++i)
            if (!std::isdigit(line[i]) && line[i] != '.')
                line[i] = '*';
    }
}

strings Parse()
{
    strings lines = pypp::splitFileLines("input.txt");
    ConvertSymbolsToStars(lines);

    return lines;
}

std::vector<int> GetPartNumbers(const strings& lines)
{
    std::vector<int> part_numbers {};

    std::string digit_buf {};
    for (std::uint32_t row { 0 }; row < lines.size(); ++row) {
        for (std::uint32_t col { 0 }; col < lines[row].length(); ++col) {
            if (std::isdigit(lines[row][col])) {
                digit_buf.push_back(lines[row][col]);

            } else if (!digit_buf.empty()) {
                const auto _ = Search2dGrid('*', digit_buf, lines, std::make_pair(row, col - digit_buf.length()));
                if (_.has_value())
                    part_numbers.push_back(std::stoi(digit_buf));
                digit_buf.clear();
            }
        }
    }

    return part_numbers;
}

int main()
{
    strings lines = Parse();

    std::vector<int> part_numbers = GetPartNumbers(lines);

    int sum { 0 };
    for (const auto part_number : part_numbers) {
        sum += part_number;
    }

    std::cout << "Sum of Part Numbers: " << sum << std::endl;

    return 0;
}