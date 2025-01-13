// Created: 2025-01-10 16:00:00
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#if _WIN32
    #define CLEAR "cls"
    #define SLEEP(x) Sleep(x)
    #include <windows.h>
#elif __gnu_linux__
    #define CLEAR "clear"
    #define SLEEP(x) usleep(x*1000)
    #include <unistd.h>
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

Entry* browseEntries(Entry* first_entry) {
    // Browses the entries in the list
    // WIP
    return first_entry;
}

Entry* sortEntries(Entry* first_entry) {
    // Sorts the entries in the list
    // WIP
    return first_entry;
}

Entry* saveEntries(Entry* first_entry) {
    // Saves the entries to a file
    // WIP
    return first_entry;
}

Entry* loadEntries(Entry* first_entry) {
    // Loads the entries from a file
    // WIP
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
                    first_entry = browseEntries(first_entry);
                    break;
                }
                case 6: {
                    first_entry = sortEntries(first_entry);
                    break;
                }
                case 7: {
                    first_entry = saveEntries(first_entry);
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
    Entry *first_entry = nullptr;
    system(CLEAR);
    first_entry = main_menu(first_entry);
    system(CLEAR);
    wprintf(L"Running garbage collector\n");
    garbage_collector(first_entry);
    system(CLEAR);
    wprintf(L"Exiting program\n");
    return 0;
}