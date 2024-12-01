#pragma once

unsigned int getUtf8CharLength(const char* utf8_char);
bool isLetter(const char* s);
void getTextData(char* text, char**& ptrs_to_words, unsigned int*& ptrs_to_sizes, unsigned int& current_capacity, unsigned int& words_total, unsigned int& temp_indx, const unsigned int& ptr_byte_step);
unsigned int decreaseIfOdd(unsigned int total);
void switchEqualWords(int word_size, char* ptr_word1, char* ptr_word2, const unsigned int& ptr_byte_step);
unsigned int getBetweenSequenceSize(const char* text, const char* start, const char* end);
char* getBetweenSequence(const char* text, const char* start, const char* end, const unsigned int size);
char* extractWordFromCollocation(int word_size, char* start_ptr, char* end_ptr);
inline void swapChars(int& word_size, char*& ptr1, char*& ptr2, char*& word_arr, unsigned int& temp_indx, char* extra_ptr = nullptr, char* extra_ptr_end = nullptr);
void completeBiggestWord(int& symbols_to_complete, char*& ptr, char*& word_array, unsigned int& temp_indx);
void completeBetweenSequence(unsigned int between_sequence_size, char* ptr, char* between_sequence);
void swapWordsInText(const char* text, char**& ptrs_to_words, unsigned int*& ptrs_to_sizes, unsigned int words_total, unsigned int& temp_indx, const unsigned int& ptr_byte_step);
void task3(char* text, bool type_eng);