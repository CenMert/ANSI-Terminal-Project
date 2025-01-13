#pragma once

#include "Cell.h"
#include <iostream>
#include <stdexcept>
namespace Spreadsheet{

    class SpreadSheet {
    public:
        // Constructor: initializes the grid with the given dimensions
        SpreadSheet(size_t rows, size_t cols);

        // Destructor: cleans up allocated memory
        ~SpreadSheet();

        // Set a cell in the spreadsheet
        void setCell(size_t row, size_t col, Cell* cell);

        // Get a cell from the spreadsheet
		Cell* getCell(size_t row, size_t col) const;
		Cell* getCell(const std::string& cellRef) const; // Overload for cell reference

        size_t getRows() const;
        size_t getCols() const;

        // Print the entire spreadsheet content
        void display() const;
        void displayAsValue() const;

    private:
        size_t m_rows; // Number of rows in the spreadsheet
        size_t m_cols; // Number of columns in the spreadsheet
        Cell*** m_grid; // Pointer to a 2D array of Cell pointers
    };
}
