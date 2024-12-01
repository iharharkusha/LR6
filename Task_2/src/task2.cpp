#include <iostream>
#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"
#include "../header-files/utils.h"

void task2() {
    std::cout << "Задание 2. В тексте удалить указанный символ везде, где он встречается.\n";
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
        std::cout << "Введите пожалуйста текст:\n";
        char* txt = readText(std::cin);
        std::cout << "Текст, который вы ввели:\n" << txt << '\n'; 

        std::cout << "Введите символ для удаления:\n";
        char utf8_char[16]; 

        while (true) {
            int result = readUtf8CharInLine(utf8_char, sizeof(utf8_char));
            if (result == INF) {
                std::cout << "Некорректный ввод. Пожалуйста, введите один символ UTF-8.\n";
                continue;
            }
            break;
        }

        char* txt2 = removeUtf8Char(txt, utf8_char);
        delete[] txt;
        std::cout << "Обработанный текст:\n" << txt2 << '\n';
        delete[] txt2; 
    }
}
