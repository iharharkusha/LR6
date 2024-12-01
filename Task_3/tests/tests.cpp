#include <gtest/gtest.h>
#include "../header-files/logic.h"

TEST(GetUtf8CharLengthTests, HandlesAscii) {
    EXPECT_EQ(getUtf8CharLength("A"), 1);
}

TEST(GetUtf8CharLengthTests, HandlesTwoByteUtf8) {
    EXPECT_EQ(getUtf8CharLength("Д"), 2);
}

TEST(IsLetterTests, RecognizesEnglishLetter) {
    EXPECT_TRUE(isLetter("A"));
    EXPECT_TRUE(isLetter("z"));
}

TEST(IsLetterTests, RecognizesRussianLetter) {
    const char ru_letter1[] = { (char)0xD0, (char)0x90, '\0' }; // А
    const char ru_letter2[] = { (char)0xD1, (char)0x8F, '\0' }; // я
    EXPECT_TRUE(isLetter(ru_letter1));
    EXPECT_TRUE(isLetter(ru_letter2));
}

TEST(IsLetterTests, RejectsNonLetter) {
    EXPECT_FALSE(isLetter("1"));
    EXPECT_FALSE(isLetter("@"));
}

TEST(DecreaseIfOddTests, HandlesEven) {
    EXPECT_EQ(decreaseIfOdd(4), 4);
}

TEST(DecreaseIfOddTests, HandlesOdd) {
    EXPECT_EQ(decreaseIfOdd(5), 4);
}

TEST(SwitchEqualWordsTests, SwapsEqualLengthWords) {
    char word1[] = "test";
    char word2[] = "swap";
    const unsigned int ptr_byte_step = 1;

    switchEqualWords(4, word1, word2, ptr_byte_step);

    EXPECT_STREQ(word1, "swap");
    EXPECT_STREQ(word2, "test");
}

TEST(GetTextDataTests, ExtractsWordsFromText) {
    char text[] = "Hello world Hello world";
    const unsigned int default_capacity = 10;
    char** ptrs_to_words = new char*[default_capacity];
    unsigned int* ptrs_to_sizes = new unsigned int[default_capacity];
    unsigned int current_capacity = default_capacity;
    unsigned int words_total = 0, temp_indx = 0;
    unsigned int ptr_byte_step = 1; // English

    getTextData(text, ptrs_to_words, ptrs_to_sizes, current_capacity, words_total, temp_indx, ptr_byte_step);

    ASSERT_EQ(words_total, 4);
    EXPECT_EQ(ptrs_to_sizes[0], 5);  // "Hello"
    EXPECT_EQ(ptrs_to_sizes[1], 5);  // "world"
    EXPECT_STREQ(ptrs_to_words[0], text);
    EXPECT_STREQ(ptrs_to_words[1], text + 6);  // Skips ' '

    delete[] ptrs_to_words;
    delete[] ptrs_to_sizes;
}

TEST(WholeTaskTests, EnglishTextTest) {
    bool type_eng = true;
    char text[] = "Hello, world my123name is Andrey Arshavin and ^&& i like to eat bananas"; 
    char expected_result[] = "world, Hello name123my Andrey is and Arshavin ^&& i to like bananas eat";
    task3(text, type_eng);

    EXPECT_STREQ(text, expected_result);
}

TEST(WholeTaskTests, RussianTextTest) {
    bool type_eng = false;
    char text[] = "Егор Кузьменков нормальный тип или он любит играть в бильярд или он любит компот с черешни вот в чем вопрос!!! Михаил Литвин - известбываший в космосе, впадина"; 
    char expected_result[] = "Кузьменков Егор тип нормальный он или играть любит в или бильярд любит он черешни с компот чем в вот Михаил!!! вопрос известбываший - Литвин в впадина, космосе";
    task3(text, type_eng);

    EXPECT_STREQ(text, expected_result);
}