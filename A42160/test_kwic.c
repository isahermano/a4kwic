/**
 * test_kwic.c
 *
 * COMP 2160 SECTION A02
 * INSTRUCTOR    John Braico
 * ASSIGNMENT    Assignment 4, question 1
 * AUTHOR        Isabella Hermano, 7967075
 * DATE          November 23, 2023
 *
 * PURPOSE: Source file that runs the tests
 * for the KWIC
 */

#include <stdio.h>
#include <stdlib.h>

#include "multimap.h"
#include "kwic.h"
#include "a4_tests.h"

void test_typical_cases() {
    Multimap *mm;
    char paragraph[MAX_STR_LENGTH];

    printf("\n*** Typical tests:\n\n");

    VERIFY_NOT_NULL(mm = mm_create(10));

    // tests a txt file with just simple words
    split_words("typical_test.txt", paragraph);
    VERIFY_STR("It was a very nice day for everyone It It It ", paragraph);

    // ensure words in stop list are ignored
    // verify context string is properly built for each word
    // check correctness of KWIC index
    process_words(paragraph, 1, NULL, MAX_ENTRIES, mm);
    VERIFY_INT(1, post_process_mm(mm, 1));

    VERIFY_INT(6, mm_destroy(mm));
}

void test_unusual_cases() {
    Multimap *mm;
    char paragraph[MAX_STR_LENGTH];

    printf("\n***Unusual case tests:\n\n");

    VERIFY_NOT_NULL(mm = mm_create(10));

    // test with paragraphs of special characters, nums, unusual format
    // words with different casing (upper and lower)
    // test with paragraphs with multiple spaces between words
    split_words("unusual_test.txt", paragraph);
    VERIFY_STR("hello my name is isa and this- is unusual anD tHesE Are SomE oDd wORds ", paragraph);

    process_words(paragraph, 1, NULL, MAX_ENTRIES, mm);
    VERIFY_INT(1, post_process_mm(mm, 1));

    // print_kwic(mm, "out.txt");

    VERIFY_INT(16, mm_destroy(mm));
}

void test_bounds() {
    Multimap *mm;

    printf("\n***Testing bounds:\n\n");
    // test creating mm of MAX_ENTRIES
    VERIFY_NOT_NULL(mm = mm_create(MAX_ENTRIES));

    // test upperbounds: MAX_STR_LENGTH 20000, MAX_STOP_LENGTH 1000
    
    // test lowerbounds

    // test edge cases
}

void test_invalid() {   
    // test empty paragraphs
    Multimap *mm;
    char paragraph[MAX_STR_LENGTH];
    char all_stop_paragraph[MAX_STR_LENGTH];

    printf("\n***Testing Invalids:\n\n");

    VERIFY_NOT_NULL(mm = mm_create(1));
    split_words("empty.txt", paragraph);
    VERIFY_STR("", paragraph);

    // tests paragraph with all stop words
    split_words("all_stop.txt", all_stop_paragraph);
    VERIFY_STR("all these words are stop words ", all_stop_paragraph);

    process_words(all_stop_paragraph, 1, "all_stop.txt", MAX_ENTRIES, mm);
    VERIFY_INT(1, post_process_mm(mm, 1));

    print_kwic(mm, "out.txt");
#ifdef NDEBUG
    // test paragraphs with words exceeding bounds

#endif 
}

void test_capacity() {
    // test paragraphs with high frequency of words

    // test with diff values for high frequency
}

int main() { 
  test_typical_cases();
  test_unusual_cases();
  test_bounds();
  test_capacity();
  test_invalid();

  if (0 == num_failed()) {
    printf("\nAll %d tests passed.\n", num_passed());
  } else {
    printf("\nFAILED %d of %d tests.\n", num_failed(), num_failed()+num_passed());
  }
  printf("\n*** Tests complete.\n");  
  return 0;
}