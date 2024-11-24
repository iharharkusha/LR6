#include <iostream>
#include <limits>

const int INF = 200000000;

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

void reverseText(const char* text, unsigned long text_size) {
    const unsigned long default_size = 64;
    unsigned long curr_size = default_size;

    char* words_odd = new char[default_size];
    char* words_odd_ptr = words_odd;

    char* words_even = new char[default_size];
    char* words_even_ptr = words_even;

    unsigned int total1 = 0, total2 = 0;

    const char* text_ptr = text;
    
    bool flag = true;
    while (*text_ptr != '\0') {
        if (*text_ptr == ' ') {
            if (flag) {
                *words_odd_ptr = ' '; 
                words_odd_ptr += 1;
                total1 += 1;
                flag = false;
            }
            else {
                *words_even_ptr = ' ';
                words_even_ptr += 1;
                total2 += 1;
                flag = true;
            }
        } else {
            if (flag) {
                *words_odd_ptr = *text_ptr;
                words_odd_ptr += 1;
                total1 += 1;
            } else {
                *words_even_ptr = *text_ptr; 
                words_even_ptr += 1;
                total2 += 1;
            }
        }
        text_ptr += 1;
    }
    words_odd[total1] = '\0';
    words_even[total2] = '\0';

    std::cout << words_odd << '\n'; 
    std::cout << words_even << '\n'; 
   
    char* result = new char[text_size + 1];
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
        unsigned long text_length = getTextLength(text);
        std::cout << "Длина полученного текста равна " << text_length << '\n';
        reverseText(text, text_length);
        // char* text2 = reverseText(text, text_length);
        delete[] text; 
        /*
        text = nullptr;
        std::cout << "Полученный текст:\n" << text2 << '\n';
        delete[] text2;
        */
        // text2 = nullptr;
    }
    return 0;
}