/* Implementation file for HashTable.
 *
 * After ten collisions (ie. ten items in
 * a particular hash items list) the hash
 * table will expand to the maxCollision
 * plus the growthFactor.
 */

#include <stdlib.h>
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

typedef size_t (*hash_function)(void *);
typedef size_t (*compare_equal)(void *, void *);

typedef struct Item
{
    void *key;
    void *value;
    struct Item *next;
} Item;

typedef struct HashTable
{
    size_t size;
    size_t maxCollisions;
    size_t growthFactor;
    Item **table;
    hash_function hf;
    compare_equal eq;
} HashTable;

/*
 * Creates instance of HashTable with size and
 * function given to create a hash of the key.
 *
 * The hash function is given so that any variable
 * or structure etc can be used as the key in the
 * key value pairing.
 */
HashTable *hashtable_initialize(size_t, size_t, size_t, hash_function, compare_equal);

/*
 * Finds the value in the table in O(n) speed given
 * key, and returns value as void * or void * 0 on
 * error.
 */
void *hashtable_get(HashTable *, void *);

/*
 * Free's all memory in the hash table.  Returns
 * success status 1 true, 0 false.
 */
int hashtable_destroy(HashTable *);

/*
 * Resizes the hash table to a different
 * size.
 */
int hashtable_resize(HashTable *, size_t);

/*
 * Adds a new key value pair to the table.  If
 * key already exists it will overwrite it.
 */
int hashtable_add(HashTable *, void *, void *);

/*
 * Free's and deletes memory of a item and clears
 * the spot in the table.
 */
int hashtable_remove(HashTable *, void *);

#endif

HashTable *hashtable_initialize(size_t size, size_t mc, size_t gf, hash_function fn, compare_equal efn)
{
    size_t i;
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));

    if (ht == NULL)
    {
        printf("\nERROR: Cannot create hash table. Terminating...");
        exit(EXIT_FAILURE); // well... any other implementation could be added, instead of this.
    }

    ht->hf = fn;
    ht->eq = efn;
    ht->size = size;
    ht->maxCollisions = mc;
    ht->growthFactor = gf;

    ht->table = (Item **)malloc(size * sizeof(Item *));

    if (ht->table == NULL)
    {
        printf("\nERROR: Cannot create hash table. Terminating...");
        exit(EXIT_FAILURE); // well... any other implementation could be added, instead of this.
    }

    for (i = 0; i < size; i++)
    {
        ht->table[i] = 0;
    }

    return (ht);
}

void *hashtable_get(HashTable *ht, void *key)
{
    size_t hash = ht->hf(key);
    Item *next = ht->table[hash % ht->size];

    while (next)
    {
        if (ht->eq(next->key, key))
        {
            return (next->value);
        }
        else
        {
            next = next->next;
        }
    }

    return ((void *)0);
}

int hashtable_destroy(HashTable *ht)
{

    // Avoiding runtime errors. Return a successful destroy when the
    // hashtable has not been initialized using the 'hashtable_initialize'
    // function.

    if (ht == NULL)
        return 1;

    // From here we know the hashtable has been properly initialized so,
    // we continue computations.

    size_t i;

    for (i = 0; i < ht->size; i++)
    {
        free(ht->table[i]);
    }

    free(ht->table);
    free(ht);

    return (1);
}

int hashtable_resize(HashTable *ht, size_t size)
{
    HashTable *newht = hashtable_initialize(size, ht->maxCollisions, ht->growthFactor, ht->hf, ht->eq);
    int i;
    Item *next;

    // Re-enter all the items again into the new hashtable
    // with the new size.
    for (i = 0; i < ht->size; i++)
    {
        if (ht->table[i])
        {
            for (next = ht->table[i]; next; next = next->next)
            {
                hashtable_add(newht, next->key, next->value);
            }
        }

        hashtable_remove(ht, ht->table[i]->key);
    }

    free(ht->table);
    newht->size = ht->size;
    newht->table = ht->table;

    return (1);
}

int hashtable_add(HashTable *ht, void *key, void *value)
{
    size_t hash = ht->hf(key);
    Item *next = ht->table[hash % ht->size];
    size_t i = 0;

    while (next)
    {
        // Replace data if key is same
        if (ht->eq(next->key, key))
        {
            next->value = value;
            return (1);
        }

        next = next->next;
        i++;
    }

    next = (Item *)malloc(sizeof(Item));

    // Making sure that memory was properly allocated for 'next'.
    if (next == NULL)
    {
        printf("\nERROR: Insufficient memory. Terminating....");
        exit(EXIT_FAILURE); // some other implementation could be used here.
    }

    next->key = key;
    next->value = value;
    next->next = ht->table[hash % ht->size];
    ht->table[hash % ht->size] = next;

    if (i >= ht->maxCollisions)
    {
        hashtable_resize(ht, ht->size + ht->growthFactor);
    }

    return (1);
}

int hashtable_remove(HashTable *ht, void *key)
{
    size_t hash = ht->hf(key);
    Item *next = ht->table[hash % ht->size];
    Item *prev = 0;

    while (next)
    {
        if (ht->eq(next->key, key))
        {
            if (prev)
            {
                prev->next = next->next;
            }
            else
            {
                ht->table[hash % ht->size] = next->next;
            }

            free(next);

            return (1);
        }

        prev = next;
        next = next->next;
    }

    return (0);
}

size_t hash(void *key)
{
    size_t hash = 0;
    const char *k = (const char *)key;

    while (*k)
    {
        hash = hash * 37 + *k++;
    }
    return hash;
}

size_t mycompare_equal(void *key1, void *key2)
{
    if ((const char *)key1 == (const char *)key2)
        return (1);
    else
        return (0);
}

int main(int argc, char **argv)
{
    HashTable *ht = hashtable_initialize(1, 1, 2, hash, mycompare_equal);

    hashtable_add(ht, (void *)"1", (void *)"ONE");
    hashtable_add(ht, (void *)"2", (void *)"TWO");
    hashtable_add(ht, (void *)"3", (void *)"THREE");
    hashtable_add(ht, (void *)"4", (void *)"FOUR");

    printf("ht[\"1\"]: %s\n", (const char *)hashtable_get(ht, (void *)"1"));
    printf("ht[\"2\"]: %s\n", (const char *)hashtable_get(ht, (void *)"2"));
    printf("ht[\"3\"]: %s\n", (const char *)hashtable_get(ht, (void *)"3"));
    printf("ht[\"4\"]: %s\n", (const char *)hashtable_get(ht, (void *)"4"));

    // Add more to inact resize

    hashtable_add(ht, (void *)"5", (void *)"FIVE");
    hashtable_add(ht, (void *)"6", (void *)"SIX");
    hashtable_add(ht, (void *)"7", (void *)"SEVEN");
    hashtable_add(ht, (void *)"8", (void *)"EIGHT");

    printf("ht[\"5\"]: %s\n", (const char *)hashtable_get(ht, (void *)"5"));
    printf("ht[\"6\"]: %s\n", (const char *)hashtable_get(ht, (void *)"6"));
    printf("ht[\"7\"]: %s\n", (const char *)hashtable_get(ht, (void *)"7"));
    printf("ht[\"8\"]: %s\n", (const char *)hashtable_get(ht, (void *)"8"));

    hashtable_destroy(ht);

    return (0);
}