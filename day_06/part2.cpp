#include "pypp.hpp" // https://github.com/A-Bergonzoli/pypp

#include <cmath>
#include <iostream>
#include <string>

void Parse(const std::string& file, long& time, long& record)
{
    std::string time_s {};
    std::string record_s {};

    auto lines = pypp::splitFileLines(file);

    for (auto c : lines[0])
        if (std::isdigit(c))
            time_s.push_back(c);

    for (auto c : lines[1])
        if (std::isdigit(c))
            record_s.push_back(c);

    time = std::stol(time_s);
    record = std::stol(record_s);
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
    long time {};
    long record {};

    Parse("input.txt", time, record);

    std::cout << "Result: " << GetHowManyWinStrategy(time, record) << std::endl;
    return 0;
}