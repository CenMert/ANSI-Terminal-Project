#include "DoubleValueCell.h"
#include "IntValueCell.h"
#include <iostream>
#include <stdexcept>

namespace Spreadsheet {

    double DoubleValueCell::operator+(const DoubleValueCell& other) const {
        return m_value + other.m_value;
    }

    double DoubleValueCell::operator-(const DoubleValueCell& other) const {
        return m_value - other.m_value;
    }

    double DoubleValueCell::operator*(const DoubleValueCell& other) const {
        return m_value * other.m_value;
    }

    double DoubleValueCell::operator/(const DoubleValueCell& other) const {
        if (other.m_value == 0) throw std::invalid_argument("Division by zero.");
        return m_value / other.m_value;
    }

    double DoubleValueCell::getValue() const {
        return m_value;
    }

    void DoubleValueCell::setValue(double value) {
        m_value = value;
    }

    std::string DoubleValueCell::getValueAsString() const
    {
        return std::to_string(m_value);
    }

    std::ostream& operator<<(std::ostream& os, const DoubleValueCell& cell) {
        os << cell.getValue();
        return os;
    }

    void DoubleValueCell::displayContent() const {
        std::cout << m_value << std::endl;
    }

    double operator+(const DoubleValueCell& lhs, const IntValueCell& rhs) {
        return lhs.getValue() + static_cast<double>(rhs.getValue());
    }

    double operator-(const DoubleValueCell& lhs, const IntValueCell& rhs) {
        return lhs.getValue() - static_cast<double>(rhs.getValue());
    }

    double operator*(const DoubleValueCell& lhs, const IntValueCell& rhs) {
        return lhs.getValue() * static_cast<double>(rhs.getValue());
    }

    double operator/(const DoubleValueCell& lhs, const IntValueCell& rhs) {
        if (rhs.getValue() == 0) throw std::invalid_argument("Division by zero.");
        return lhs.getValue() / static_cast<double>(rhs.getValue());
    }

}