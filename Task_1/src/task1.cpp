#include <iostream>
#include <cstring>
#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"
#include "../header-files/utils.h"

void task1() {
    std::cout << "Задание 1. Из строки, состоящей из букв, цифр, запятых, точек, знаков + (плюс) ";
    std::cout << "и – (минус), выделить подстроку, которая соответствует записи целого числа.\n\n";
    while (true) {
        std::cout << "Введите 1 для запуска программы, 0 для ее завершения:\n";
        int type = readIntegerInLine();
        if (type != 1 && type != 0) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        if (type == 0) {
            break;
        }
        
        std::cout << "Введите пожалуйста строку:\n";
        char* line = readLine(std::cin);
        std::cout << "Введенная вами строка:\n" << line << '\n';

        unsigned long size = strlen(line);
        getNumbersSubStrings(line, size);
        delete[] line;
        line = nullptr;
    }
}


