#pragma once

#include "ValueCell.h"
#include "IntValueCell.h"
#include <iostream>
#include <string>
#include <stdexcept>

namespace Spreadsheet {

    // DoubleValueCell: Specialized class for floating-point cell values
    class DoubleValueCell : public ValueCell<double> {
    public:
        // Constructors
        DoubleValueCell() : ValueCell<double>(0.0) {}
        explicit DoubleValueCell(double value) : ValueCell<double>(value) {}

        // Overloaded arithmetic operators for DoubleValueCell
        double operator+(const DoubleValueCell& other) const;
        double operator-(const DoubleValueCell& other) const;
        double operator*(const DoubleValueCell& other) const;
        double operator/(const DoubleValueCell& other) const;

        // Getters and Setters
        double getValue() const override;
        void setValue(double value) override;
        std::string getValueAsString() const override;

        // Display Content
        void displayContent() const override;

        // Output stream operator
        friend std::ostream& operator<<(std::ostream& os, const DoubleValueCell& cell);

    private:
        // m_value is inherited from ValueCell<double>
    };

    // Non-member operator overloads for DoubleValueCell and IntValueCell interactions
    double operator+(const DoubleValueCell& lhs, const IntValueCell& rhs);
    double operator-(const DoubleValueCell& lhs, const IntValueCell& rhs);
    double operator*(const DoubleValueCell& lhs, const IntValueCell& rhs);
    double operator/(const DoubleValueCell& lhs, const IntValueCell& rhs);
}
