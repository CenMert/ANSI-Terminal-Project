#include "Parser.h"
#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <cmath>

namespace Util {

    double Parser::parse(const std::string& formula, std::function<double(const std::string&)> getCellValue) {
        std::regex tokenRegex(
            "([A-Z]+\\d+|\\d+(\\.\\d+)?|[+\\-*/]|SUM\\(([^)]+)\\)|AVER\\(([^)]+)\\)|MAX\\(([^)]+)\\)|MIN\\(([^)]+)\\)|STDD\\(([^)]+)\\))"
        );
        std::sregex_iterator tokenIt(formula.begin(), formula.end(), tokenRegex);
        std::sregex_iterator tokenEnd;

        std::vector<double> values;
        std::vector<char> operators;

        for (; tokenIt != tokenEnd; ++tokenIt) {
            std::string token = tokenIt->str();
            if (std::regex_match(token, std::regex("\\d+(\\.\\d+)?"))) {
                // Handle numeric value
                values.push_back(std::stod(token));
            }
            else if (std::regex_match(token, std::regex("[A-Z]+\\d+"))) {
                // Handle cell reference
                values.push_back(getCellValue(token));
            }
            else if (std::regex_match(token, std::regex("[+\\-*/]"))) {
                // Handle operator
                operators.push_back(token[0]);
            }
            else if (std::regex_match(token, std::regex("SUM\\(([^)]+)\\)"))) {
                // Handle SUM(range)
                values.push_back(handleFunction("SUM", token, getCellValue));
            }
            else if (std::regex_match(token, std::regex("AVER\\(([^)]+)\\)"))) {
                // Handle AVER(range)
                values.push_back(handleFunction("AVER", token, getCellValue));
            }
            else if (std::regex_match(token, std::regex("MAX\\(([^)]+)\\)"))) {
                // Handle MAX(range)
                values.push_back(handleFunction("MAX", token, getCellValue));
            }
            else if (std::regex_match(token, std::regex("MIN\\(([^)]+)\\)"))) {
                // Handle MIN(range)
                values.push_back(handleFunction("MIN", token, getCellValue));
            }
            else if (std::regex_match(token, std::regex("STDD\\(([^)]+)\\)"))) {
                // Handle STDEV(range)
                values.push_back(handleFunction("STDD", token, getCellValue));
            }
        }

        // Perform arithmetic operations
        double result = values[0];
        for (size_t i = 0; i < operators.size(); ++i) {
            switch (operators[i]) {
            case '+': result += values[i + 1]; break;
            case '-': result -= values[i + 1]; break;
            case '*': result *= values[i + 1]; break;
            case '/': result /= values[i + 1]; break;
            }
        }
        return result;
    } // parse func

    // Private functions

    // Handle range functions like SUM, AVER, MAX, MIN, STDEV
    double Parser::handleFunction(const std::string& func, const std::string& token, std::function<double(const std::string&)> getCellValue) {
        std::regex rangeRegex("\\(([^)]+)\\)");
        std::smatch match;
        if (std::regex_search(token, match, rangeRegex)) {
            std::string range = match[1];
            std::vector<std::string> cells = parseRange(range);

            std::vector<double> values;
            for (const auto& cell : cells) {
                values.push_back(getCellValue(cell));
            }

            if (func == "SUM") {
                return sum(values);
            }
            else if (func == "AVER") {
                return average(values);
            }
            else if (func == "MAX") {
                return max(values);
            }
            else if (func == "MIN") {
                return min(values);
            }
            else if (func == "STDD") {
                return stdev(values);
            }
        }
        throw std::runtime_error("Invalid function format: " + token);
	} // handleFunction func

    // Parse a range like A1..A10
    std::vector<std::string> Parser::parseRange(const std::string& range) {
        std::regex rangeRegex("([A-Z]+)(\\d+)\\.\\.([A-Z]+)(\\d+)");
        std::smatch match;
        if (std::regex_match(range, match, rangeRegex)) {
            std::string startCol = match[1], endCol = match[3];
            int startRow = std::stoi(match[2]), endRow = std::stoi(match[4]);

            std::vector<std::string> cells;
            for (int row = startRow; row <= endRow; ++row) {
                cells.push_back(startCol + std::to_string(row));
            }
            return cells;
        }
        throw std::runtime_error("Invalid range format: " + range);
	} // parseRange func

    // Helper functions for math operations
    double Parser::sum(const std::vector<double>& values) {
        double result = 0;
        for (double val : values) result += val;
        return result;
    }

    double Parser::average(const std::vector<double>& values) {
        if (values.empty()) return 0;
        return sum(values) / values.size();
    }

    double Parser::max(const std::vector<double>& values) {
        return *std::max_element(values.begin(), values.end());
    }

    double Parser::min(const std::vector<double>& values) {
        return *std::min_element(values.begin(), values.end());
    }

    double Parser::stdev(const std::vector<double>& values) {
        double mean = average(values);
        double variance = 0;
        for (double val : values) {
            variance += (val - mean) * (val - mean);
        }
        return std::sqrt(variance / values.size());
    }
}

