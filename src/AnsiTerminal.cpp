#include "AnsiTerminal.h"
#include <iostream>
#include <stdexcept>

namespace Spreadsheet {

    // Constructor: Configure terminal for non-canonical input
    AnsiTerminal::AnsiTerminal() {
        if (tcgetattr(STDIN_FILENO, &originalTio) != 0) {
            throw std::runtime_error("Failed to get terminal attributes");
        }
        struct termios newTio = originalTio;
        newTio.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
        if (tcsetattr(STDIN_FILENO, TCSANOW, &newTio) != 0) {
            throw std::runtime_error("Failed to set terminal attributes");
        }
    }

    // Destructor: Restore terminal settings
    AnsiTerminal::~AnsiTerminal() {
        tcsetattr(STDIN_FILENO, TCSANOW, &originalTio);
    }

    // Print text at a specific row and column
    void AnsiTerminal::printAt(int row, int col, const std::string& text) {
        std::cout << "\033[" << row << ";" << col << "H" << text << std::flush;
    }

    // Print text with inverted background at a specific position
    void AnsiTerminal::printInvertedAt(int row, int col, const std::string& text) {
        std::cout << "\033[" << row << ";" << col << "H\033[7m" << text << "\033[0m" << std::flush;
    }

    // Clear the terminal screen
    void AnsiTerminal::clearScreen() {
        std::cout << "\033[2J\033[H" << std::flush;
    }

    // Get a single character from terminal input
    char AnsiTerminal::getKeystroke() {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) != 1) {
            throw std::runtime_error("Failed to read input");
        }
        return ch;
    }

    // Handle arrow keys and special inputs
    char AnsiTerminal::getSpecialKey() {
        char ch = getKeystroke();

        if (ch == '\033') { // Escape sequence
            char nextCh;
            if (read(STDIN_FILENO, &nextCh, 1) == 0) return '\033';
            if (nextCh == '[') {
                char arrowKey;
                if (read(STDIN_FILENO, &arrowKey, 1) == 1) {
                    switch (arrowKey) {
                        case 'A': return 'U'; // Up arrow
                        case 'B': return 'D'; // Down arrow
                        case 'C': return 'R'; // Right arrow
                        case 'D': return 'L'; // Left arrow
                    }
                }
            }
        }
        return ch;
    }

} // namespace Spreadsheet
