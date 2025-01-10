// Created: 2025-01-10 16:00:00
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Entry {
    struct Entry *prev;
    char name[50];
    char lastname[50];
    int age;
    int pesel;
    int gender;
    struct Entry *next;
} Entry;

Entry* allocateEntry() {
    // Allocates memory for a new entry
    Entry *new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->prev = nullptr;
    new_entry->next = nullptr;
    return new_entry;
}

void freeEntry(Entry *entry) {
    free(entry);
}

int main_menu(Entry *first_entry) {
    bool exit = false;
    while(!exit) {
        wprintf(L"Simple personal data manager\n");
        wprintf(L"--- Main menu ---\n");
        wprintf(L"1. Add new entry\n");
        wprintf(L"2. Remove entry\n");
        wprintf(L"3. Find entry\n");
        wprintf(L"4. Display all entries\n");
        wprintf(L"5. Browse entries\n");
        wprintf(L"6. Sort entries\n");
        wprintf(L"7. Save entries to the file\n");
        wprintf(L"8. Load entries from the file\n");
        wprintf(L"9. Exit\n");
        wprintf(L"Select an option and press enter: ");
        int option;
        scanf("%d", &option);
        switch(option) {
            case 1:
                // add_entry(first_entry);
                    continue;
            case 2:
                // remove_entry(first_entry);
                    continue;
            case 3:
                // find_entry(first_entry);
                    continue;
            case 4:
                // display_entries(first_entry);
                    continue;
            case 5:
                // browse_entries(first_entry);
                    continue;
            case 6:
                // sort_entries(first_entry);
                    continue;
            case 7:
                // save_entries(first_entry);
                    continue;
            case 8:
                // load_entries(first_entry);
                    continue;
            case 9:
                exit = true;
            continue;
            default:
                // resolve_easter_egg(option);
                    wprintf(L"Invalid option\n");
            continue;
        }
    }
    return 0;
}

int main(void) {
    #ifdef _WIN32
        char clear[3] = "cls";
    #else
        char clear[5] = "clear";
    #endif

    printf("Loading program\n");
    setlocale(LC_ALL, "");
    Entry *first_entry = nullptr;
    system(clear);
    scanf("#");
    return 0;
}