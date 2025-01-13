#pragma once
#include "ValueCell.h"
#include <string>



namespace Spreadsheet{

    class StringValueCell : public ValueCell<std::string> {
    public:
        explicit StringValueCell(const std::string& value);

        // Overloaded operator
        std::string operator+(const StringValueCell& other) const;

        // Set
        void setValue(const std::string value) override;

        // Get
        std::string getValue() const override;

        // Implementation of getValueAsString
        std::string getValueAsString() const override;

        // Terminal method
        void displayContent() const override;

    private:
        std::string m_value; // Stores the string value
    };

}
