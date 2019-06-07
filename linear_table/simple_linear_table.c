#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINEAR_LIST_LEN 100

struct simple_linear_list
{
  int *data;
  int num; // table length
  int cur_pos; // current position, -1 is invalid
};

// functions:

struct simple_linear_list *_create(int length); // create table;
void _drop(struct simple_linear_list *linear_table);
int _length(const struct simple_linear_list * linear_table); // get table length
int _search(const int key, const struct simple_linear_list *linear_table); // search the position of key
int _locate(const int index, const struct simple_linear_list *linear_table); // locate the index item's position in the table
int *_get_data(const int index, const struct simple_linear_list *linear_table); // get the index item key
bool _set_data(const int index, const int data, struct simple_linear_list *linear_table); // set the index item key
bool _insert(const int index, const int data, struct simple_linear_list *linear_table); // insert
bool _remove(const int index, struct simple_linear_list *linear_table);
bool _is_empty(const struct simple_linear_list *linear_table);
bool _is_full(const struct simple_linear_list *linear_table);
bool _copy_list(const struct simple_linear_list *src_linear_table, struct simple_linear_list *dst_linear_table);
bool _sort(struct simple_linear_list *linear_table);

int _length(const struct simple_linear_list * linear_table)
{
  if (NULL == linear_table)
  {
    return 0;
  }

  return linear_table->cur_pos + 1;
}

bool _is_empty(const struct simple_linear_list *linear_table)
{
  // TODO if NULL
  return -1 == linear_table->cur_pos;
}

bool _is_full(const struct simple_linear_list *linear_table)
{
  // TODO if NULL
  return linear_table->num == linear_table->cur_pos + 1;
}

int _search(const int key, const struct simple_linear_list *linear_table)
{
  // TODO if NULL
  int i = 0;

  for (i = 0; i <= linear_table->cur_pos; i++)
  {
    if (key == linear_table->data[i])
    {
      return i + 1;
    }
  }

  return 0;
}

int _locate(const int index, const struct simple_linear_list *linear_table)
{
  // TODO if NULL

  if (index >= 1 && index <= linear_table->cur_pos + 1)
  {
    return index;
  }

  return 0;
}


int *_get_data(const int index, const struct simple_linear_list *linear_table)
{
  // TODO if NULL

  if (index <= 0 || index > linear_table->cur_pos + 1)
  {
    return NULL;
  }

  return linear_table->data + index - 1;
}

bool _set_data(const int index, const int data, struct simple_linear_list *linear_table)
{
  // TODO if NULL

  if (index <= 0 || index > linear_table->cur_pos + 1)
  {
    return false;
  }
  
  linear_table->data[index - 1] = data;
  return true;
}

bool _insert(const int index, const int data, struct simple_linear_list *linear_table)
{
  if (_is_full(linear_table))
  {
    return false;
  }

  if (index < 0 || index > linear_table->cur_pos + 1)
  {
    return false;
  }

  int i = 0;

  for (i = linear_table->cur_pos; i >= index; i--)
  {
    linear_table->data[i+1] = linear_table->data[i];
  }

  linear_table->data[index] = data;
  linear_table->cur_pos++;

  return true;
}

bool _remove(const int index, struct simple_linear_list *linear_table)
{
  if (_is_empty(linear_table))
  {
    return false;
  }

  if (index <= 0 || index > linear_table->cur_pos + 1)
  {
    return false;
  }

  int i = 0;

  for (i = index; i <= linear_table->cur_pos; i++)
  {
    linear_table[i-1] = linear_table[i];
  }

  linear_table->cur_pos--;

  return true;
}

void _drop(struct simple_linear_list *linear_table)
{
  if (NULL == linear_table || NULL == linear_table->data)
  {
    return (void)0;
  }

  free(linear_table->data);
  linear_table->data = NULL;

  free(linear_table);
  linear_table = NULL;

  return (void)0;
}

struct simple_linear_list *_create(int length)
{
  if (length < 0 || length > MAX_LINEAR_LIST_LEN)
  {
    return NULL;
  }

  struct simple_linear_list *list = NULL;

  list = (struct simple_linear_list *)malloc(sizeof(struct simple_linear_list));

  if (NULL == list)
  {
    return NULL;
  }

  list->data = NULL;
  list->data = (int *)malloc(sizeof(int) * length);

  if (NULL == list->data)
  {
    free(list);
    list = NULL;
    return NULL;
  }

  memset(list->data, 0, sizeof(int) * length);
  list->num = length;
  list->cur_pos = -1;
  
  return list;
}

void print_list(const struct simple_linear_list *linear_table)
{
  int i = 0;
  int len = _length(linear_table);

  for (i = 0; i < len; i++)
  {
    printf("list [%d] = %d\n", i, *_get_data(i+1, linear_table));
  }

  return (void)0;
}

int main(void)
{

  struct simple_linear_list *list = _create(MAX_LINEAR_LIST_LEN);

  printf("init length is %d\n", _length(list));

  _insert(0, 23, list);
  _insert(0, 24, list);
  _insert(0, 28, list);
  _insert(0, 13, list);

  printf("insert length is %d\n", _length(list));
  print_list(list);

  _drop(list);

  return 0;
}
