#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

void ParseInput(std::vector<int>& calibration_values, const std::string& file_name)
{
    std::string line {};
    std::fstream input(file_name, std::ios::in);

    if (input.is_open()) {
        while (std::getline(input, line)) {
            if (!std::all_of(line.begin(), line.end(), ::isdigit)) {
                line.erase(std::remove_if(line.begin(), line.end(), [](const char ch) { return !std::isdigit(ch); }), line.end());
            }
            if (!line.empty()) {
                const std::string first = line.substr(0, 1);
                const std::string last = line.substr(line.size() - 1, line.size());
                calibration_values.push_back(std::stoi(first + last));
            }
        }
    }
}

int main()
{
    std::vector<int> calibration_values {};

    ParseInput(calibration_values, "input.txt");

    std::cout << "Result: " << std::accumulate(calibration_values.begin(), calibration_values.end(), 0);

    return 0;
}