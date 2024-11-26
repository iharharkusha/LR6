#include <iostream>
#include <limits>

const int INF = 200000000;

bool isLetter(const char* s) {
    unsigned char firstByte = s[0];
    unsigned char secondByte = s[1];

    // Проверяем диапазоны для русского алфавита в UTF-8
    if (firstByte == 0xD0) { // Диапазон для 'А'-'п'
        return (secondByte >= 0x90 && secondByte <= 0xBF);
    } else if (firstByte == 0xD1) { // Диапазон для 'р'-'я' + 'ё'
        return (secondByte >= 0x80 && secondByte <= 0x8F);
    } else {
        return (*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z');
    }

    return false;
}

unsigned int getBetweenSequenceSize(const char* text, const char* start, const char* end) {
    unsigned int size = 0;

    while (start != end) {
        size += 1;
        start += 1;
    }

    return size;
}

char* getBetweenSequence(const char* text, const char* start, const char* end, const unsigned int size) {
    char* result_sequence = new char[size];

    unsigned int indx = 0;
    while (start != end) {
        result_sequence[indx] = *start;
        start += 1;
        indx += 1;
    }

    return result_sequence;
}

void f_ru(char* text, unsigned int text_size) {
    
    
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

unsigned long getTextLength(const char* text) {
    unsigned long length = 0;
    while (*text != '\0') {
        length += 1;
        text += 1;
    }
    return length;
}

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
        std::cout << "Введите желаемый текст:\n";
        char* text = readText(std::cin);
        std::cout << "Введенный вами текст:\n" << text << '\n';
        std::cout << "Результат: ";
        const unsigned int text_size = getTextLength(text);
        f_ru(text, text_size);
        delete[] text; 
    }
    return 0;
}

