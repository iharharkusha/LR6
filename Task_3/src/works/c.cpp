#include <iostream>
#include <limits>

const int INF = 200000000;

bool isLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
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

void f(char* text) {
    char* text_ptr = text;

    const unsigned int dflt_capacity = 16;
    unsigned int curr_capacity = dflt_capacity;

    char** w_ptrs = new char*[curr_capacity];
    unsigned int indx1 = 0;

    unsigned int* w_sizes = new unsigned int[curr_capacity];
    unsigned int indx2 = 0;

    unsigned int cnt = 0;
    
    while (*text_ptr != '\0') {
        
        if (isLetter(*text_ptr)) {
            text_ptr += 1;
            
            if (isLetter(*text_ptr)) {
                text_ptr -= 1;
                char* w_start = text_ptr;
                text_ptr += 1;

                text_ptr += 1;
                while (isLetter(*text_ptr)) {
                    text_ptr += 1;
                }

                char* w_end = text_ptr;
                unsigned int w_size = w_end - w_start;
                
                w_ptrs[indx1++] = w_start;
                w_sizes[indx2++] = w_size;
                cnt += 1;
            }
        } else {
            text_ptr += 1;
        }
    }

    char* text_ptr2 = text;

    if (cnt % 2) {
        cnt -= 1;
    } 
    for (unsigned int i = 0; i < cnt; i += 2) {
        char* w_ptr1 = w_ptrs[i];
        char* w_ptr2 = w_ptrs[i + 1];

        int w_size1 = w_sizes[i];
        int w_size2 = w_sizes[i + 1];

        if (w_size1 == w_size2) {
            while (w_size1--) {
                char temp = *w_ptr1;
                *w_ptr1 = *w_ptr2;
                *w_ptr2 = temp;
                w_ptr1 += 1;
                w_ptr2 += 1;
            }
        } else {
            int diff = w_size1 - w_size2;
            //первое > второе
            if (diff > 0) {
                //на примере с hello say
                //сразу выписываем то что между слов находится
                unsigned int between_sequence_size = getBetweenSequenceSize(text, w_ptr1 + w_size1, w_ptr2);
                char* between_seq = getBetweenSequence(text, w_ptr1 + w_size1, w_ptr2, between_sequence_size); 

                //записываем большее слово в массив
                char* temp_ptr = w_ptr1;
                const char* seq_end = temp_ptr + w_size1;

                char* word1 = new char[w_size1];

                unsigned int temp_indx = 0;
                while (temp_ptr != seq_end) {
                    word1[temp_indx] = *temp_ptr;
                    temp_indx += 1;
                    temp_ptr += 1;
                }

                //записываем меньшее слово в массив
                temp_ptr = w_ptr2;
                seq_end = temp_ptr + w_size2;

                char* word2 = new char[w_size2];

                temp_indx = 0;
                while (temp_ptr != seq_end) {
                    word2[temp_indx] = *temp_ptr;
                    temp_indx += 1;
                    temp_ptr += 1;
                }            

                temp_indx = 0;
                w_ptr2 -= diff;
                while (w_size2--) {
                    *w_ptr1 = word2[temp_indx];
                    *w_ptr2 = word1[temp_indx];
                    temp_indx += 1;
                    w_ptr1 += 1;
                    w_ptr2 += 1;
                }

                while(diff--) {
                    *w_ptr2 = word1[temp_indx];
                    temp_indx += 1;
                    w_ptr2 += 1;
                }

                //between
                temp_indx = 0;
                
                while (between_sequence_size--) {
                    *w_ptr1 = between_seq[temp_indx];
                    w_ptr1 += 1;
                    temp_indx += 1;
                }

                delete[] word1;
                delete[] word2;
                delete[] between_seq;
            } 
            //первое < второе
            else if (diff < 0) {
                //последловательность символов, которая разделяет два слова
                diff = abs(diff);
                unsigned int between_sequence_size = getBetweenSequenceSize(text, w_ptr1 + w_size1, w_ptr2);
                char* between_seq = getBetweenSequence(text, w_ptr1 + w_size1, w_ptr2, between_sequence_size); 

                //на примере с say hello

                //записывыем в массив второе слово целиком
                unsigned int temp_indx = 0;
                char* temp_ptr = w_ptr2;

                const char* seq_end = temp_ptr + w_size2;

                char* word2 = new char[w_size2];

                while (temp_ptr != seq_end) {
                    word2[temp_indx] = *temp_ptr;
                    temp_indx += 1;
                    temp_ptr += 1;
                }           
                //print word2 => hello 

                //меняем до меньшей длины
                temp_indx = 0;
                w_ptr2 += diff;
                while (w_size1--) {
                    *w_ptr2 = *w_ptr1;
                    *w_ptr1 = word2[temp_indx];
                    temp_indx += 1;
                    w_ptr1 += 1;
                    w_ptr2 += 1;
                }
                //print text => "hel hesay"

                //дозаполняем большее слово
                while (diff--) {
                    *w_ptr1 = word2[temp_indx];
                    w_ptr1 += 1;
                    temp_indx += 1;
                }
                //print text >= "helloesay"

                //between
                temp_indx = 0;
                while (between_sequence_size--) {
                    *w_ptr1 = between_seq[temp_indx];
                    w_ptr1 += 1;
                    temp_indx += 1;
                }
                //print text => "hello say"

                //чистим память
                delete[] word2;
                delete[] between_seq;
            }
        }
    }

    //выводим результат
    char* text_ptr3 = text;
    while (*text_ptr3 != '\0') {
        std::cout << *text_ptr3;
        text_ptr3 += 1;
    }
    std::cout << '\n';

    //чистим память
    delete[] w_ptrs;
    delete[] w_sizes;
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
        f(text);
        delete[] text; 
    }
    return 0;
}

/*
//ютф8
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
*/
