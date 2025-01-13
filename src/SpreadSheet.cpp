#include "SpreadSheet.h"

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"

namespace Spreadsheet{
    // Constructor: dynamically allocate a 2D array of Cell pointers
    SpreadSheet::SpreadSheet(size_t rows, size_t cols)
        : m_rows(rows), m_cols(cols) {
        m_grid = new Cell * *[m_rows]; // Allocate rows
        for (size_t i = 0; i < m_rows; ++i) {
            m_grid[i] = new Cell * [m_cols]; // Allocate columns for each row
            for (size_t j = 0; j < m_cols; ++j) {
                m_grid[i][j] = nullptr; // Initialize all cells to nullptr
            }
        }
    }

    // Destructor: clean up the allocated 2D array
    SpreadSheet::~SpreadSheet() {
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_cols; ++j) {
                delete m_grid[i][j]; // Delete each cell object
            }
            delete[] m_grid[i]; // Delete each row
        }
        delete[] m_grid; // Delete the array of row pointers
    }

    // Set a cell in the spreadsheet
	// This cell do not keep the previous cell value, it will delete it automaticly.
    void SpreadSheet::setCell(size_t row, size_t col, Cell* cell) {
        if (row >= m_rows || col >= m_cols) {
            throw std::out_of_range("Invalid cell position");
        }
        delete m_grid[row][col]; // Delete the existing cell, if any
        m_grid[row][col] = cell; // Assign the new cell
    }

    // Get a cell from the spreadsheet
    Cell* SpreadSheet::getCell(size_t row, size_t col) const {
        if (row >= m_rows || col >= m_cols) {
            throw std::out_of_range("Invalid cell position");
        }
        return m_grid[row][col];
    }

    Cell* SpreadSheet::getCell(const std::string& cellRef) const {
        // Parse "A1" to row and column indices.
        char col = cellRef[0]; // Assumes single-letter columns for simplicity.
        int row = std::stoi(cellRef.substr(1)) - 1;
        return getCell(row, col - 'A');
    }

    size_t SpreadSheet::getRows() const
    {
        return m_rows;
    }

    size_t SpreadSheet::getCols() const
    {
        return m_cols;
    }


    // Print the entire spreadsheet content
    void SpreadSheet::display() const {
        // print in green color
		std::cout << GREEN << "Spreadsheet Content:" << RESET << std::endl;

        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_cols; ++j) {
                if (m_grid[i][j]) {
                    std::cout << "[Cell (" << i << ", " << j << ")]\t";
                }
                else if (m_grid[i][j] == nullptr) {
                    std::cout << "[Cell Empty]\t";
                }
                else
                {
                    std::cout << "[Cell Empty]\t";
                }
            }
            std::cout << '\n';
        }

		// print in red color
		std::cout << RED << "End of Spreadsheet Content" << RESET << std::endl;
    }
    void SpreadSheet::displayAsValue() const
    {
		// print in blue color
		std::cout << BLUE << "Spreadsheet Content:" << RESET << std::endl;

		for (size_t i = 0; i < m_rows; ++i) {
			for (size_t j = 0; j < m_cols; ++j) {
				if (m_grid[i][j]) {
					std::cout << m_grid[i][j]->getValueAsString() << '\t';
				}
				else if (m_grid[i][j] == nullptr) {
					std::cout << "[Cell Empty]\t";
				}
				else
				{
					std::cout << "[Cell Empty]\t";
				}
			}
			std::cout << '\n';
		}
        // print in red color
        std::cout << RED << "End of Spreadsheet Content" << RESET << std::endl;
    }

}
