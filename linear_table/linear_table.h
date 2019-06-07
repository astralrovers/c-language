#ifndef __LINEAR_TABLE_H__
#define __LINEAR_TABLE_H__
#include <stdbool.h>

// functions:

void *create(int len); // create table;
int length(void * linear_table); // get table length
int search(void *key); // search the position of key
int locate(int index); // locate the index item's position in the table
void *get_data(int index); // get the index item key
void *set_data(int index, void *data); // set the index item key
bool insert(int index, void *data); // insert
bool remove(int index, void *data);
bool is_empty(void);
bool is_full(void);
void copy_list(void);
void sort(void);

#endif // #ifdef __LINEAR_TABLE_H__
