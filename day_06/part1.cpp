#include "pypp.hpp" // https://github.com/A-Bergonzoli/pypp

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

void Parse(const std::string& file, std::vector<long>& times, std::vector<long>& records)
{

    auto lines = pypp::splitFileLines(file);

    auto times_s = pypp::split(lines[0], ' ');
    times_s.erase(times_s.begin());
    auto records_s = pypp::split(lines[1], ' ');
    records_s.erase(records_s.begin());

    times.reserve(times_s.size());
    for (auto time : times_s)
        times.push_back(std::stol(time));

    records.reserve(records_s.size());
    for (auto distance : records_s)
        records.push_back(std::stol(distance));
}

int GetHowManyWinStrategy(long time_max, long record)
{
    /*
     * Given: vel = Delta_pos / Delta_time
     * for each `t_max` and `record`
     * the num of ways to beat the record is found by solving this inequality:
     *
     *             distance_traveled > record
     *     vel   *   delta_time_from_release   >   record
     *     t_r   *        (t_max - t_r)        >   record
     *     t_r^2 - t_max * t_r + record < 0
     *
     * where t_r is the time step at which we release the button
     *
     */

    auto a { 1L };
    auto b { -time_max };
    auto c { record };
    auto root_1 = std::ceil((-b + std::sqrt(b * b - 4 * a * c)) / (2 * a));
    auto root_2 = std::floor((-b - std::sqrt(b * b - 4 * a * c)) / (2 * a));

    return root_1 - root_2 - 1;
}

int main()
{
    std::vector<long> times {};
    std::vector<long> records {};

    Parse("input.txt", times, records);

    long product { 1L };
    for (int i = 0; i < times.size(); ++i)
        product *= GetHowManyWinStrategy(times[i], records[i]);

    std::cout << "Result: " << product << std::endl;
    return 0;
}