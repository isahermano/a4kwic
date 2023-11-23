/**
 * kwic.c
 *
 * COMP 2160 SECTION A02
 * INSTRUCTOR    John Braico
 * ASSIGNMENT    Assignment 4, question 1
 * AUTHOR        Isabella Hermano, 7967075
 * DATE          November 23, 2023
 *
 * PURPOSE: Source file contains the implementations
 * of the KWIC algorithm.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "multimap.h"
#include "kwic.h"
#include "boolean.h"

// Reads an entire paragraph from the input text file at a time into a string, even 
// if it spans multiple lines in the text file.

void read_in_file(char *in_file, char *stop_list, char *paragraph, int entry_length, Multimap *mm) {
    assert(NULL != in_file);

    FILE *in = fopen(in_file, "r");

    if(NULL != in) {
        char line[MAX_STR_LENGTH];
        int para_index = 1;

        while(NULL != fgets(line, MAX_STR_LENGTH, in)) {
            // for each paragraph, process the words
            if(feof(in) > 0 || strcmp(line, "\n") == 0) {
                process_words(paragraph, para_index, stop_list, entry_length, mm);
                para_index++;
                paragraph[0] = '\0';
            } else {
                // remove extra spaces and punctuation (that isn't a - or ')
                char delimiters[] = " \n";
                char *tokens = strtok(line, delimiters);
                while(NULL != tokens) {
                    int index = 0;
                    int word_length = strlen(tokens);
                    char curr_word[word_length + 1];
                    for(int i = 0; i < word_length; i++) {
                        if(isalnum(tokens[i]) || tokens[i] == '-' || tokens[i] == '\'') {
                            curr_word[index++] = tokens[i];
                        }
                    }
                    curr_word[index] = ' ';
                    curr_word[index + 1] = '\0';
                    strcat(paragraph, curr_word);
                    tokens = strtok(NULL, delimiters);
                }
            }
        }
        fclose(in);
    }
}

void split_words(char *in_file, char *paragraph) {
    FILE *in = fopen(in_file, "r");

    if(NULL != in) {
        char line[MAX_STR_LENGTH];
        paragraph[0] = '\0';
        while(NULL != fgets(line, MAX_STR_LENGTH, in)) {
            // remove extra spaces and punctuation (that isn't a - or ')
            char delimiters[] = " \n";
            char *tokens = strtok(line, delimiters);
            while(NULL != tokens) {
                int index = 0;
                int word_length = strlen(tokens);
                char curr_word[word_length + 1];
                for(int i = 0; i < word_length; i++) {
                    if(isalnum(tokens[i]) || tokens[i] == '-' || tokens[i] == '\'') {
                        curr_word[index++] = tokens[i];
                    }
                }
                curr_word[index] = ' ';
                curr_word[index + 1] = '\0';
                strcat(paragraph, curr_word);
                tokens = strtok(NULL, delimiters);
            }
        }
        fclose(in);
    }
}

// The stop list file contains one word per line. Treat each line as a word; 
// there is no error checking.

void read_stop_file(char *stop_file, char *stop_list) {
    assert(NULL != stop_file);

    FILE *in = fopen(stop_file, "r"); 
    char str[MAX_STOP_LENGTH];
    int count = 0;

    if(NULL != in && count < MAX_STOP_LENGTH) {
        while(NULL != fgets(str, MAX_STOP_LENGTH, in)) { // keep reading until reach newline
            strncat(stop_list, str, MAX_STOP_LENGTH); // use strncat instead of strncpy to avoid overwriting line
            count++;
        }
        stop_list[strlen(stop_list)] = '\0';
        fclose(in);
    }
}

int is_stop_word(char *stop_list, char *word) {
    char delimeters[] = " \n";
    char *stop_tokens = strtok(stop_list, delimeters);
 
    if(NULL != stop_list) {
        while(NULL != stop_tokens) {    
        if(strcasecmp(stop_tokens, word) == 0) {
                return TRUE;
            }
            stop_tokens = strtok(NULL, delimeters);
        }
    }
    return FALSE;
}

// Check if the word is in the stop list. If it is, do not process it further, 
// and go on to the next word. Otherwise, subtract the length of the word from the 
// maximum entry length and divide it by two. This is the amount of characters allowed
// on either side of the word for context. Build a context string by fitting as many words 
// as possible, from before the word, and after the word, with a single space between them, 
// without exceeding the amount characters allowed on each side. Using the word as the key, 
// and the paragraph number and the string you built as the value, add it to the index multimap.

int process_words(char *paragraph, int para_index, char *stop_list, int entry_length, Multimap *mm) {    
    assert(NULL != mm);
    assert(para_index >= 1);
    assert(entry_length > 0);
    
    char delimeters[] = " \n";
    char *token = strtok(paragraph, delimeters);

    while(NULL != token) {
        int word_length = strlen(token);
        if(is_stop_word(stop_list, token) == 0) {
            int context_length = (entry_length - strlen(token))/2;
            char context_string[entry_length + 1]; // subtract length of word fr max entry len, and divide by 2
            context_string[0] = '\0';
            
            char left_sentence[context_length];
            char right_sentence[context_length];
            left_sentence[0] = '\0';
            right_sentence[0] = '\0';
            char *curr_token = token;

            // add words to lhs of context string
            int i = 0;
            while(i < context_length && curr_token > paragraph) {
                curr_token--;
                strncpy(left_sentence, curr_token, context_length - 1);
                i++;
            }
            strcat(context_string, left_sentence);
            
            // add target word
            strcat(context_string, token);

            // add words to rhs of context string
            curr_token = token + word_length;
            int k = 0;
            while(k < context_length && *curr_token != '\0') {
                strncpy(right_sentence, curr_token, context_length -1);
            }

            strcat(context_string, right_sentence);

            // insert value to context string
            mm_insert_value(mm, token, para_index, context_string);
        }
        token = strtok(NULL, delimeters);
    }
    return 1;
}

// Count the total number of values for all keys, and for each key, if its frequency 
// (number of values / total number of values) is greater than the maximum frequency, 
// remove it from the multimap.

int post_process_mm(Multimap *mm, int max_frequency) {
    assert(NULL != mm);
    assert(max_frequency >= 0);

    if(NULL == mm || max_frequency < 0) {
        return -1;
    }

    int pos = 0;
    while(pos < mm->num_keys) {
        char *curr_key = mm->keys[pos].key; // keep track of curr key

        if(mm_count_values(mm, curr_key) > max_frequency) {
            mm_remove_key(mm, curr_key);
        } 
        pos++;
    }
    return 1; 
}

void print_kwic(Multimap *mm, char *out_file) {
    assert(NULL != mm);

    char key[MAX_KEY_LENGTH];
    int num_values;
    Value values[MAX_ENTRIES];
    FILE *out = fopen(out_file, "w"); 

    // print to console
    printf("%-20s %-4s %s\n", "WORD", "PARA", "CONTEXT");
    printf("%-20s %-4s %s\n", "====", "====", "=======");

    // write to out file
    if(NULL != out) {
        fprintf(out, "%-20s %-4s %s\n", "WORD", "PARA", "CONTEXT");
        fprintf(out, "%-20s %-4s %s\n", "====", "====", "=======");
    }

    if (mm_get_first_key(mm, key, MAX_KEY_LENGTH) > 0) {
      do {
        num_values = mm_get_values(mm, key, values, MAX_ENTRIES);
        for(int i = 0; i < num_values; i++) {
            // print to console
            printf("%-23s %d %s\n", key, values[i].num, values[i].str);

            // write to out file
            if(NULL != out) {
                fprintf(out, "%-23s %d %s\n", key, values[i].num, values[i].str);
            }
        }
      } while (mm_get_next_key(mm, key, MAX_KEY_LENGTH) > 0);
    }
    fclose(out);
}

void kwic(char *in_file, char *out_file, char *stop_file, int max_frequency, int entry_length, int max_index) {
    Multimap *mm = mm_create(max_index);
    char *stop_list = malloc(MAX_STOP_LENGTH);
    char *paragraph = malloc(MAX_STR_LENGTH);

    if(stop_file != NULL) {
        read_stop_file(stop_file, stop_list);
    } else {
        stop_list = NULL;
    }

    read_in_file(in_file, stop_list, paragraph, entry_length, mm);
    post_process_mm(mm, max_frequency);
    print_kwic(mm, out_file);
    
    free(paragraph);
    free(stop_list);
    mm_destroy(mm);
}
