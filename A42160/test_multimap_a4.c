/**
 * test_multimap_a4.c
 *
 * COMP 2160 SECTION A02
 * INSTRUCTOR    John Braico
 * ASSIGNMENT    Assignment 4, question 1
 * AUTHOR        Isabella Hermano, 7967075
 * DATE          November 23, 2023
 *
 * PURPOSE: Source file that runs the new tests
 * for the multimap (OBTAINED FROM A3 SOLUTIONS)
 */

#include <stdio.h>

#include "multimap.h"
#include "a4_tests.h"

void test_typical_cases() {
    Multimap *mm;
    char first_key[MAX_KEY_LENGTH] = "";
    char next_key[MAX_KEY_LENGTH] = "";

    printf("\n*** Typical tests:\n\n");

    VERIFY_NOT_NULL(mm = mm_create(5));
    // test getting first and next key
    VERIFY_INT(1, mm_insert_value(mm, "abc", 123, "cde"));
    VERIFY_INT(1, mm_get_first_key(mm, first_key, 4));
    VERIFY_STR("abc", first_key);
    VERIFY_INT(1, mm_insert_value(mm, "efg", 123, "cde"));
    VERIFY_INT(1, mm_get_next_key(mm, next_key, 4)); 
    VERIFY_STR("efg", next_key);

    // test getting first and next key after removing next
    VERIFY_INT(1, mm_remove_key(mm, "efg"));
    VERIFY_INT(1, mm_get_first_key(mm, first_key, 4));
    VERIFY_INT(0, mm_get_next_key(mm, next_key, 4));

    // test getting first and next key after removing all keys
    VERIFY_INT(1, mm_remove_key(mm, "abc"));
    VERIFY_INT(0, mm_get_first_key(mm, first_key, 4));
    VERIFY_INT(0, mm_get_next_key(mm, next_key, 4));
}

void test_unusual_cases() {
    Multimap *mm;
    char first_key[MAX_KEY_LENGTH] = "";
    char next_key[MAX_KEY_LENGTH] = "";

    printf("\n***Unusual case tests:\n\n");

    VERIFY_NOT_NULL(mm = mm_create(5));
    // tests operations on a key that doesn't exist
    VERIFY_INT(0, mm_get_first_key(mm, first_key, 3));
    VERIFY_INT(0, mm_get_next_key(mm, next_key, 3));
    VERIFY_STR("", first_key);
    VERIFY_STR("", next_key);

    // passing in symbols as keys
    VERIFY_INT(1, mm_insert_value(mm, "?", 123, "abc"));
    VERIFY_INT(1, mm_insert_value(mm, "!", 123, "abc"));
    VERIFY_INT(1, mm_get_first_key(mm, first_key, 3));
    VERIFY_STR("!", first_key);
    VERIFY_INT(1, mm_get_next_key(mm, next_key, 3));
    VERIFY_STR("?", next_key);
}

void test_bounds() {
    Multimap *mm;
    char first_key[MAX_KEY_LENGTH] = "";
    char next_key[MAX_KEY_LENGTH] = "";

    printf("\n***Testing bounds:\n\n");

    VERIFY_NOT_NULL(mm = mm_create(5));
    // insert/obtain keys 1 less than max
    VERIFY_INT(1, mm_insert_value(mm, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx", 123, "efg"));
    VERIFY_INT(1, mm_get_first_key(mm, first_key, MAX_KEY_LENGTH - 1));
    VERIFY_STR("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx", first_key);

    // insert/obtain keys equal to max
    VERIFY_INT(1, mm_insert_value(mm, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", 123, "hij"));
    VERIFY_INT(1, mm_get_next_key(mm, next_key, MAX_KEY_LENGTH));
    VERIFY_STR("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", next_key);
}

void test_invalid() {
  printf("\n***Testing Invalids:\n\n");
#ifdef NDEBUG
    Multimap *mm;
    char first_key[MAX_KEY_LENGTH] = "";

    VERIFY_NOT_NULL(mm = mm_create(5));
    // pass in NULL key
    VERIFY_INT(-1, mm_insert_value(mm, NULL, 123, "efg"));
    VERIFY_INT(0, mm_get_first_key(mm, first_key, MAX_KEY_LENGTH));
    VERIFY_STR("", first_key);
#endif
}

int main() {
  printf("*** Starting tests...\n");
  
  test_typical_cases();
  test_unusual_cases();
  test_bounds();
  //test_capacity();
#ifdef NDEBUG
  test_invalid();
#endif
  
  if (0 == num_failed()) {
    printf("\nAll %d tests passed.\n", num_passed());
  } else {
    printf("\nFAILED %d of %d tests.\n", num_failed(), num_failed()+num_passed());
  }
  printf("\n*** Tests complete.\n");  
  return 0;
}
