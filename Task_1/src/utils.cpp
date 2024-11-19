#include <iostream>
#include <limits>
#include "./header-files/constants.h"
#include "./header-files/utils.h"

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

char* readLine(std::istream& in) {
    const unsigned long buffer_size = 128;
    unsigned long curr_size = buffer_size;
    char* buffer = new char[curr_size];
    unsigned long indx = 0;
    char ch;
    while (in.get(ch) && ch != '\n' && ch != EOF) {
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

/*
char* readLine() {
    const int buffer_size = 128;
    int curr_size = buffer_size;
    char* buffer = new char[curr_size];
    unsigned long indx = 0;
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
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
*/

void getNumbersSubStrings(char* line, unsigned long size) {
    unsigned long capacity = 8;
    unsigned long count = 0;
    char** numbers = new char*[capacity];
    for (unsigned long i = 0; i < size;) {
        if (std::isdigit(line[i])) {
            unsigned long start = i;
            while (i < size && std::isdigit(line[i])) {
                i++;
            }
            unsigned long end = i;
            unsigned long length = end - start;
            char* number = new char[length + 1];
            std::copy(line + start, line + end, number);
            number[length] = '\0';

            if (count == capacity) {
                capacity *= 2;
                char** new_numbers = new char*[capacity];
                std::copy(numbers, numbers + count, new_numbers);
                delete[] numbers;
                numbers = new_numbers;
            }
            numbers[count++] = number;
        } else {
            i++;
        }
    }
    if (!count) {
        std::cout << '\n' << "Нет чисел в заданной строке\n\n"; 
    } else {
        std::cout << '\n' << "Найденные числа в строке:\n";
        for (unsigned long i = 0; i < count; ++i) {
            std::cout << numbers[i] << '\n';
        }
        std::cout << '\n';
    }
    for (unsigned long i = 0; i < count; ++i) {
        delete[] numbers[i];
        numbers[i] = nullptr;
    }
    delete[] numbers;
    numbers = nullptr;
}