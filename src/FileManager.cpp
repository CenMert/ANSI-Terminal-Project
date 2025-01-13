#include "FileManager.h"
#include "SpreadSheet.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include "IntValueCell.h"
#include "DoubleValueCell.h"
#include "StringValueCell.h"
#include <filesystem> 	// this library added for the folder check
						// std::filesystem for example

/*
Util namesapce are defined for the classes that usabble and efficent for the external
calculations and operations.
Util namesapce has FileManager and Parser classes.
*/

namespace Util {

    void FileManager::saveToCSV(const Spreadsheet::SpreadSheet& sheet, const std::string& filename) {
		 
		// this is the folder name where the saved files are keeping.
		std::string folder = "savedFiles";
		
		// Ensure the directory exists
		/*
        if (!std::filesystem::exists(folder)) {
            std::filesystem::create_directory(folder);
        }*/
		
		std::string full_path = folder + "/" + filename;
        std::ofstream file(full_path);
		
		if (!file.is_open()) {
            throw std::runtime_error("Unable to open file for saving: " + full_path);
        }

        for (size_t row = 0; row < sheet.getRows(); ++row) {
            for (size_t col = 0; col < sheet.getCols(); ++col) {
                const auto cell = sheet.getCell(row, col);
                if (cell) {
                    file << escapeCSV(cell->getValueAsString());
                }
                if (col < sheet.getCols() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }

        file.close();
    }

    void FileManager::loadFromCSV(Spreadsheet::SpreadSheet& sheet, const std::string& filename) {
    // Define the folder name
    std::string folder = "savedFiles";

    // Construct the full path
    std::string full_path = folder + "/" + filename;

    // Open the file for reading
    std::ifstream file(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for loading: " + full_path);
    }

    std::string line;
    size_t row = 0;

    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string cellValue;
        size_t col = 0;

        while (std::getline(lineStream, cellValue, ',')) {
            if (!cellValue.empty()) {
                cellValue = unescapeCSV(cellValue);

                // Determine cell type
                try {
                    double doubleValue = std::stod(cellValue); // Try parsing as double
                    sheet.setCell(row, col, new Spreadsheet::DoubleValueCell(doubleValue));
                } catch (const std::invalid_argument&) {
                    // If parsing fails, treat as a string
                    sheet.setCell(row, col, new Spreadsheet::StringValueCell(cellValue));
                }
            }
            ++col;
        }
        ++row;
    }

    file.close();
}


    std::string FileManager::escapeCSV(const std::string& value) {
        std::string escaped = value;
        if (escaped.find(',') != std::string::npos || escaped.find('"') != std::string::npos) {
            escaped = "\"" + escaped + "\"";
        }
        return escaped;
    }

    std::string FileManager::unescapeCSV(const std::string& value) {
        if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
            return value.substr(1, value.size() - 2);
        }
        return value;
    }

} // namespace Util
