#include "IntValueCell.h"
#include "DoubleValueCell.h"

namespace Spreadsheet {

    int IntValueCell::operator+(const IntValueCell& other) const {
        return m_value + other.m_value;
    }

    int IntValueCell::operator-(const IntValueCell& other) const {
        return m_value - other.m_value;
    }

    int IntValueCell::operator*(const IntValueCell& other) const {
        return m_value * other.m_value;
    }

    int IntValueCell::operator/(const IntValueCell& other) const {
        if (other.m_value == 0) throw std::invalid_argument("Division by zero.");
        return m_value / other.m_value;
    }

    int IntValueCell::getValue() const {
        return m_value;
    }

    void IntValueCell::setValue(int value) {
        m_value = value;
    }

    std::string IntValueCell::getValueAsString() const {
        return std::to_string(m_value);
    }

    std::ostream& operator<<(std::ostream& os, const IntValueCell& cell) {
        os << cell.m_value;
        return os;
    }

    void IntValueCell::displayContent() const {
        std::cout << m_value << std::endl;
    }

    // Mixed-type arithmetic operators
    double operator+(const IntValueCell& lhs, const DoubleValueCell& rhs) {
        return static_cast<double>(lhs.getValue()) + rhs.getValue();
    }

    double operator-(const IntValueCell& lhs, const DoubleValueCell& rhs) {
        return static_cast<double>(lhs.getValue()) - rhs.getValue();
    }

    double operator*(const IntValueCell& lhs, const DoubleValueCell& rhs) {
        return static_cast<double>(lhs.getValue()) * rhs.getValue();
    }

    double operator/(const IntValueCell& lhs, const DoubleValueCell& rhs) {
        if (rhs.getValue() == 0.0) throw std::invalid_argument("Division by zero.");
        return static_cast<double>(lhs.getValue()) / rhs.getValue();
    }
}
