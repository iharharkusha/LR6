#include <iostream>
#include <limits>
#include "../../general/header-files/constants.h"

void printSelectedLanguage(const int type) {
    if (type == 1) {
        std::cout << "Выбранный язык ввода: английский 🏴󠁧󠁢󠁥󠁮󠁧󠁿\n";
    } else if (type == 2) {
        std::cout << "Выбранный язык ввода: русский 🇷🇺\n";
    }
}

void printText(const char* text) {
    while (*text != '\0') {
        std::cout << *text;
        ++text;
    }
    std::cout << '\n';
}