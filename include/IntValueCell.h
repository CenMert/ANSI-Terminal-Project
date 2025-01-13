#pragma once

#include "ValueCell.h"
#include <iostream>
#include <string>
#include <stdexcept>

namespace Spreadsheet {

    class DoubleValueCell; // Forward declaration for mixed-type operator support

    // IntValueCell: Specialized class for integer cell values
    class IntValueCell : public ValueCell<int> {
    public:
        // Constructors
        IntValueCell() : ValueCell<int>(0) {}
        explicit IntValueCell(int value) : ValueCell<int>(value) {}

        // Overloaded arithmetic operators for IntValueCell
        int operator+(const IntValueCell& other) const;
        int operator-(const IntValueCell& other) const;
        int operator*(const IntValueCell& other) const;
        int operator/(const IntValueCell& other) const;

        // Getters and Setters
        int getValue() const override;
        void setValue(int value) override;
        std::string getValueAsString() const override;

        // Display Content
        void displayContent() const override;

        // Output stream operator
        friend std::ostream& operator<<(std::ostream& os, const IntValueCell& cell);

    private:
        // m_value is inherited from ValueCell<int>
    };

    // Non-member operator overloads for IntValueCell and DoubleValueCell interactions
    double operator+(const IntValueCell& lhs, const DoubleValueCell& rhs);
    double operator-(const IntValueCell& lhs, const DoubleValueCell& rhs);
    double operator*(const IntValueCell& lhs, const DoubleValueCell& rhs);
    double operator/(const IntValueCell& lhs, const DoubleValueCell& rhs);
}
