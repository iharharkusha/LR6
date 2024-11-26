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

bool isLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

void switchEqualWords(int word_size, char* ptr_word1, char* ptr_word2) {
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

char* extractWordFromCollocation(const int word_size, char* start_ptr, const char* end_ptr) {
    char* extractedWord = new char[word_size];

    unsigned int temp_indx = 0;
    while (start_ptr != end_ptr) {
        extractedWord[temp_indx] = *start_ptr;
        temp_indx += 1;
        start_ptr += 1;
    }

    return extractedWord;
}

unsigned int decreaseIfOdd(unsigned int total) {return total % 2 ? --total : total;}

void completeBiggestWord(int& letters_to_complete, char*& ptr, char*& word_array, unsigned int& temp_indx) {
    while (letters_to_complete--) {
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

void swapChars(int& word_size, char*& ptr1, char*& ptr2, char*& word_arr, unsigned int& temp_indx, char* extra_ptr = nullptr, char* extra_ptr_end = nullptr) {
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

void swapWordsInText(const char* text, char**& ptrs_to_words, unsigned int*& ptrs_to_sizes, unsigned int words_total, unsigned int& temp_indx) {
    for (unsigned int i = 0; i < words_total; i += 2) {
        char* ptr_word1 = ptrs_to_words[i];
        char* ptr_word2 = ptrs_to_words[i + 1];
        int size_word1 = ptrs_to_sizes[i], size_word2 = ptrs_to_sizes[i + 1];

        //если размеры двух слов равны
        if (size_word1 == size_word2) {
            switchEqualWords(size_word1, ptr_word1, ptr_word2);
        } 
        //если размеры двух слов разные
        else {
            int sizes_difference = size_word1 - size_word2;
            //сразу выписываем то что между слов находится
            unsigned int between_sequence_size = getBetweenSequenceSize(text, ptr_word1 + size_word1, ptr_word2);
            char* between_seq = getBetweenSequence(text, ptr_word1 + size_word1, ptr_word2, between_sequence_size); 

            const char* seq_end;

            temp_indx = 0;
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

void getTextData(char* text, char**& ptrs_to_words, unsigned int*& ptrs_to_sizes, unsigned int& current_capacity, unsigned int& words_total, unsigned int& temp_indx) {
    char* text_ptr = text;

    char* word_start;
    char* word_end; 
    while (*text_ptr != '\0') {

        if (isLetter(*text_ptr)) {
            ++text_ptr;

            if (isLetter(*text_ptr)) {
                --text_ptr;
                word_start = text_ptr;
                ++text_ptr;

                ++text_ptr;
                while (isLetter(*text_ptr)) {
                    ++text_ptr;
                }
                word_end = text_ptr;

                unsigned int word_size = word_end - word_start;
                
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

void printText(const char* text) {
    while (*text != '\0') {
        std::cout << *text;
        ++text;
    }
    std::cout << '\n';
}

void task3(char* text) {
    const unsigned int default_capacity = 4;
    unsigned int current_capacity = default_capacity;

    char** ptrs_to_words = new char*[current_capacity];
    unsigned int* ptrs_to_sizes = new unsigned int[current_capacity];

    unsigned int words_total = 0;
    unsigned int temp_indx = 0;
    
    getTextData(text, ptrs_to_words, ptrs_to_sizes, current_capacity, words_total, temp_indx);
    
    words_total = decreaseIfOdd(words_total);
    swapWordsInText(text, ptrs_to_words, ptrs_to_sizes, words_total, temp_indx);

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
        std::cout << "Введите желаемый текст:\n";
        char* text = readText(std::cin);
        std::cout << "Введенный вами текст:\n" << text << '\n';
        std::cout << "Результат: ";
        task3(text);
        delete[] text; 
    }
    return 0;
}