#ifndef KWIC_H
#define KWIC_H

#include "multimap.h"

#define MAX_STR_LENGTH 20000
#define MAX_STOP_LENGTH 1000
#define MAX_ENTRIES 100 // max entries for EACH WORD in index

void read_in_file(char *in_file, char *stop_list, char *paragraph, int entry_length, Multimap *mm);
void split_words(char *in_file, char *paragraph);
void read_stop_file(char *stop_file, char *stop_list);
int process_words(char *paragraph, int para_index, char *stop_list, int entry_length, Multimap *mm);
int post_process_mm(Multimap *mm, int max_frequency);
void print_kwic(Multimap *mm, char *out_file);
void kwic(char *in_file, char *out_file, char *stop_file, int max_frequency, int entry_length, int max_index);

#endif 