#include <stdio.h>

#define TABLE_SIZE 10

int hash1(int key, int table_size) {
    return key % table_size;
}

void insert_linear_probing(int table[], int key, int table_size) {
    int index = hash1(key, table_size);

    while (table[index] != -1) {
        index = (index + 1) % table_size; // Linear probing
    }

    table[index] = key;
}

int search_linear_probing(int table[], int key, int table_size) {
    int index = hash1(key, table_size);
    int originalIndex = index;

    while (table[index] != key && table[index] != -1) {
        index = (index + 1) % table_size; // Linear probing
        if (index == originalIndex) {
            return -1; // Key not found
        }
    }

    if (table[index] == key) {
        return index; // Key found at index
    } else {
        return -1; // Key not found
    }
}

void display(int table[], int table_size) {
    for (int i = 0; i < table_size; i++) {
        printf("Index %d: %d\n", i, table[i]);
    }
}

int main() {
    int elements[TABLE_SIZE];
    int size;
    int searchValue;
    printf("Enter the size of the element array: ");
    scanf("%d", &size);

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &elements[i]);
    }

    int hashTable[TABLE_SIZE];

    // Initialize hash table with -1 (indicating empty slots)
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        insert_linear_probing(hashTable, elements[i], TABLE_SIZE);
    }

    display(hashTable, TABLE_SIZE);

   
    printf("Enter a value to search for: ");
    scanf("%d", &searchValue);

    int result = search_linear_probing(hashTable, searchValue, TABLE_SIZE);

    if (result != -1) {
        printf("\nValue %d found at index %d\n", searchValue, result);
    } else {
        printf("\nValue %d not found\n", searchValue);
    }

    return 0;
}
