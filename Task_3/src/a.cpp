#include <iostream>

bool isLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
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
            if (diff > 0) {
                unsigned int between_sequence_size = getBetweenSequenceSize(text, w_ptr1 + w_size1, w_ptr2);
                char* between_seq = getBetweenSequence(text, w_ptr1 + w_size1, w_ptr2, between_sequence_size); 

                char* temp_ptr = w_ptr1;
                temp_ptr += w_size2;
                const char* seq_end = temp_ptr + diff;

                char* seq = new char[diff];

                unsigned int temp_indx = 0;
                while (temp_ptr != seq_end) {
                    seq[temp_indx] = *temp_ptr;
                    temp_indx += 1;
                    temp_ptr += 1;
                }

                temp_indx = 0;
                temp_ptr = w_ptr2;
                seq_end = temp_ptr + w_size2;
                char* word2 = new char[w_size2];

                while (temp_ptr != seq_end) {
                    word2[temp_indx] = *temp_ptr;
                    temp_indx += 1;
                    temp_ptr += 1;
                }            

                temp_indx = 0;
                w_ptr2 -= diff;
                while (w_size2--) {
                    *w_ptr2 = *w_ptr1;
                    *w_ptr1 = word2[temp_indx];
                    temp_indx += 1;
                    w_ptr1 += 1;
                    w_ptr2 += 1;
                }

                //between
                temp_indx = 0;
                
                while (between_sequence_size--) {
                    *w_ptr1 = between_seq[temp_indx];
                    w_ptr1 += 1;
                    temp_indx += 1;
                }

                temp_indx = 0;

                while (diff--) {
                    *w_ptr2 = seq[temp_indx];
                    w_ptr2 += 1;
                    temp_indx += 1;
                }
            } else if (diff < 0) {
                diff = abs(diff);
                unsigned int between_sequence_size = getBetweenSequenceSize(text, w_ptr1 + w_size1, w_ptr2);
                char* between_seq = getBetweenSequence(text, w_ptr1 + w_size1, w_ptr2, between_sequence_size); 

                char* temp_ptr = w_ptr2;
                temp_ptr += w_size1;
                const char* seq_end = temp_ptr + diff;

                char* seq = new char[diff];

                unsigned int temp_indx = 0;
                while (temp_ptr != seq_end) {
                    seq[temp_indx] = *temp_ptr;
                    temp_indx += 1;
                    temp_ptr += 1;
                }

                temp_indx = 0;
                temp_ptr = w_ptr2;
                seq_end = temp_ptr + w_size2;
                char* word2 = new char[w_size2];

                while (temp_ptr != seq_end) {
                    word2[temp_indx] = *temp_ptr;
                    temp_indx += 1;
                    temp_ptr += 1;
                }            

                temp_indx = 0;
                w_ptr2 += diff;
                while (w_size1--) {
                    *w_ptr2 = *w_ptr1;
                    *w_ptr1 = word2[temp_indx];
                    temp_indx += 1;
                    w_ptr1 += 1;
                    w_ptr2 += 1;
                }

                temp_indx = 0;

                while (diff--) {
                    *w_ptr1 = seq[temp_indx];
                    w_ptr1 += 1;
                    temp_indx += 1;
                }

                //between
                temp_indx = 0;
                
                while (between_sequence_size--) {
                    *w_ptr1 = between_seq[temp_indx];
                    w_ptr1 += 1;
                    temp_indx += 1;
                }
            }
        }
    }

    char* text_ptr3 = text;
    while (*text_ptr3 != '\0') {
        std::cout << *text_ptr3;
        text_ptr3 += 1;
    }

    std::cout << '\n';
}

int main() {
    char text5[] = "Hello egor pidr123privet poka";
    std::cout << "Тестовый текст: " << text5 << '\n'; 
    std::cout << "Результат: ";
    f(text5);
    return 0;
}

