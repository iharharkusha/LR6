#include <iostream>
#include "./header-files/iofuncs.h"
#include "./header-files/constants.h"
#include "./header-files/logic.h"

int main() {
    std::cout << "Задание 3. Написать функцию, меняющую местами все четные и нечетные слова в строке.\n";
    std::cout << "Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n";
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
        std::cout << "Введите 1 для ввода английского текста, 2 для ввода русского текста:\n";
        while (true) {
            type = readIntegerInLine();
            if (type == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            } 
            break;
        }
        printSelectedLanguage(type); 
        std::cout << "Введите желаемый текст:\n";
        char* text = readText(std::cin);
        std::cout << "Введенный вами текст:\n" << text << '\n';
        bool type_eng = true;
        if (type == 1) {
            if (getUtf8CharLength(text) == 2) {
                delete[] text;
                std::cout << "Необходимо было ввести английский текст!\n";
                continue;
            }
            std::cout << "Результат: ";
            task3(text, type_eng);
        }
        else if (type == 2) {
            if (getUtf8CharLength(text) == 2) {
                delete[] text;
                std::cout << "Необходимо было ввести русский текст!\n";
                continue;
            }
            std::cout << "Результат: ";
            type_eng = false;
            task3(text, type_eng);
        } 
        delete[] text;
    }
    return 0;
}
