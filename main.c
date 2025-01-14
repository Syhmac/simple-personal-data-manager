// Created: 2025-01-10 16:00:00
// Version: 1.1
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#if _WIN32
    #define CLEAR "cls"
#elif __gnu_linux__
    #define CLEAR "clear"
    #include <wchar.h>
#endif

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

void printEntry(Entry *entry) {
    // Prints the entry
    wprintf(L"Name: %hs\n", entry->name);
    wprintf(L"Lastname: %hs\n", entry->lastname);
    wprintf(L"Age: %d\n", entry->age);
    wprintf(L"PESEL: %d\n", entry->pesel);
    int gender = entry->gender;
    if (gender == 1) {
        wprintf(L"Gender: Male\n");
    } else if (gender == 2) {
        wprintf(L"Gender: Female\n");
    } else {
        wprintf(L"Gender: Non-binary\n");
    }
}

Entry* addEntry(Entry *first_entry) {
    // Adds a new entry to the list
    Entry *new_entry = allocateEntry();
    if (first_entry == nullptr) {
        first_entry = new_entry;
        new_entry->prev = nullptr;
    } else {
        Entry *current_entry = first_entry;
        while (current_entry->next != nullptr) {
            current_entry = current_entry->next;
        }
        current_entry->next = new_entry;
        new_entry->prev = current_entry;
    }
    new_entry->next = nullptr;
    // Creating variables for the new entry
    char name[50] = "";
    char lastname[50] = "";
    int age = 0;
    int pesel = 0;
    int gender = -1;
    // Getting information from the user
    system(CLEAR);
    wprintf(L"Adding a new entry\n");
    wprintf(L"Enter the name (max 50 char): ");
    scanf("%s", name);
    wprintf(L"Enter the lastname (max 50 char): ");
    scanf("%s", lastname);
    wprintf(L"Enter the age: ");
    scanf("%d", &age);
    wprintf(L"Enter the PESEL: ");
    scanf("%d", &pesel);
    wprintf(L"Enter the gender (1 for male, 2 for female, 3 for other): ");
    scanf("%d", &gender);
    // Assigning the values to the new entry
    strcpy(new_entry->name, name);
    strcpy(new_entry->lastname, lastname);
    new_entry->age = age;
    new_entry->pesel = pesel;
    new_entry->gender = gender;
    // Displaying success message
    system(CLEAR);
    wprintf(L"Entry added successfully\n");
    wprintf(L"Press enter to return to the menu\n");
    getchar();
    getchar();
    return first_entry;
}

Entry* removeEntry(Entry* first_entry) {
    // Removes an entry from the list
    system(CLEAR);
    wprintf(L"Delete by the name or lastname?\n");
    wprintf(L"1 - name; 2 - lastname\n");
    int del_by;
    fflush(stdin);
    scanf("%d", &del_by);
    switch(del_by) {
        case 1: {
            system(CLEAR);
            wprintf(L"Enter the name of the entry to delete: ");
            char name[50] = "";
            fflush(stdin);
            scanf("%s", name);
            Entry *current_entry = first_entry;
            while (current_entry != nullptr) {
                if (strcmp(current_entry->name, name) == 0) {
                    system(CLEAR);
                    printEntry(current_entry);
                    wprintf(L"Do you wish to delete this entry?\n");
                    wprintf(L"1 - yes; 2 - search for another matching entry; 3 - cancel deletion\n");
                    int del_option;
                    fflush(stdin);
                    scanf("%d", &del_option);
                    switch (del_option) {
                        case 1: {
                            if (current_entry->prev == nullptr) { // if this entry is first
                                first_entry = current_entry->next;
                                if (first_entry != nullptr) {
                                    first_entry->prev = nullptr; // first entry always has nullptr as prev
                                }
                                freeEntry(current_entry);
                                system(CLEAR);
                                wprintf(L"Entry removed successfully\n");
                                wprintf(L"Press enter to return to the menu\n");
                                getchar();
                                getchar();
                                return first_entry;
                            }
                            current_entry->prev->next = current_entry->next; // if it's not first
                            if (current_entry->next != nullptr) { // if it's not last
                                current_entry->next->prev = current_entry->prev;
                            }
                            freeEntry(current_entry);
                            system(CLEAR);
                            wprintf(L"Entry removed successfully\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return first_entry;
                        }
                        case 2: {
                            break;
                        }
                        case 3: {
                            system(CLEAR);
                            wprintf(L"Canceled operation\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return first_entry;
                        }
                        default: {
                            system(CLEAR);
                            wprintf(L"Invalid option\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return first_entry;
                        }
                    }
                }
                current_entry = current_entry->next;
            }
            system(CLEAR);
            wprintf(L"Couldn't find a matching entry\n");
            wprintf(L"Press enter to return to the menu\n");
            getchar();
            getchar();
            return first_entry;
        }
        case 2: {
            system(CLEAR);
            wprintf(L"Enter the lastname of the entry to delete: ");
            char lastname[50] = "";
            scanf("%s", lastname);
            Entry *current_entry = first_entry;
            while (current_entry != nullptr) {
                if (strcmp(current_entry->lastname, lastname) == 0) {
                    system(CLEAR);
                    printEntry(current_entry);
                    wprintf(L"Do you wish to delete this entry?\n");
                    wprintf(L"1 - yes; 2 - search for another matching entry; 3 - cancel deletion\n");
                    int del_option;
                    fflush(stdin);
                    scanf("%d", &del_option);
                    switch (del_option) {
                        case 1: {
                            if (current_entry->prev == nullptr) {
                                first_entry = current_entry->next;
                                if (first_entry != nullptr) {
                                    first_entry->prev = nullptr; // first entry always has nullptr as prev
                                }
                                freeEntry(current_entry);
                                system(CLEAR);
                                wprintf(L"Entry removed successfully\n");
                                wprintf(L"Press enter to return to the menu\n");
                                getchar();
                                getchar();
                                return first_entry;
                            }
                            current_entry->prev->next = current_entry->next;
                            if (current_entry->next != nullptr) {
                                current_entry->next->prev = current_entry->prev;
                            }
                            freeEntry(current_entry);
                            system(CLEAR);
                            wprintf(L"Entry removed successfully\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return first_entry;
                        }
                        case 2: {
                            break;
                        }
                        case 3: {
                            system(CLEAR);
                            wprintf(L"Canceled operation\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return first_entry;
                        }
                        default: {
                            system(CLEAR);
                            wprintf(L"Invalid option\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return first_entry;
                        }
                    }
                }
                current_entry = current_entry->next;
            }
            system(CLEAR);
            wprintf(L"Couldn't find a matching entry\n");
            wprintf(L"Press enter to return to the menu\n");
            getchar();
            getchar();
            return first_entry;
        }
        default: {
            system(CLEAR);
            wprintf(L"Invalid option\n");
            wprintf(L"Press enter to return to the menu\n");
            getchar();
            getchar();
            return first_entry;
        }
    }
}

void findEntry(Entry* first_entry) {
    // Finds an entry in the list
    system(CLEAR);
    wprintf(L"Search by the name or lastname?\n");
    wprintf(L"1 - name; 2 - lastname\n");
    int search_by;
    fflush(stdin);
    scanf("%d", &search_by);
    switch(search_by) {
        case 1: {
            system(CLEAR);
            wprintf(L"Enter the name of the entry to find: ");
            char name[50] = "";
            fflush(stdin);
            scanf("%s", name);
            Entry *current_entry = first_entry;
            while (current_entry != nullptr) {
                if (strcmp(current_entry->name, name) == 0) {
                    system(CLEAR);
                    printEntry(current_entry);
                    wprintf(L"Found a matching entry. Do you wish to find next?\n");
                    wprintf(L"1 - Exit; 2 - Find next\n");
                    int find_option;
                    fflush(stdin);
                    scanf("%d", &find_option);
                    switch (find_option) {
                        case 1: {
                            system(CLEAR);
                            wprintf(L"Exiting the search function.\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return;
                        }
                        case 2: {
                            break;
                        }
                        default: {
                            system(CLEAR);
                            wprintf(L"Invalid option\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return;
                        }
                    }
                }
                current_entry = current_entry->next;
            }
            system(CLEAR);
            wprintf(L"Couldn't find a matching entry\n");
            wprintf(L"Press enter to return to the menu\n");
            getchar();
            getchar();
            return;
        }
        case 2: {
            system(CLEAR);
            wprintf(L"Enter the lastname of the entry to find: ");
            char lastname[50] = "";
            fflush(stdin);
            scanf("%s", lastname);
            Entry *current_entry = first_entry;
            while (current_entry != nullptr) {
                if (strcmp(current_entry->lastname, lastname) == 0) {
                    system(CLEAR);
                    printEntry(current_entry);
                    wprintf(L"Found a matching entry. Do you wish to find next?\n");
                    wprintf(L"1 - Exit; 2 - Find next\n");
                    int find_option;
                    fflush(stdin);
                    scanf("%d", &find_option);
                    switch (find_option) {
                        case 1: {
                            system(CLEAR);
                            wprintf(L"Exiting the search function.\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return;
                        }
                        case 2: {
                            break;
                        }
                        default: {
                            system(CLEAR);
                            wprintf(L"Invalid option\n");
                            wprintf(L"Press enter to return to the menu\n");
                            getchar();
                            getchar();
                            return;
                        }
                    }
                }
                current_entry = current_entry->next;
            }
            system(CLEAR);
            wprintf(L"Couldn't find a matching entry\n");
            wprintf(L"Press enter to return to the menu\n");
            getchar();
            getchar();
            return;
        }
        default: {
            system(CLEAR);
            wprintf(L"Invalid option\n");
            wprintf(L"Press enter to return to the menu\n");
            getchar();
            getchar();
        }
    }
}

void displayEntries(Entry* first_entry) {
    // Displays all entries in the list
    Entry *current_entry = first_entry;
    int index = 1;
    system(CLEAR);
    wprintf(L"Displaying all entries\n");
    wprintf(L"---\n");
    while (current_entry != nullptr) {
        wprintf(L"NO. %d\n", index);
        printEntry(current_entry);
        wprintf(L"---\n");
        current_entry = current_entry->next;
        index++;
    }
    wprintf(L"Press enter to return to the menu\n");
    getchar();
    getchar();
}

void browseEntries(Entry* first_entry) {
    // Browses the entries in the list
    // Count entries
    int entries_count = 0;
    Entry *current_entry = first_entry;
    while (current_entry != nullptr) {
        entries_count++;
        current_entry = current_entry->next;
    }
    if (entries_count == 0) {
        system(CLEAR);
        wprintf(L"There are no entries to browse.\n");
        wprintf(L"Press enter to return to the menu.\n");
        getchar();
        getchar();
        return;
    }
    int current_index = 1;
    current_entry = first_entry;
    bool exit = false;
    while(!exit) {
        system(CLEAR);
        wprintf(L"Entry %d / %d\n", current_index, entries_count);
        printEntry(current_entry);
        wprintf(L"---\n");
        if (current_entry->prev != nullptr) {
            wprintf(L"1. Previous entry\n");
        } else {
            wprintf(L"1. Previous entry [unavailable]\n");
        }
        wprintf(L"2. Exit browser\n");
        if (current_entry->next != nullptr) {
            wprintf(L"3. Next entry\n");
        } else {
            wprintf(L"3. Next entry [unavailable]\n");
        }
        wprintf(L"Select an option and press enter: ");
        int option;
        fflush(stdin);
        scanf("%d", &option);
        switch(option) {
            case 1: {
                if (current_entry->prev != nullptr) {
                    current_entry = current_entry->prev;
                    current_index--;
                }
                break;
            }
            case 2: {
                exit = true;
                break;
            }
            case 3: {
                if (current_entry->next != nullptr) {
                    current_entry = current_entry->next;
                    current_index++;
                }
                break;
            }
            default: {
                system(CLEAR);
                wprintf(L"Invalid option\n");
                wprintf(L"Press enter to return to the menu\n");
                getchar();
                getchar();
                break;
            }
        }
    }
}

Entry* sortEntries(Entry* first_entry) {
    // Sorts the entries in the list
    system(CLEAR);
    wprintf(L"Do you want to sort by name or lastname?\n");
    wprintf(L"1 - name; 2 - lastname\n");
    int sort_by;
    fflush(stdin);
    scanf("%d", &sort_by);
    switch (sort_by) {
        case 1: {
            // Counting entries
            int entries_count = 0;
            Entry *current_entry = first_entry;
            while (current_entry != nullptr) {
                entries_count++;
                current_entry = current_entry->next;
            }
            system(CLEAR);
            wprintf(L"Sorting entries by name\n");
            for (int i = 0; i < entries_count; i++) {
                current_entry = first_entry;
                Entry *next_entry = current_entry->next;
                while (next_entry != nullptr) {
                    if (strcmp(current_entry->name, next_entry->name) > 0) {
                        Entry *temp_entry = nullptr;

                        if (current_entry->prev != nullptr) {
                            current_entry->prev->next = next_entry;
                        }

                        if (next_entry->next != nullptr) {
                            next_entry->next->prev = current_entry;
                        }

                        temp_entry = current_entry->prev;
                        current_entry->prev = next_entry;
                        next_entry->prev = temp_entry;

                        current_entry->next = next_entry->next;
                        next_entry->next = current_entry;

                        if(next_entry->prev == nullptr) {
                            first_entry = next_entry;
                        } else if (current_entry->prev == nullptr) {
                            first_entry = current_entry;
                        }

                        temp_entry = current_entry;
                        current_entry = next_entry;
                        next_entry = temp_entry;

                    }
                    next_entry = next_entry->next;
                    current_entry = current_entry->next;
                }
            }
            break;
        }
        case 2: {
            // Counting entries
            int entries_count = 0;
            Entry *current_entry = first_entry;
            while (current_entry != nullptr) {
                entries_count++;
                current_entry = current_entry->next;
            }
            system(CLEAR);
            wprintf(L"Sorting entries by lastname\n");
            for (int i = 0; i < entries_count; i++) {
                current_entry = first_entry;
                Entry *next_entry = current_entry->next;
                while (next_entry != nullptr) {
                    if (strcmp(current_entry->lastname, next_entry->lastname) > 0) {
                        Entry *temp_entry = nullptr;

                        if (current_entry->prev != nullptr) {
                            current_entry->prev->next = next_entry;
                        }

                        if (next_entry->next != nullptr) {
                            next_entry->next->prev = current_entry;
                        }

                        temp_entry = current_entry->prev;
                        current_entry->prev = next_entry;
                        next_entry->prev = temp_entry;

                        current_entry->next = next_entry->next;
                        next_entry->next = current_entry;

                        if(next_entry->prev == nullptr) {
                            first_entry = next_entry;
                        } else if (current_entry->prev == nullptr) {
                            first_entry = current_entry;
                        }

                        temp_entry = current_entry;
                        current_entry = next_entry;
                        next_entry = temp_entry;

                    }
                    next_entry = next_entry->next;
                    current_entry = current_entry->next;
                }
            }
            break;
        }
        default: {
            system(CLEAR);
            wprintf(L"Invalid option\n");
            wprintf(L"Press enter to return to the menu\n");
            getchar();
            getchar();
            return first_entry;
        }
    }
    return first_entry;
}

void saveEntries(Entry* first_entry) {
    // Saves the entries to a file
    system(CLEAR);
    wprintf(L"Insert the name of the file where you want to save data.\n");
    wprintf(L"Do NOT include the file extension. Maximum 50 characters.\n");
    char filename[50] = "";
    fflush(stdin);
    scanf("%s", filename);
    strcat(filename, ".txt");
    FILE *file = fopen(filename, "w");
    if (file == nullptr) {
        system(CLEAR);
        wprintf(L"Error opening the file.\n");
        wprintf(L"Press enter to return to the menu.\n");
        getchar();
        getchar();
        return;
    }
    Entry *current_entry = first_entry;
    while (current_entry != nullptr) {
        fprintf(file, "%s\n", current_entry->name);
        fprintf(file, "%s\n", current_entry->lastname);
        fprintf(file, "%d\n", current_entry->age);
        fprintf(file, "%d\n", current_entry->pesel);
        fprintf(file, "%d\n", current_entry->gender);
        current_entry = current_entry->next;
    }
    fclose(file);
}

Entry* loadEntries(Entry* first_entry) {
    // Loads the entries from a file
    system(CLEAR);
    wprintf(L"Insert the name of the file with the data.\n");
    wprintf(L"Do NOT include the file extension. Maximum 50 characters.\n");
    char filename[50] = "";
    fflush(stdin);
    scanf("%s", filename);
    strcat(filename, ".txt");
    FILE *file = fopen(filename, "r");
    if (file == nullptr) {
        system(CLEAR);
        wprintf(L"Error opening the file.\n");
        wprintf(L"Press enter to return to the menu.\n");
        getchar();
        getchar();
        return first_entry;
    }
    if (first_entry == nullptr) {
        first_entry = allocateEntry();
        first_entry->prev = nullptr;
    }
    Entry *current_entry = first_entry;
    Entry *prev_entry = nullptr;
    while (!feof(file)) {
        if (current_entry != first_entry) {
            current_entry->prev = prev_entry;
        }

        char name[50] = "";
        char lastname[50] = "";
        int age = 0;
        int pesel = 0;
        int gender = -1;

        fscanf(file, "%s", name);
        fscanf(file, "%s", lastname);
        fscanf(file, "%d", &age);
        fscanf(file, "%d", &pesel);
        fscanf(file, "%d", &gender);
        fscanf(file, "\n");

        strcpy(current_entry->name, name);
        strcpy(current_entry->lastname, lastname);
        current_entry->age = age;
        current_entry->pesel = pesel;
        current_entry->gender = gender;

        if (feof(file)) {
            current_entry->next = nullptr;
            break;
        } else {
            Entry *next_entry = allocateEntry();
            current_entry->next = next_entry;
        }
        prev_entry = current_entry;
        current_entry = current_entry->next;
    }
    fclose(file);
    return first_entry;
}

Entry* debugEntries() {
    // Debug function to add a few entries to test functions
    Entry* first_entry = allocateEntry();
    Entry* second_entry = allocateEntry();
    Entry* third_entry = allocateEntry();
    Entry* fourth_entry = allocateEntry();

    first_entry->prev = nullptr;
    strcpy(first_entry->name, "John");
    strcpy(first_entry->lastname, "Doe");
    first_entry->age = 25;
    first_entry->pesel = 123456789;
    first_entry->gender = 1;
    first_entry->next = second_entry;

    second_entry->prev = first_entry;
    strcpy(second_entry->name, "Alice");
    strcpy(second_entry->lastname, "Smith");
    second_entry->age = 30;
    second_entry->pesel = 987654321;
    second_entry->gender = 2;
    second_entry->next = third_entry;

    third_entry->prev = second_entry;
    strcpy(third_entry->name, "Bob");
    strcpy(third_entry->lastname, "Johnson");
    third_entry->age = 40;
    third_entry->pesel = 123123123;
    third_entry->gender = 1;
    third_entry->next = fourth_entry;

    fourth_entry->prev = third_entry;
    strcpy(fourth_entry->name, "Eve");
    strcpy(fourth_entry->lastname, "Brown");
    fourth_entry->age = 35;
    fourth_entry->pesel = 321321321;
    fourth_entry->gender = 2;
    fourth_entry->next = nullptr;

    return first_entry;
}

Entry* main_menu(Entry *first_entry) {
    bool exit = false;
    while(!exit) {
        if (first_entry == nullptr) {
            // If there are no entries some options are unavailable
            system(CLEAR);
            wprintf(L"Simple personal data manager\n");
            wprintf(L"--- Main menu ---\n");
            wprintf(L"1. Add new entry\n");
            wprintf(L"2. Remove entry [unavailable - there is no entries]\n");
            wprintf(L"3. Find entry [unavailable - there is no entries]\n");
            wprintf(L"4. Display all entries [unavailable - there is no entries]\n");
            wprintf(L"5. Browse entries [unavailable - there is no entries]\n");
            wprintf(L"6. Sort entries [unavailable - there is no entries]\n");
            wprintf(L"7. Save entries to the file [unavailable - there is no entries]\n");
            wprintf(L"8. Load entries from the file\n");
            wprintf(L"9. Exit\n");
            wprintf(L"Select an option and press enter: ");
            int option;
            scanf("%d", &option);
            switch(option) {
                case 1: {
                    first_entry = addEntry(first_entry);
                    break;
                }
                case 2: {
                    system(CLEAR);
                    wprintf(L"You can't delete entries because there is no entries.\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
                case 3: {
                    system(CLEAR);
                    wprintf(L"There's no entries to be found.\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
                case 4: {
                    system(CLEAR);
                    wprintf(L"There's no entries to be displayed.\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
                case 5: {
                    system(CLEAR);
                    wprintf(L"You cannot browse an empty list.\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
                case 6: {
                    system(CLEAR);
                    wprintf(L"You cannot sort an empty list.\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
                case 7: {
                    system(CLEAR);
                    wprintf(L"You cannot save an empty list.\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
                case 8: {
                    first_entry = loadEntries(first_entry);
                    break;
                }
                case 9: {
                    exit = true;
                    break;
                }
                default: {
                    // resolve_easter_egg(option);
                    system(CLEAR);
                    wprintf(L"Invalid option!\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
            }
        } else {
            system(CLEAR);
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
                case 1: {
                    first_entry = addEntry(first_entry);
                    break;
                }
                case 2: {
                    first_entry = removeEntry(first_entry);
                    break;
                }
                case 3: {
                    findEntry(first_entry);
                    break;
                }
                case 4: {
                    displayEntries(first_entry);
                    break;
                }
                case 5: {
                    browseEntries(first_entry);
                    break;
                }
                case 6: {
                    first_entry = sortEntries(first_entry);
                    break;
                }
                case 7: {
                    saveEntries(first_entry);
                    break;
                }
                case 8: {
                    first_entry = loadEntries(first_entry);
                    break;
                }
                case 9: {
                    exit = true;
                    break;
                }
                default: {
                    // resolve_easter_egg(option);
                    system(CLEAR);
                    wprintf(L"Invalid option!\n");
                    wprintf(L"Press enter to return to the menu.\n");
                    getchar();
                    getchar();
                    break;
                }
            }
        }
    }
    return first_entry;
}

int garbage_collector(Entry *first_entry) {
    // Frees all the memory allocated for the entries
    Entry *current_entry = first_entry;
    while (current_entry != nullptr) {
        Entry *next_entry = current_entry->next;
        freeEntry(current_entry);
        current_entry = next_entry;
    }
    return 0;
}

int main(void) {
    setlocale(LC_ALL, "Polish");
    wprintf(L"Loading program\n");
    // Release
    Entry *first_entry = nullptr;
    // Debug
    // Entry *first_entry = debugEntries();
    system(CLEAR);
    first_entry = main_menu(first_entry);
    system(CLEAR);
    wprintf(L"Running garbage collector\n");
    garbage_collector(first_entry);
    system(CLEAR);
    wprintf(L"Exiting program\n");
    return 0;
}