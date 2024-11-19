#include <iostream>

int readIntegerInLine();
char* readText(std::istream& in);
bool isValidUtf8Char(const char* utf8_char);
int readUtf8CharInLine(char* utf8_char, unsigned long buffer_size);
char* removeUtf8Char(const char* text, const char* utf8_char);