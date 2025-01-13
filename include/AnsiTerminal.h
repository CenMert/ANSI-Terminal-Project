#pragma once
#include <string>
#include <termios.h>
#include <unistd.h>

namespace Spreadsheet {

    // Class for managing terminal display and input
    class AnsiTerminal {
    public:
        // Constructor: Sets up the terminal for non-blocking input
        AnsiTerminal();

        // Destructor: Restores original terminal settings
        ~AnsiTerminal();

        // Print text at a specific position
        void printAt(int row, int col, const std::string& text);

        // Print text with inverted background at a specific position
        void printInvertedAt(int row, int col, const std::string& text);

        // Clear the terminal screen
        void clearScreen();

        // Get a single character input from the terminal
        char getKeystroke();

        // Get special keys (e.g., arrow keys, Alt+key combinations)
        char getSpecialKey();

    private:
        struct termios originalTio; // Holds the original terminal settings
    };

} // namespace Spreadsheet
