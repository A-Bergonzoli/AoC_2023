#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "pypp.hpp"

constexpr auto expected { 303 };

struct Point2D {
    int x;
    int y;
};

bool operator==(const Point2D& lhs, const Point2D& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const Point2D& lhs, const Point2D& rhs)
{
    return !(lhs == rhs);
}

struct Point2DHash {
    size_t operator()(const Point2D& point) const
    {
        return point.x ^ point.y;
    }
};

class Solution {
public:
    void Parse(const std::string& file_name)
    {
        auto lines = pypp::splitFileLines(file_name);

        for (int i = 0; i < lines.size(); ++i) {
            map_.push_back({});
            for (int j = 0; j < lines[i].size(); ++j) {
                map_[i].push_back(lines[i][j]);
                if (lines[i][j] == 'S')
                    start_ = Point2D { i, j };

                maze_[{ i, j }] = lines[i][j];
            }
        }

        map_[25][108] = '|';

        height_ = lines.size();
        width_ = lines[0].size();
    }

    std::pair<Point2D, Point2D> ComputePossibleMoves(Point2D& current, Point2D& prev)
    {
        Point2D up { current.x - 1, current.y };
        Point2D down { current.x + 1, current.y };
        Point2D left { current.x, current.y - 1 };
        Point2D right { current.x, current.y + 1 };

        switch (maze_[current]) {
        case '|':
            return std::make_pair(up, down);
        case '-':
            return std::make_pair(left, right);
        case 'L':
            return std::make_pair(up, right);
        case 'J':
            return std::make_pair(up, left);
        case 'F':
            return std::make_pair(down, right);
        default: // '7'
            return std::make_pair(down, left);
        }
    }

    Point2D Move(Point2D& current, Point2D& prev)
    {
        Point2D option_1 {};
        Point2D option_2 {};

        std::tie(option_1, option_2) = ComputePossibleMoves(current, prev);

        return (option_1 != prev) ? option_1 : option_2;
    }

    void TraverseMaze()
    {
        auto old_now { start_ };
        auto prev { start_ };
        auto now = Point2D { start_.x + 1, start_.y };

        tunnel_parts.insert(start_);
        tunnel_parts.insert(now);

        while (maze_[now] != 'S') {
            // loop until we reach the start again
            old_now = now;
            now = Move(now, prev);
            tunnel_parts.insert(now);
            prev = old_now;

            move_count++;
        }
    }

    bool IsPartOfTunnel(Point2D candidate)
    {
        const auto it = std::ranges::find(tunnel_parts, candidate);
        return it != tunnel_parts.end();
    }

    int GetNumEnclosedTiles()
    {
        int tot = 0;

        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                int cnt = 0;

                if (!IsPartOfTunnel(Point2D { i, j })) {
                    for (int k = j + 1; k < width_; ++k) {
                        if ((map_[i][k] == '|' || map_[i][k] == 'J' || map_[i][k] == 'L') && IsPartOfTunnel(Point2D { i, k })) {
                            cnt++;
                        }
                    }
                }

                tot += (cnt % 2 == 0) ? 0 : 1; // even => outside, odd => inside
            }
        }

        return tot;
    }

    std::vector<std::vector<char>> map_ {};
    std::unordered_map<Point2D, char, Point2DHash> maze_;
    std::unordered_set<Point2D, Point2DHash> tunnel_parts {};
    Point2D start_ { 0, 0 };
    int move_count { 1 };
    int width_ { 0 };
    int height_ { 0 };
};

int main(int argc, char* argv[])
{
    Solution solution {};
    solution.Parse("input.txt");
    solution.TraverseMaze();

    int result { solution.GetNumEnclosedTiles() };
    std::cout << "Number of enclosed tiles: " << result << std::endl;

    assert(expected == result);
    return 0;
}
