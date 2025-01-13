#pragma once
#include <string>
#include <utility>
#include <iostream>

namespace Spreadsheet
{
    // Abstract base class for cells used in a spreadsheet
    class Cell
    {
    public:
        // Default constructor
        Cell() = default;

        // Virtual destructor (important for polymorphic base classes)
        virtual ~Cell() = default;

        // Copy constructor
        Cell(const Cell& copy) = default;

        // Assignment operator
        Cell& operator=(const Cell& other) = default;

        // Setters
        void setGridPosition(int row, int col) {
            m_row = row;
            m_col = col;
        }

        // Getters
        std::pair<int, int> getGridPosition() const {
            return { m_row, m_col };
        }

        // Pure virtual function to make this class abstract
        virtual void displayContent() const = 0;
		  virtual std::string getValueAsString() const = 0;

    protected:
        int m_row = 0; // Row position of the cell
        int m_col = 0; // Column position of the cell
    };
}
