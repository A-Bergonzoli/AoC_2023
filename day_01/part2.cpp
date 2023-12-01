#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

constexpr int patch { 1 };

enum class TokenType {
    DIGIT,
    ALPHA
};

struct Token {
    TokenType type;
    char value;
};

class Tokenizer {
public:
    explicit Tokenizer(const std::string& line)
        : line_(line)
    {
    }

    std::optional<char> Peek(int steps_ahead = 0)
    {
        if (index_ + steps_ahead >= line_.length())
            return std::nullopt;

        return line_.at(index_ + steps_ahead);
    }

    char ConsumeAdvance()
    {
        return line_.at(index_++);
    }

    std::vector<Token> tokenize()
    {
        std::vector<Token> tokens {};

        while (Peek().has_value()) {
            if (std::isdigit(Peek().value())) {
                // digit token
                tokens.push_back(Token { .type = TokenType::DIGIT, .value = Peek().value() });
                ConsumeAdvance();
            } else {
                // alpha token
                tokens.push_back(Token { .type = TokenType::ALPHA, .value = Peek().value() });
                ConsumeAdvance();
            }
        }

        index_ = 0;
        return tokens;
    }

private:
    std::string line_;
    size_t index_ { 0 };
};

class Parser {
public:
    explicit Parser(std::vector<Token> tokens)
        : tokens_(std::move(tokens))
    {
    }

    std::optional<Token> Peek(int steps_ahead = 0) const
    {
        if (index_ + steps_ahead > tokens_.size() - 1)
            return std::nullopt;

        return tokens_.at(index_ + steps_ahead);
    }

    Token ConsumeAdvance()
    {
        return tokens_.at(index_++);
    }

    std::optional<std::string> parseDigit()
    {
        if (Peek().has_value() && Peek().value().type == TokenType::DIGIT) {
            return std::string(1, Peek().value().value);
        }
        return std::nullopt;
    }

    ///@param fuck_you `oneeight` --- shoudl be parsed as ---> `18`, instead of `1`
    ///                 Boy that would have been fun to know uh?
    std::optional<std::string> parseNumberAsString(const std::string& numberAsLetter, const std::string& numberAsDigit, const int fuck_you = 0) const
    {
        bool maybe_number { true };
        bool for_sure_number { true };

        for (int i = 0; i < numberAsLetter.length(); ++i) {
            if (!(Peek(i - fuck_you).has_value() && (Peek(i - fuck_you).value().type == TokenType::ALPHA)))
                maybe_number = false;
        }

        if (maybe_number) {
            for (int i = 0; i < numberAsLetter.length(); ++i) {
                if (!(Peek(i - fuck_you).value().value == numberAsLetter[i])) {
                    for_sure_number = false;
                }
            }
        }
        if (maybe_number && for_sure_number)
            return numberAsDigit;

        return {};
    }

    std::optional<std::vector<std::string>> parseLine()
    {
        std::vector<std::string> line;

        while (Peek().has_value()) {
            if (auto digit = parseDigit()) {
                if (digit.has_value()) {
                    line.push_back(digit.value());
                    ConsumeAdvance();
                }
            } else if (auto one = parseNumberAsString("one", "1")) {
                if (one.has_value()) {
                    line.push_back(one.value());
                    for (auto elem : std::string("one"))
                        ConsumeAdvance();
                }
            } else if (auto two = parseNumberAsString("two", "2")) {
                if (two.has_value()) {
                    line.push_back(two.value());
                    for (auto elem : std::string("two"))
                        ConsumeAdvance();
                }
            } else if (auto three = parseNumberAsString("three", "3")) {
                if (three.has_value()) {
                    line.push_back(three.value());
                    for (auto elem : std::string("three"))
                        ConsumeAdvance();
                }
            } else if (auto four = parseNumberAsString("four", "4")) {
                if (four.has_value()) {
                    line.push_back(four.value());
                    for (auto elem : std::string("four"))
                        ConsumeAdvance();
                }
            } else if (auto five = parseNumberAsString("five", "5")) {
                if (five.has_value()) {
                    line.push_back(five.value());
                    for (auto elem : std::string("five"))
                        ConsumeAdvance();
                }
            } else if (auto six = parseNumberAsString("six", "6")) {
                if (six.has_value()) {
                    line.push_back(six.value());
                    for (auto elem : std::string("six"))
                        ConsumeAdvance();
                }
            } else if (auto seven = parseNumberAsString("seven", "7")) {
                if (seven.has_value()) {
                    line.push_back(seven.value());
                    for (auto elem : std::string("seven"))
                        ConsumeAdvance();
                }
            } else if (auto eight = parseNumberAsString("eight", "8")) {
                if (eight.has_value()) {
                    line.push_back(eight.value());
                    for (auto elem : std::string("eight"))
                        ConsumeAdvance();
                }
            } else if (auto nine = parseNumberAsString("nine", "9")) {
                if (nine.has_value()) {
                    line.push_back(nine.value());
                    for (auto elem : std::string("nine"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_one = parseNumberAsString("one", "1", patch)) {
                if (shitty_one.has_value()) {
                    line.push_back(shitty_one.value());
                    for (auto elem : std::string("ne"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_two = parseNumberAsString("two", "2", patch)) {
                if (shitty_two.has_value()) {
                    line.push_back(shitty_two.value());
                    for (auto elem : std::string("wo"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_three = parseNumberAsString("three", "3", patch)) {
                if (shitty_three.has_value()) {
                    line.push_back(shitty_three.value());
                    for (auto elem : std::string("hree"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_four = parseNumberAsString("four", "4", patch)) {
                if (shitty_four.has_value()) {
                    line.push_back(shitty_four.value());
                    for (auto elem : std::string("our"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_five = parseNumberAsString("five", "5", patch)) {
                if (shitty_five.has_value()) {
                    line.push_back(shitty_five.value());
                    for (auto elem : std::string("ive"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_six = parseNumberAsString("six", "6", patch)) {
                if (shitty_six.has_value()) {
                    line.push_back(shitty_six.value());
                    for (auto elem : std::string("ix"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_seven = parseNumberAsString("seven", "7", patch)) {
                if (shitty_seven.has_value()) {
                    line.push_back(shitty_seven.value());
                    for (auto elem : std::string("even"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_eight = parseNumberAsString("eight", "8", patch)) {
                if (shitty_eight.has_value()) {
                    line.push_back(shitty_eight.value());
                    for (auto elem : std::string("ight"))
                        ConsumeAdvance();
                }
            } else if (auto shitty_nine = parseNumberAsString("nine", "9", patch)) {
                if (shitty_nine.has_value()) {
                    line.push_back(shitty_nine.value());
                    for (auto elem : std::string("ine"))
                        ConsumeAdvance();
                }
            } else {
                ConsumeAdvance();
            }
        }

        index_ = 0;
        return line;
    }

private:
    std::vector<Token> tokens_;
    size_t index_ { 0 };
};

void ParseInput(std::vector<int>& calibration_values, const std::string& file_name)
{
    std::string line {};
    std::fstream input(file_name, std::ios::in);

    if (input.is_open()) {
        while (std::getline(input, line)) {
            Tokenizer tokenizer { line };
            std::vector<Token> tokens = tokenizer.tokenize();
            Parser parser { tokens };
            auto tmp = parser.parseLine();

            if (tmp.has_value()) {
                calibration_values.push_back(std::stoi(tmp.value()[0] + tmp.value()[tmp.value().size() - 1]));
            }
        }
    }
}

int main()
{
    std::vector<int> calibration_values {};

    ParseInput(calibration_values, "input.txt");

    std::cout << calibration_values.size() << std::endl;
    std::cout << "Result: " << std::accumulate(calibration_values.begin(), calibration_values.end(), 0);

    return 0;
}