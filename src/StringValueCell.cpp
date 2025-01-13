#include "StringValueCell.h"
#include <iostream>
namespace Spreadsheet{

    // Constructor
    StringValueCell::StringValueCell(const std::string& value) : m_value(value) {}

    // Overloaded operator
    std::string StringValueCell::operator+(const StringValueCell& other) const {
        return this->m_value + other.m_value;
    }

    // Set method
    void StringValueCell::setValue(const std::string value) {
        this->m_value = value;
    }

    // Get method
    std::string StringValueCell::getValue() const {
        return this->m_value;
    }

    // Implementation of getValueAsString
    std::string StringValueCell::getValueAsString() const {
        return m_value;
    }

    // Terminal method
    void StringValueCell::displayContent() const {
        std::cout << m_value << std::endl;
    }
}
