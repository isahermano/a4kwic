#ifndef MULTIMAP_H
#define MULTIMAP_H

#define MAX_KEY_LENGTH 31
#define MAX_VALUE_LENGTH 81

typedef struct VALUE { int num; char str[MAX_VALUE_LENGTH]; } Value;
typedef struct MULTIMAP Multimap; 

typedef struct VALUE_NODE {
  Value value;
  struct VALUE_NODE *next;
} ValueNode;

typedef struct KEY_AND_VALUES {
  char key[MAX_KEY_LENGTH];
  int num_values;
  ValueNode *head;
} KeyAndValues;

struct MULTIMAP {
  int num_keys;
  int max_keys;
  int index;
  KeyAndValues *keys;
};

Multimap *mm_create(int max_keys);
int mm_insert_value(Multimap *mm, char *key, int value_num, char *value_str);
int mm_count_keys(Multimap *mm);
int mm_count_values(Multimap *mm, char *key);
int mm_get_values(Multimap *mm, char *key, Value values[], int max_values);
int mm_remove_key(Multimap *mm, char *key);
void mm_print(Multimap *mm);
int mm_destroy(Multimap *mm);
int mm_get_first_key(Multimap *mm, char *key, int length);
int mm_get_next_key(Multimap *mm, char *key, int length);

#endif