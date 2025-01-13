#pragma once
#include "Cell.h"
#include <iostream>
#include <string>
#include <stdexcept>

/*
This is second derived class for the <int> <double> and <string> value cells.
This class is derived from the base class Cell.
typname Type: will be replaced by int, double, or string.
displayContent() is virtual and can be overriden.
+ BIG3 used.
+ const keywords are used properly.
*/

namespace Spreadsheet {
    // Generic base class for value cells
    template <typename Type>
    class ValueCell : public Cell {
    public:
        ValueCell() = default;
        explicit ValueCell(Type value) : m_value(value) {} // Constructor with initialization
        virtual ~ValueCell() = default;

        // Copy and Assignment
        ValueCell(const ValueCell& copy) = default;
        ValueCell& operator=(const ValueCell& other) = default;

        // Pure Virtual Functions
        virtual std::string getValueAsString() const = 0;
        virtual Type getValue() const = 0;
        virtual void setValue(Type value) = 0; // Pure virtual for setting the value

        // Display Content
        virtual void displayContent() const {
            std::cout << "Value: " << getValueAsString() << "\n";
        }

    protected:
        Type m_value{}; // Protected to allow derived classes access
    };
}
