/*
  Documentation
  Name         : Vamsi Thummaluri
  Date         : 8/9/25
  Description  : INVERTED SEARCH  project
*/

#include "inverted_search.h"

#define SIZE 28 // 26 alphabets + 1 number + 1 punctuation

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <file1> [file2] [file3] ...\n", argv[0]);
        return 1;
    }

    FileList *file_list = NULL;

    // Validate and store files into file_list
    if (read_and_validate(argc, argv, &file_list) == FAILURE)
    {
        printf("⚠️ Some files failed to process. Continuing with valid files.\n");
    }

    printf("\nFile list is : \n");
    print_file_list(file_list);

    // Create hash table
    HashTable *database = create_HashTable();

    int is_db_created = 0; // Flag to ensure DB creation only once
    int is_db_saved = 0;   // Flag to ensure save only once
    char last_saved_file[100];
    int choice;
    char word[20];

    while (1)
    {
        printf("\n┌──────────────────────────────────────┐\n");
        printf("│        📂 Inverted Search Menu       │\n");
        printf("├────┬─────────────────────────────────┤\n");
        printf("│ 1  │ Create Database                 │\n");
        printf("│ 2  │ Search Word in Database         │\n");
        printf("│ 3  │ Display Database                │\n");
        printf("│ 4  │ Save Database                   │\n");
        printf("│ 5  │ Update Database                 │\n");
        printf("│ 6  │ Exit                            │\n");
        printf("└────┴─────────────────────────────────┘\n");
        printf("👉 Enter your choice: ");

        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice)
        {
        case 1:
            if (is_db_created)
            {
                printf("⚠️  Database already created\n");
            }
            else
            {
                if (create_Database(database, file_list) != SUCCESS)
                {
                    printf("\n❌ Database creation Failed\n");
                    break;
                }
                is_db_created = 1;
                printf("\n✅ Database created successfully\n");
            }
            break;

        case 2:
            if (!is_db_created)
            {
                printf("⚠️  Database not created yet. Please create it first\n");
                break;
            }
            printf("Enter word to search: ");
            scanf("%s", word);
            getchar();
            if (search_Database(database, word) != SUCCESS)
            {
                printf("\n❌ Failed Searching\n");
                break;
            }
            printf("\n✅ Displayed successfully\n");
            break;

        case 3:
            if (!is_db_created)
            {
                printf("⚠️  Database not created yet. Nothing to display\n");
                break;
            }
            if (display_Database(database) != SUCCESS)
            {
                printf("\n❌ Displaying the Database failed\n");
                break;
            }
            printf("\n✅ Database Displayed successfully\n");
            break;

        case 4:
        {
            if (!is_db_created)
            {
                printf("⚠️  Database not created yet. Cannot save\n");
                break;
            }

            if (is_db_saved)
            {
                printf("⚠️  Database has already been saved. Cannot save again.\n");
                break;
            }

            // Load the last saved file
            load_last_saved_file(last_saved_file);
            printf("\nLast saved file: %s\n", last_saved_file);

            char filename[100];
            printf("Enter filename to save database [Press Enter to take default: %s]: ", last_saved_file);

            if (scanf("%99[^\n]", filename) != 1)
            {
                strcpy(filename, last_saved_file);
                printf("➡️  Proceeding with default file '%s'\n", filename);
            }
            getchar(); // consume newline

            printf("\n👉 Saving database to '%s'\n", filename);
            if (save_Database(database, filename) != SUCCESS)
            {
                printf("\n❌ Saving failed\n");
                break;
            }

            strcpy(last_saved_file, filename);
            save_last_saved_file(last_saved_file); // Persist last saved file
            is_db_saved = 1;

            printf("\n✅ Database saved successfully\n");
            break;
        }

        case 5:
        {
            if (is_db_created)
            {
                printf("⚠️  Database is already created. Cannot update again\n");
                break;
            }

            // Load last saved file from config
            load_last_saved_file(last_saved_file);
            printf("\nLast saved file: %s\n", last_saved_file);

            char filename[100];
            printf("Enter filename to update database from [Press Enter to take Last saved file: %s]: ", last_saved_file);

            if (scanf("%99[^\n]", filename) != 1)
            {
                strcpy(filename, last_saved_file); // Use last saved file
            }
            getchar(); // consume newline

            if (!validate_backup_file(filename))
            {
                printf("❌ Validation failed. Update operation aborted\n");
                break;
            }

            if (is_backup_used(filename))
            {
                printf("⚠️  Backup file '%s' was already used. Skipping update\n", filename);
                break;
            }

            if (database == NULL)
            {
                database = create_HashTable();
            }

            printf("\n👉 Updating database from '%s'\n", filename);

            if (update_Database(database, filename, &file_list) != SUCCESS)
            {
                printf("❌ Updating Database failed from %s\n", filename);
                break;
            }

            printf("\n👉 Updated File List is:\n");
            print_file_list(file_list);

            if (file_list != NULL)
            {
                printf("👉 Creating database with new files\n");
                create_Database(database, file_list);
            }
            else
            {
                printf("\nℹ️  No new files to create database\n");
            }

            mark_backup_used(filename);
            is_db_created = 1;

            printf("✅ Database updated from %s\n", filename);
            break;
        }

        case 6:
            printf("👋 Exiting program.\n");
            free_Database(database, SIZE);
            free_FileList(file_list);
            return 0;

        default:
            printf("❌ Invalid choice. Please select again.\n");
        }
    }

    return 0;
}
