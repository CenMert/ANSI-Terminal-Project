#include "AnsiTerminal.h"
#include "SpreadSheet.h"
#include "StringValueCell.h"
#include "IntValueCell.h"
#include "DoubleValueCell.h"
#include "FileManager.h"
#include "Parser.h"
#include <iostream>
#include <memory>
#include <filesystem>

using namespace Spreadsheet;
using namespace Util;

void displayGrid(SpreadSheet& sheet, AnsiTerminal& terminal, int currentRow, int currentCol) {
    terminal.clearScreen();
    int rows = sheet.getRows(), cols = sheet.getCols();

    const std::string blueColor = "\033[34m"; // Blue text color
    const std::string resetColor = "\033[0m"; // Reset text color

    // Print column headers (A, B, C, ...)
    terminal.printAt(1, 2, blueColor);
    for (int j = 0; j < cols; ++j) {
		std::string colHeader;
		if (cols <= 26) {
			// Single letter for columns <= 26
			colHeader = std::string(1, 'A' + j); // 'A', 'B', ..., 'Z'
		} else {
			// Multi-letter for columns > 26
			int temp = j;
			while (temp >= 0) {
				colHeader.insert(colHeader.begin(), 'A' + (temp % 26)); // Prepend the letter
				temp = temp / 26 - 1; // Adjust for zero-based indexing
			}
		}
		terminal.printAt(1, j * 10 + 10, colHeader);
	}
	terminal.printAt(1, cols * 10 + 2, resetColor);


    // Print grid
    for (int i = 0; i < rows; ++i) {
        // Print row headers (1, 2, 3, ...)
        terminal.printAt(i + 2, 0, blueColor + std::to_string(i + 1) + resetColor );

        for (int j = 0; j < cols; ++j) {
			int printAtRow = i+2, printAtCol = j*10+5; // added +1 other wise string deletes "|". At print cell value - line 40
            terminal.printAt(printAtRow, printAtCol, "|                 "); // Cell borders
            if (sheet.getCell(i, j)) {
                std::string value = sheet.getCell(i, j)->getValueAsString();
                terminal.printAt(printAtRow, printAtCol + 1, value.substr(0, 10)); // Print cell value
            }
        }
        terminal.printAt(i + 2, cols * 10 + 4, "|");
    }

    // Highlight current cell
    terminal.printAt(currentRow + 2, currentCol * 10 + 5, "\033[7m          \033[0m");
}
// Function to list files in the savedFiles folder
void listFilesInDirectory(AnsiTerminal& terminal, const std::string& folder, const int rows) {
	try {
        if (!std::filesystem::exists(folder)) {
            terminal.printAt(19, 2, "Directory does not exist.");
            return;
        }

        size_t row = rows + 10; // Starting row for printing file names
        for (const auto& entry : std::filesystem::directory_iterator(folder)) {
            if (entry.is_regular_file()) {
                terminal.printAt(row++, 2, entry.path().filename().string());
            }
        }
        if (row == 50) {
            terminal.printAt(rows + 10, 2, "No files found in the folder.");
        }
    } catch (const std::exception& e) {
        terminal.printAt(rows + 9, 2, "Error accessing directory: " + std::string(e.what()));
    }
}

int main() {
    AnsiTerminal terminal;
	
	// declare vars but wait for the input.
	int rows, cols;
	
	std::cout << "Enter number of rows (!!ONLY INTEGER!!): ";
	std::cin >> rows;
	std::cout << rows << "\n";
	
	std::cout << "Enter number of columns (!!ONLY INTEGER!!): ";
	std::cin >> cols;
	std::cout << cols << "\n";

    // Create a spreadsheet with a rows x cols grid
    SpreadSheet sheet(rows, cols);

    int currentRow = 0, currentCol = 0; // Start at the top-left corner
    displayGrid(sheet, terminal, currentRow, currentCol);

    char input;
    while (true) {
        terminal.printAt(rows + 5, 2, "Use arrow keys to navigate, 'E' to edit, 'S' to save, 'l' to load, 'Q' to quit, 'X' for extra operations.");
        input = terminal.getSpecialKey();

        switch (input) {
        case 'U':
            if (currentRow > 0) currentRow--;
            break;
        case 'D':
            if (currentRow < rows - 1) currentRow++;
            break;
        case 'L':
            if (currentCol > 0) currentCol--;
            break;
        case 'R':
            if (currentCol < cols - 1) currentCol++;
            break;
        case 'E': {
			terminal.printAt(rows + 6, 2, "Enter value for the cell (spaces not allowed): ");
			std::string value;
			std::cin >> value;

			// Check for formulas with arithmetic operations
			if (value.find_first_of("+-*/") != std::string::npos) {
				try {
					// Create a parser and evaluate the formula
					Parser parser;

					// Lambda to fetch cell values dynamically from the spreadsheet
					auto getCellValue = [&sheet](const std::string& cellRef) -> double {
						const auto* cell = sheet.getCell(cellRef);  // Get the cell by reference
						if (!cell) throw std::invalid_argument("Invalid cell reference: " + cellRef);
						return std::stod(cell->getValueAsString());  // Convert value to double
					};

					// Use the parser to evaluate the formula
					double result = parser.parse(value, getCellValue);

					// Set the result as a DoubleValueCell in the current cell
					sheet.setCell(currentRow, currentCol, new DoubleValueCell(result));
				} catch (const std::exception& e) {
					terminal.printAt(rows + 7, 2, "Error evaluating formula: " + std::string(e.what()));
				}
			} else if (value.find('.') != std::string::npos) {
				sheet.setCell(currentRow, currentCol, new DoubleValueCell(std::stod(value)));
			} else if (std::all_of(value.begin(), value.end(), ::isdigit)) {
				sheet.setCell(currentRow, currentCol, new IntValueCell(std::stoi(value)));
			} else {
				sheet.setCell(currentRow, currentCol, new StringValueCell(value));
			}
			break;
		}

        case 'S': {
            terminal.printAt(rows + 6, 2, "Enter file name to save: ");
            std::string filename;
            std::cin >> filename;

            try {
                FileManager::saveToCSV(sheet, filename);
                terminal.printAt(rows + 7, 2, "Spreadsheet saved successfully!");
            } catch (const std::exception& e) {
                terminal.printAt(rows + 7, 2, "Error saving file: " + std::string(e.what()));
            }
            break;
        }
        case 'l': {
            terminal.printAt(rows + 6, 2, "Enter file name to load: ");
            std::string filename;
            std::cin >> filename;
			std::string emptyFile = "empty";
            try {
                // FileManager::loadFromCSV(sheet, emptyFile);
				FileManager::loadFromCSV(sheet, filename);
                terminal.printAt(rows + 7, 2, "Spreadsheet loaded successfully!");
            } catch (const std::exception& e) {
                terminal.printAt(rows + 7, 2, "Error loading file: " + std::string(e.what()));
            }
            break;
        }
        case 'Q':
            terminal.clearScreen();
            return 0;
        case 'X': {
            terminal.printAt(rows + 6, 2, "Listing files in savedFiles folder:");
            listFilesInDirectory(terminal, "savedFiles", rows);

            // Wait for a key press before clearing the grid
            terminal.printAt(rows + 22, 2, "Press any key to continue...");
            terminal.getKeystroke();
            break;
        }
        default:
            terminal.printAt(rows + 7, 2, "Invalid key. Try again.");
        }

        // Redraw the grid after any action
        displayGrid(sheet, terminal, currentRow, currentCol);
    }

    return 0;
}
