#include <stdio.h>

#define TABLE_SIZE 10

int hash1(int key, int table_size) {
    return key % table_size;
}

int hash2(int key, int table_size) {
    return 8 - (key % 8);
}

int doubleHash(int key, int i, int table_size) {
    return (hash1(key, 11) + i * hash2(key, 8)) % table_size;
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

void delete_linear_probing(int table[], int key, int table_size) {
    int index = search_linear_probing(table, key, table_size);

    if (index != -1) {
        table[index] = -1;
    } else {
        printf("Value %d not found, cannot delete.\n", key);
    }
}

void insert_double_hash(int table[], int key, int table_size) {
    int index = hash1(key, 11);

    if (table[index] == -1) {
        table[index] = key;
    } else {
        int i = 1;
        do {
            index = doubleHash(key, i, table_size);

            if (table[index] == -1) {
                table[index] = key;
                return;
            }

            i++;
        } while (i < table_size);
        printf("Error: Hash table is full.\n");
    }
}

int search_double_hash(int table[], int key, int table_size) {
    int index = hash1(key, 11);

    if (table[index] == key) {
        return index;
    } else if (table[index] == -1) {
        return -1; // Key not found
    } else {
        int i = 1;
        do {
            index = doubleHash(key, i, table_size);

            if (table[index] == key) {
                return index;
            }

            if (table[index] == -1) {
                return -1; // Key not found
            }

            i++;
        } while (i < table_size);
        return -1; // Key not found
    }
}

void delete_double_hash(int table[], int key, int table_size) {
    int index = search_double_hash(table, key, table_size);

    if (index != -1) {
        table[index] = -1;
    } else {
        printf("Value %d not found, cannot delete.\n", key);
    }
}

void insert_quadratic_probing(int table[], int key, int table_size) {
    int index = hash1(key, table_size);
    int i = 0;

    while (table[index] != -1) {
        i++;
        index = (index + i*i) % table_size; 
    }

    table[index] = key;
}

int search_quadratic_probing(int table[], int key, int table_size) {
    int index = hash1(key, table_size);
    int originalIndex = index;
    int i = 0;

    while (table[index] != key && table[index] != -1) {
        i++;
        index = (index + i*i) % table_size; 
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

void delete_quadratic_probing(int table[], int key, int table_size) {
    int index = search_quadratic_probing(table, key, table_size);

    if (index != -1) {
        table[index] = -1;
    } else {
        printf("Value %d not found, cannot delete.\n", key);
    }
}

void display(int table[], int table_size) {
    for (int i = 0; i < table_size; i++) {
        printf("Index %d: %d\n", i, table[i]);
    }
}

void linear_probing() {
    int elements[TABLE_SIZE];
    int size;
    int searchValue, deleteValue;

    printf("Enter the size of the element array: ");
    scanf("%d", &size);

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &elements[i]);
    }

    int hashTable[TABLE_SIZE];

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

    printf("Enter a value to delete: ");
    scanf("%d", &deleteValue);
    delete_linear_probing(hashTable, deleteValue, TABLE_SIZE);

    printf("\nAfter deletion:\n");
    display(hashTable, TABLE_SIZE);
}

void double_hashing() {
    int size;
    int result, deleteValue;
    int hashTable[11];

    printf("Enter the size of the element array: ");
    scanf("%d", &size);

    int elements[size];

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &elements[i]);
    }

    for (int i = 0; i < 11; i++) {
        hashTable[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        insert_double_hash(hashTable, elements[i], 11);
    }

    display(hashTable, 11);

    int keyToSearch;
    printf("Enter a value to search for: ");
    scanf("%d", &keyToSearch);

    result = search_double_hash(hashTable, keyToSearch, 11);

    if (result != -1) {
        printf("\nValue %d found at index %d\n", keyToSearch, result);
    } else {
        printf("\nValue %d not found\n", keyToSearch);
    }

    printf("Enter a value to delete: ");
    scanf("%d", &deleteValue);
    delete_double_hash(hashTable, deleteValue, 11);

    printf("\nAfter deletion:\n");
    display(hashTable, 11);
}

void quadratic_probing() {
    int elements[TABLE_SIZE];
    int size, deleteValue;

    printf("Enter the size of the element array: ");
    scanf("%d", &size);

    printf("Enter %d elements:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &elements[i]);
    }

    int hashTable[TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        insert_quadratic_probing(hashTable, elements[i], TABLE_SIZE);
    }

    display(hashTable, TABLE_SIZE);

    int searchValue;
    printf("Enter a value to search for: ");
    scanf("%d", &searchValue);

    int result = search_quadratic_probing(hashTable, searchValue, TABLE_SIZE);

    if (result != -1) {
        printf("\nValue %d found at index %d\n", searchValue, result);
    } else {
        printf("\nValue %d not found\n", searchValue);
    }

    printf("Enter a value to delete: ");
    scanf("%d", &deleteValue);
    delete_quadratic_probing(hashTable, deleteValue, TABLE_SIZE);

    printf("\nAfter deletion:\n");
    display(hashTable, TABLE_SIZE);
}

int main() {
    int choice;

    do {
        printf("\nEnter your choice\n");
        printf("\n1.Linear Probing\n2.Double Hashing\n3.Quadratic Probing\n4.Exit\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                linear_probing();
                break;
            case 2:
                double_hashing();
                break;
            case 3:
                quadratic_probing();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice");
        }
    } while (choice != 4);

    return 0;
}
