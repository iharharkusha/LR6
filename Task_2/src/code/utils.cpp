#include <iostream>
#include <cstring>
#include <limits>
#include "../header-files/constants.h"

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

int readIntegerInLine() {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }

    //очищаем буфер от символа перехода строки чтобы все работало четко
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return inputValue;
}

bool isValidUtf8Char(const char* utf8_char) {
    unsigned int len = strlen(utf8_char);

    if (len == 0 || len > 4) {
        return false;
    }   

    unsigned char c = static_cast<unsigned char>(utf8_char[0]);

    unsigned int expected_length = 1;
    if ((c & 0b11110000) == 0b11110000) {
        expected_length = 4;
    } else if ((c & 0b11100000) == 0b11100000) {
        expected_length = 3;
    } else if ((c & 0b11000000) == 0b11000000) {
        expected_length = 2;
    }

    if (len != expected_length) {
        return false;
    }

    for (unsigned int i = 1; i < len; ++i) {
        if ((utf8_char[i] & 0b11000000) != 0b10000000) {
            return false;
        }
    }
    
    return true;
}

int readUtf8CharInLine(char* utf8_char, unsigned long buffer_size) {
    std::cin.getline(utf8_char, buffer_size);

    if (!isValidUtf8Char(utf8_char)) {
        return INF;
    }

    return 0;
}

char* removeUtf8Char(const char* text, const char* utf8_char) {
    unsigned long text_length = strlen(text);

    char* result = new char[text_length + 1];
    char* result_ptr = result;

    const char* text_ptr = text;

    while (*text_ptr != '\0') {
        unsigned char c = static_cast<unsigned char>(*text_ptr);

        unsigned int char_size = 1;
        if ((c & 0b11110000) == 0b11110000) {
            char_size = 4;
        } else if ((c & 0b11100000) == 0b11100000) {
            char_size = 3;
        } else if ((c & 0b11000000) == 0b11000000) {
            char_size = 2;
        }

        if (strncmp(text_ptr, utf8_char, char_size) != 0) {
            strncpy(result_ptr, text_ptr, char_size);
            result_ptr += char_size;
        }

        text_ptr += char_size;
    }

    *result_ptr = '\0';
    return result;
}