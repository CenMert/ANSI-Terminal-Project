#pragma once

#include "SpreadSheet.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

namespace Util {

    class FileManager {
    public:
        // Save the spreadsheet to a CSV file
        static void saveToCSV(const Spreadsheet::SpreadSheet& sheet, const std::string& filename);

        // Load the spreadsheet from a CSV file
        static void loadFromCSV(Spreadsheet::SpreadSheet& sheet, const std::string& filename);

    private:
        // Helper to escape strings for CSV format
        static std::string escapeCSV(const std::string& value);

        // Helper to unescape strings from CSV format
        static std::string unescapeCSV(const std::string& value);
    };

} // namespace Util
