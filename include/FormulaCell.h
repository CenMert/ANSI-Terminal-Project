#pragma once
#include "ValueCell.h"
#include <stdexcept>
#include <iostream>
#include <string>

/*
This Class is implemented inline becasue it is a template class.
It is not possible to separate the implementation from the declaration.
To avoid from the linker problems, the implementation is included in the header file.
	but .tpp file can be used to separate the implementation from the declaration. But I couldn't use it.
*/

namespace Spreadsheet {

    // Enumeration for supported operations
    enum class Operation { PLUS, MINUS, MUL, DIV };

    // FormulaCell class definition
    template <typename T1, typename T2>
    class FormulaCell : public Cell {
    public:
        // Constructor
        FormulaCell(ValueCell<T1>& ref1, ValueCell<T2>& ref2, Operation op)
            : m_ref1(&ref1), m_ref2(&ref2), m_operation(op) {}

        // Set formula
        void setFormula(ValueCell<T1>& ref1, ValueCell<T2>& ref2, Operation op) {
            m_ref1 = &ref1;
            m_ref2 = &ref2;
            m_operation = op;
        }

        // Evaluate formula and return the result as a string
        std::string evaluateFormula() const {
            if (!m_ref1 || !m_ref2) {
                throw std::invalid_argument("References to cells are missing.");
            }

            double val1 = static_cast<double>(m_ref1->getValue());
            double val2 = static_cast<double>(m_ref2->getValue());
            double result = 0.0;

            switch (m_operation) {
            case Operation::PLUS:
                result = val1 + val2;
                break;
            case Operation::MINUS:
                result = val1 - val2;
                break;
            case Operation::MUL:
                result = val1 * val2;
                break;
            case Operation::DIV:
                if (val2 == 0) throw std::invalid_argument("Division by zero.");
                result = val1 / val2;
                break;
            default:
                throw std::invalid_argument("Unknown operation.");
            }

            return std::to_string(result);
        }

        // Display the formula result
        void displayContent() const override {
            std::cout << "Formula Result: " << evaluateFormula() << '\n';
        }

    private:
        ValueCell<T1>* m_ref1 = nullptr; // Pointer to the first operand
        ValueCell<T2>* m_ref2 = nullptr; // Pointer to the second operand
        Operation m_operation;           // The operation to perform
    };
}
