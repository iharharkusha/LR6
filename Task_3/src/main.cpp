#include <iostream>
#include <limits>

const int INF = 200000000;

unsigned int getUtf8CharLength(const char* utf8_char) { 
    unsigned char c = static_cast<unsigned char>(utf8_char[0]);

    unsigned int expected_length = 1;
    if ((c & 0b11110000) == 0b11110000) {
        expected_length = 4;
    } else if ((c & 0b11100000) == 0b11100000) {
        expected_length = 3;
    } else if ((c & 0b11000000) == 0b11000000) {
        expected_length = 2;
    }

    return expected_length;
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

void getTextData(char* text, char**& ptrs_to_words, unsigned int*& ptrs_to_sizes, unsigned int& current_capacity, unsigned int& words_total, unsigned int& temp_indx, const unsigned int& ptr_byte_step) {
    char* text_ptr = text;

    char* word_start;
    char* word_end; 

    while (*text_ptr != '\0') {

        if (isLetter(text_ptr)) {
            text_ptr += ptr_byte_step;

            if (isLetter(text_ptr)) {
                text_ptr -= ptr_byte_step;
                word_start = text_ptr;
                text_ptr += ptr_byte_step;

                text_ptr += ptr_byte_step;
                while (isLetter(text_ptr)) {
                    text_ptr += ptr_byte_step;   
                }
                word_end = text_ptr;

                unsigned int word_size = (word_end - word_start) / ptr_byte_step;
                
                //если вдруг места не хватает, то выделяем больше памяти
                if (temp_indx + 2 >= current_capacity) {
                    current_capacity *= 2;
                    char** ptrs_to_words_new = new char*[current_capacity];
                    for (unsigned int i = 0; i < current_capacity / 2; ++i) {
                        ptrs_to_words_new[i] = ptrs_to_words[i];
                    }
                    unsigned int* ptrs_to_sizes_new = new unsigned int[current_capacity];
                    for (unsigned int i = 0; i < current_capacity / 2; ++i) {
                        ptrs_to_sizes_new[i] = ptrs_to_sizes[i];
                    }

                    delete[] ptrs_to_words;
                    ptrs_to_words = ptrs_to_words_new;
                    delete[] ptrs_to_sizes; 
                    ptrs_to_sizes = ptrs_to_sizes_new;
                }
                ptrs_to_words[temp_indx] = word_start;
                ptrs_to_sizes[temp_indx] = word_size;
                
                ++temp_indx;
                ++words_total;
            }
        } 

        else {
            ++text_ptr;
        }
    }
}

unsigned int decreaseIfOdd(unsigned int total) {return total % 2 ? --total : total;}

void printText(const char* text) {
    while (*text != '\0') {
        std::cout << *text;
        ++text;
    }
    std::cout << '\n';
}

void switchEqualWords(int word_size, char* ptr_word1, char* ptr_word2, const unsigned int& ptr_byte_step) {
    word_size *= ptr_byte_step;
    while (word_size--) {
        char temp = *ptr_word1;
        *ptr_word1 = *ptr_word2;
        *ptr_word2 = temp;
        ++ptr_word1;
        ++ptr_word2;    
    }
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
    char* between_sequence = new char[size];

    unsigned int indx = 0;
    while (start != end) {
        between_sequence[indx] = *start;
        start += 1;
        indx += 1;
    }

    return between_sequence;
}

char* extractWordFromCollocation(int word_size, char* start_ptr, char* end_ptr) {
    char* extractedWord = new char[word_size];

    unsigned int temp_indx = 0;
    while (start_ptr != end_ptr) {
        extractedWord[temp_indx] = *start_ptr;
        temp_indx += 1;
        start_ptr += 1;
    }

    return extractedWord;
}

inline void swapChars(int& word_size, char*& ptr1, char*& ptr2, char*& word_arr, unsigned int& temp_indx, char* extra_ptr = nullptr, char* extra_ptr_end = nullptr) {
    if (extra_ptr == nullptr && extra_ptr_end == nullptr) {
        while (word_size--) {
            *ptr2 = *ptr1;
            *ptr1 = word_arr[temp_indx];
            ++temp_indx;
            ++ptr1;
            ++ptr2;
        }
    } else {
        while (word_size--) {
            *ptr1 = *extra_ptr;
            *ptr2 = word_arr[temp_indx];
            ++temp_indx;
            ++ptr1;
            ++ptr2;

            if (extra_ptr != extra_ptr_end) {
                ++extra_ptr;
            }
        }
    }
}

void completeBiggestWord(int& symbols_to_complete, char*& ptr, char*& word_array, unsigned int& temp_indx) {
    while (symbols_to_complete--) {
        *ptr = word_array[temp_indx];
        ptr += 1;
        temp_indx += 1;
    }
}

void completeBetweenSequence(unsigned int between_sequence_size, char* ptr, char* between_sequence) {
    unsigned int temp_indx = 0;
    while (between_sequence_size--) {
        *ptr = between_sequence[temp_indx];
        ptr += 1;
        temp_indx += 1;
    }
}

void swapWordsInText(const char* text, char**& ptrs_to_words, unsigned int*& ptrs_to_sizes, unsigned int words_total, unsigned int& temp_indx, const unsigned int& ptr_byte_step) {
    for (unsigned int i = 0; i < words_total; i += 2) {
        char* ptr_word1 = ptrs_to_words[i];
        char* ptr_word2 = ptrs_to_words[i + 1];
        int size_word1 = ptrs_to_sizes[i], size_word2 = ptrs_to_sizes[i + 1];

        //если размеры двух слов равны
        if (size_word1 == size_word2) {
            switchEqualWords(size_word1, ptr_word1, ptr_word2, ptr_byte_step);
        } 
        //если размеры двух слов разные
        else {
            int sizes_difference = size_word1 - size_word2;
            //сразу выписываем то что между слов находится
            unsigned int between_sequence_size = getBetweenSequenceSize(text, ptr_word1 + size_word1 * ptr_byte_step, ptr_word2);
            char* between_seq = getBetweenSequence(text, ptr_word1 + size_word1 * ptr_byte_step, ptr_word2, between_sequence_size); 

            const char* seq_end;

            temp_indx = 0;

            size_word1 *= ptr_byte_step;
            size_word2 *= ptr_byte_step;
            sizes_difference *= ptr_byte_step;

            if (sizes_difference > 0) {
                char* word1 = extractWordFromCollocation(size_word1, ptr_word1, ptr_word1 + size_word1);

                char* extra_ptr = ptr_word2;     
                char* temp_ptr = extra_ptr + size_word2;
                ptr_word2 -= sizes_difference;

                swapChars(size_word2, ptr_word1, ptr_word2, word1, temp_indx, extra_ptr, temp_ptr);
                completeBiggestWord(sizes_difference, ptr_word2, word1, temp_indx);
                completeBetweenSequence(between_sequence_size, ptr_word1, between_seq);

                delete[] word1;
            } 

            else if (sizes_difference < 0) {
                sizes_difference = abs(sizes_difference);

                char* word2 = extractWordFromCollocation(size_word2, ptr_word2, ptr_word2 + size_word2);   

                ptr_word2 += sizes_difference;

                swapChars(size_word1, ptr_word1, ptr_word2, word2, temp_indx);
                completeBiggestWord(sizes_difference, ptr_word1, word2, temp_indx);           
                completeBetweenSequence(between_sequence_size, ptr_word1, between_seq);

                delete[] word2;
            }

            delete[] between_seq;
        }
    }
}

void printSelectedLanguage(int type) {
    if (type == 1) {
        std::cout << "Выбранный язык ввода: английский 🏴󠁧󠁢󠁥󠁮󠁧󠁿\n";
    } else if (type == 2) {
        std::cout << "Выбранный язык ввода: русский 🇷🇺\n";
    }
}

void task3(char* text, bool type_eng) {
    const unsigned int default_capacity = 32;
    unsigned int current_capacity = default_capacity;

    char** ptrs_to_words = new char*[current_capacity];
    unsigned int* ptrs_to_sizes = new unsigned int[current_capacity];

    unsigned int words_total = 0;
    unsigned int temp_indx = 0;

    unsigned int ptr_byte_step;
    if (type_eng) {
        ptr_byte_step = 1;
    } else {
        ptr_byte_step = 2;
    }
    
    getTextData(text, ptrs_to_words, ptrs_to_sizes, current_capacity, words_total, temp_indx, ptr_byte_step);
    words_total = decreaseIfOdd(words_total);
    swapWordsInText(text, ptrs_to_words, ptrs_to_sizes, words_total, temp_indx, ptr_byte_step);

    printText(text); 

    delete[] ptrs_to_words;
    delete[] ptrs_to_sizes;
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
