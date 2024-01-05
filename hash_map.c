#include <stdio.h>
#include <stdlib.h>

#define Capacity 50

/**
* Linked list item
* @param int key
* @param int val
* @param Item next
*/
typedef struct Item
{
    int key;
    int val;
    struct Item * next;
} item_t;
/**
* Initializes an empty list.
* @code Example: Item list; init_empty(&list);
* @param Item
*/
void init_empty(item_t ** list)
{
    item_t * root = (item_t *) malloc(sizeof(item_t));
    root = NULL;
    *list = root;
}
/**
* add item at begining of list
* @param Item list
* @param int key
* @param int val
*/
void push_begin(item_t ** list, int key, int val)
{
    item_t * new = (item_t *) malloc(sizeof(item_t));
    new->key = key;
    new->val = val;
    new->next = *list;
    *list = new;
}
/**
* add item at end of list
* @param Item list
* @param int key
* @param int val
*/
void push_end(item_t * list, int key, int val)
{
    item_t * current = list;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = (item_t *) malloc(sizeof(item_t));
    current->next->key = key;
    current->next->val = val;
    current->next->next = NULL;
    return;    
}
/**
* delte item with key out of list.
* @param Item list
* @param int key
*/
void delete_key_list(item_t ** list, int key)
{
    item_t * current = *list;
    if (current->key == key)
    {
        *list = current->next;
        return;
    }
    while (current->next != NULL)
    {
        if (current->next->key == key)
        {
            current->next = current->next->next;
            return;
        }
        current = current->next;
    }
}
/**
* remove last item and return val
* @param Item list
*/
int pop_last(item_t * list)
{
    int pop_val = -1;
    item_t * current = list;
    if (list == NULL)
    {
        return pop_val;
    }
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    pop_val = current->next->val;
    current->next = NULL;
    return pop_val;
}
/**
* remove first item and return val.
* @param Item list
*/
int pop_first(item_t ** list)
{
    int pop_val = -1;
    item_t * next = NULL;
    if (*list == NULL)
    {
        return pop_val;
    }
    pop_val = (*list)->val;
    next = (*list)->next;
    *list = next;
    return pop_val;
}
/**
* print list to console
* @param Item list
*/
void print_list(item_t * list) 
{
    item_t * current = list;
    while (current != NULL) 
    {
        printf("key: %d -> val: %d\n", current->key, current->val);
        current = current->next;
    }
}
/**
* find item with key in list and return val.
* @param Item list
* @param int key
*/
int find_key_list(item_t * list, int key)
{
    item_t * current = list;
    while (current != NULL)
    {
        if (current->key == key)
        {
            return current->val;
        }
        current = current->next;
    }
    return -1;
}
/**
* Hashmap
* @param int count
* @param int size
* @param item_t array
*/
typedef struct Hashmap
{
    int count;
    int size;
    item_t ** arr;
} hashmap_t;
/**
* hashfunktion
* @param int key
* @return int hash value
*/
int hash_fn(int key)
{
    return key%Capacity;
}
/**
* Initializes empty hashmap
* @param hashmap_t
*/
void init_map(hashmap_t ** map)
{
    item_t * arr[Capacity];
    for (int i = 0; i<Capacity; i++)
    {
        arr[i] = (item_t *) malloc(sizeof(item_t));
        init_empty(&arr[i]);
    }
    hashmap_t * new_map = (hashmap_t *) malloc(sizeof(hashmap_t));
    new_map->arr = arr;
    new_map->count = 0;
    new_map->size = Capacity;
    *map = new_map;
}
/**
* insert element into hashmap
* @param hashmap_t map
* @param int key
* @param int val
*/
void insert(hashmap_t * map,int key, int val)
{
    int hash_val = hash_fn(key);
    push_begin(&map->arr[hash_val],key,val);
    map->count += 1;
}
/**
* find key in hashmap and return value
* @param hashmap_t map
* @param int key
* @return int value
*/
int find_key(hashmap_t * map, int key)
{
    int hash_val = hash_fn(key);
    return find_key_list(map->arr[hash_val],key);
}
/**
* deletes element from hashmap
* @param hashmap_t map
* @param int key
*/
void delete_key(hashmap_t * map, int key)
{
    int hash_val = hash_fn(key);
    delete_key_list(&map->arr[hash_val],key);
    map->count -= 1;
}
/**
* calculate Hashmap load value
* @param hashmap map
* @return int load_val
*/
int load_val(hashmap_t * map)
{
    return map->count/map->size;
}

int main()
{
    hashmap_t * map;
    init_map(&map);
    insert(map,8,30);
    insert(map,58,57);
    printf("count: %d\n",map->count);
    // print_list(map->arr[8]);
    insert(map,12,68);
    printf("count: %d\n",map->count);
    printf("find key 58: %d\n",find_key(map,58));
    delete_key(map,8);
    printf("find key 8: %d\n",find_key(map,8));
    printf("count: %d\n",map->count);
}