#include <iostream>
#include <cstring>
#include <limits>

const int INF = 2000000000;

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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return inputValue;
}

char* removeUtf8Char(const char* text, const char* utf8_char) {
    size_t text_length = strlen(text);          // Длина исходного текста

    // Выделяем память под результат (в худшем случае длина останется неизменной)
    char* result = new char[text_length + 1];
    char* result_ptr = result;

    const char* text_ptr = text;

    while (*text_ptr != '\0') {
        unsigned char c = static_cast<unsigned char>(*text_ptr);

        size_t char_size = 1;
        if ((c & 0b11110000) == 0b11110000) {
            char_size = 4;
        } else if ((c & 0b11100000) == 0b11100000) {
            char_size = 3;
        } else if ((c & 0b11000000) == 0b11000000) {
            char_size = 2;
        }

        // Сравниваем текущий символ с удаляемым
        if (strncmp(text_ptr, utf8_char, char_size) != 0) {
            // Копируем символ, если он не равен удаляемому
            strncpy(result_ptr, text_ptr, char_size);
            result_ptr += char_size;
        }

        text_ptr += char_size; // Переходим к следующему символу
    }

    *result_ptr = '\0'; // Завершаем строку
    return result;
}


bool isValidUtf8Char(const char* utf8_char) {
    size_t len = strlen(utf8_char);

    // Проверяем длину (UTF-8 символ может занимать от 1 до 4 байтов)
    if (len == 0 || len > 4) {
        return false;
    }

    unsigned char c = static_cast<unsigned char>(utf8_char[0]);

    // Определяем длину символа по первому байту
    size_t expected_length = 1;
    if ((c & 0b11110000) == 0b11110000) {
        expected_length = 4;
    } else if ((c & 0b11100000) == 0b11100000) {
        expected_length = 3;
    } else if ((c & 0b11000000) == 0b11000000) {
        expected_length = 2;
    }

    // Если фактическая длина не совпадает с ожидаемой, символ некорректен
    if (len != expected_length) {
        return false;
    }

    // Проверяем, что последующие байты соответствуют формату UTF-8 (10xxxxxx)
    for (size_t i = 1; i < len; ++i) {
        if ((utf8_char[i] & 0b11000000) != 0b10000000) {
            return false;
        }
    }

    return true;
}

// Функция для ввода символа UTF-8
int readUtf8CharInLine(char* utf8_char, size_t buffer_size) {
    // Считываем строку с ограничением на длину
    std::cin.getline(utf8_char, buffer_size);

    // Проверяем валидность
    if (!isValidUtf8Char(utf8_char)) {
        return INF;
    }

    return 0; // Успех
}

int main() {
    std::cout << "Задание 2. В тексте удалить указанный символ везде, где он встречается.\n";
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
        std::cout << "Введите пожалуйста текст:\n";
        char* txt = readText(std::cin);
        std::cout << "Текст, который вы ввели:\n"; 
        std::cout << txt << '\n';

        std::cout << "Введите символ для удаления:\n";
        char utf8_char[16]; // Буфер для символа

        while (true) {
            int result = readUtf8CharInLine(utf8_char, sizeof(utf8_char));
            if (result == INF) {
                std::cout << "Некорректный ввод. Пожалуйста, введите один символ UTF-8.\n";
                continue;
            }
            break;
        }

        char* txt2 = removeUtf8Char(txt, utf8_char);
        std::cout << "Обработанный текст:\n";
        std::cout << txt2 << '\n';

        delete[] txt;
        delete[] txt2; 
    }
    return 0;
}
