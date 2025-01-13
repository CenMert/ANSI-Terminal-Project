#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <functional>
#include <stdexcept>

namespace Util {
    class Parser {
    public:
        // Parse and evaluate a formula
        double parse(const std::string& formula, std::function<double(const std::string&)> getCellValue);

    private:
        // Handle range functions like SUM, AVER, MAX, MIN, STDEV
        double handleFunction(const std::string& func, const std::string& token, std::function<double(const std::string&)> getCellValue);

        // Parse a range like A1..A10
        std::vector<std::string> parseRange(const std::string& range);

        // Helper functions for math operations
        double sum(const std::vector<double>& values);

        double average(const std::vector<double>& values);

        double max(const std::vector<double>& values);

        double min(const std::vector<double>& values);

        double stdev(const std::vector<double>& values);

    }; // class Parser
} // namespace Util