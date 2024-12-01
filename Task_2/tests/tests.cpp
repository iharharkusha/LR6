#include <gtest/gtest.h>
#include <cstring>
#include "../header-files/utils.h"

// Тест 1: Проверка на корректную работу с одним байтом (ASCII символ)
TEST(RemoveUtf8CharTest, RemoveSingleAsciiChar) {
    const char* text = "Hello, world!";
    const char* utf8_char = "H";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "ello, world!");
    delete[] result;
}

// Тест 2: Проверка удаления UTF-8 символа длиной 2 байта (например, '©')
TEST(RemoveUtf8CharTest, RemoveTwoByteUtf8Char) {
    const char* text = "Тестовый © пример";
    const char* utf8_char = "©";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "Тестовый  пример");
    delete[] result;
}

// Тест 3: Проверка удаления UTF-8 символа длиной 3 байта (например, '€')
TEST(RemoveUtf8CharTest, RemoveThreeByteUtf8Char) {
    const char* text = "Цена в евро: €20";
    const char* utf8_char = "€";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "Цена в евро: 20");
    delete[] result;
}

// Тест 4: Проверка удаления UTF-8 символа длиной 4 байта (например, '💩')
TEST(RemoveUtf8CharTest, RemoveFourByteUtf8Char) {
    const char* text = "Эмодзи: 💩";
    const char* utf8_char = "💩";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "Эмодзи: ");
    delete[] result;
}

// Тест 5: Проверка, когда символ не найден в строке
TEST(RemoveUtf8CharTest, RemoveNonExistentUtf8Char) {
    const char* text = "Тестовая строка";
    const char* utf8_char = "©";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "Тестовая строка");
    delete[] result;
}

// Тест 6: Проверка на строку без UTF-8 символов
TEST(RemoveUtf8CharTest, RemoveFromTextWithoutUtf8Chars) {
    const char* text = "Привет Мир!";
    const char* utf8_char = "🙂";  // Emoji, 4 байта
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "Привет Мир!");
    delete[] result;
}

// Тест 7: Проверка на пустую строку
TEST(RemoveUtf8CharTest, EmptyStringTest) {
    const char* text = "";
    const char* utf8_char = "H";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "");
    delete[] result;
}

// Тест 8: Крайний случай — строка состоит из только одного символа
TEST(RemoveUtf8CharTest, SingleCharacterString) {
    const char* text = "A";
    const char* utf8_char = "A";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "");
    delete[] result;
}

// Тест 9: Крайний случай — строка состоит из нескольких одинаковых символов
TEST(RemoveUtf8CharTest, RemoveRepeatedUtf8Char) {
    const char* text = "AAA";
    const char* utf8_char = "A";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "");
    delete[] result;
}

// Тест 10: Проверка на строку с несколькими разными символами
TEST(RemoveUtf8CharTest, RemoveMultipleDifferentUtf8Chars) {
    const char* text = "аво1ваылождолда43";
    const char* utf8_char = "1";
    char* result = removeUtf8Char(text, utf8_char);
    EXPECT_STREQ(result, "авоваылождолда43");
    delete[] result;
}
