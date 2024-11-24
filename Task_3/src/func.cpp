#include <iostream>

const int INF = 2000000000;

unsigned int l(const char* text) {
    unsigned int r = 0;
    while (*text != '\0') {
        r += 1;
        text += 1;
    }
    return r;
}

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

bool isValidUtf8Char(const char* utf8_char) {
    unsigned int len = l(utf8_char);

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

void func(const char* text, unsigned int size) {
    const char* text_ptr = text;
    const char* end = text + size; // Указатель на конец строки

    while (text_ptr < end) {
        unsigned char lead = static_cast<unsigned char>(*text_ptr);

        int char_length = 0;
        if ((lead & 0b10000000) == 0) {
            char_length = 1; 
        } else if ((lead & 0b11100000) == 0b11000000) {
            char_length = 2; 
        } else if ((lead & 0b11110000) == 0b11100000) {
            char_length = 3;
        } else if ((lead & 0b11111000) == 0b11110000) {
            char_length = 4; 
        } 

        for (int i = 0; i < char_length; ++i) {
            std::cout << text_ptr[i];
        }

        text_ptr += char_length;
    }
}

int main() {
    char text[] = "hello world";
    unsigned int size = l(text);
    /*
    std::cout << "Введите символ:\n";
    char utf8_char[16]; 
    while (true) {
        int result = readUtf8CharInLine(utf8_char, sizeof(utf8_char));
        if (result == INF) {
            std::cout << "Некорректный ввод. Пожалуйста, введите один символ UTF-8.\n";
            continue;
        }
        break;
    }  
    */ 
    func(text, size);
    return 0;
}


  const unsigned int default_capacity = 32;
    unsigned int capacity = default_capacity;

    char* words_ptrs = new char[capacity];
    const char* words_ptrs_ptr = words_ptrs;

    unsigned int* words_sizes = new unsigned int[capacity];
    const unsigned int* words_sizes_ptr = words_sizes;

    const char* text_ptr = text;

    while (*text_ptr != '\0') {

        if (isLetter(*text_ptr)) {
            unsigned int c = 0;
            c += 1;
            text_ptr += 1;
            if (isLetter(*text_ptr)) {
                const char* word_start = text_ptr - 1;
                c += 1;
                text_ptr += 1;
                while (isLetter(*text_ptr)) {
                    c += 1;
                    text_ptr += 1;
                }
                const char* word_end = text_ptr;
                unsigned int word_size = word_end - word_start;

                *words_ptrs = word_start;
                *words_sizes = word_size;

            } else {
                text_ptr += 1;
            }
        }

    }


    /*
    WOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOORKS


    void f(const char* text, unsigned int text_size) {
    const char* text_ptr = text;

    const unsigned int dflt_capacity = 16;
    unsigned int curr_capacity = dflt_capacity;

    const char** w_ptrs = new const char*[curr_capacity];
    unsigned int indx1 = 0;

    unsigned int* w_sizes = new unsigned int[curr_capacity];
    unsigned int indx2 = 0;

    unsigned int cnt = 0;
    while (*text_ptr != '\0') {
        
        if (isLetter(*text_ptr)) {
            text_ptr += 1;
            if (isLetter(*text_ptr)) {
                text_ptr -= 1;
                const char* w_start = text_ptr;
                text_ptr += 1;

                text_ptr += 1;
                while (isLetter(*text_ptr)) {
                    text_ptr += 1;
                }

                const char* w_end = text_ptr;
                unsigned int w_size = w_end - w_start;
                
                w_ptrs[indx1++] = w_start;
                w_sizes[indx2++] = w_size;
                cnt += 1;
            }
        } else {
            text_ptr += 1;
        }
    }

    for (unsigned int i = 0; i < cnt; ++i) {
        std::cout << *w_ptrs[i] << '\t'; 
    }
    std::cout << '\n';
    for (unsigned int i = 0; i < cnt; ++i) {
        std::cout << w_sizes[i] << '\t'; 
    }
    std::cout << '\n';
}
    
    */