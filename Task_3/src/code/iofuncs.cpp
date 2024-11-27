#include <iostream>
#include <limits>
#include "../header-files/constants.h"

int readIntegerInLine() {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return inputValue;
}

void printSelectedLanguage(const int type) {
    if (type == 1) {
        std::cout << "Выбранный язык ввода: английский 🏴󠁧󠁢󠁥󠁮󠁧󠁿\n";
    } else if (type == 2) {
        std::cout << "Выбранный язык ввода: русский 🇷🇺\n";
    }
}

char* readText(std::istream& in) {
    const unsigned long buffer_size = 128;
    unsigned long curr_size = buffer_size;
    char* buffer = new char[curr_size];
    unsigned long indx = 0;

    char ch;
    while (in.get(ch) && ch != '\n') {
        if (indx + 1 >= curr_size) {
            curr_size *= 2;
            char* new_buffer = new char[curr_size];
            std::copy(buffer, buffer + indx, new_buffer);
            delete[] buffer;
            buffer = new_buffer;
        }
        buffer[indx++] = ch;
    }
    buffer[indx] = '\0';
    return buffer;
}

void printText(const char* text) {
    while (*text != '\0') {
        std::cout << *text;
        ++text;
    }
    std::cout << '\n';
}