/*
  Documentation
  Name         : Vamsi Thummaluri
  Date         : 8/9/25
  Description  : INVERTED SEARCH  project
*/

#include "inverted_search.h"

int display_Database(HashTable *table)
{
    printf("📢 Displaying the data ...\n");
    // Display header box above the table
    printf("╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                         INVERTED SEARCH DATABASE                       ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n");

    // Table header
    printf("╔═══════╦═════════════════╦════════════╦════════════════════╦════════════╗\n");
    printf("║ %-5s ║ %-15s ║ %-10s ║ %-18s ║ %-10s ║\n",
           "Index", "Word", "FileCount", "FileName", "WordCount");
    printf("╠═══════╬═════════════════╬════════════╬════════════════════╬════════════╣\n");

    int last_i = -1; // last index with any mainNode
    MainNode *last_node = NULL;

    // Find last mainNode for avoiding last row separator
    for (int i = 0; i < 28; i++)
    {
        if (table[i].link != NULL)
        {
            last_i = i;
            last_node = table[i].link;
            while (last_node->main_link != NULL)
                last_node = last_node->main_link;
        }
    }

    // Loop through hash table
    for (int i = 0; i < 28; i++)
    {
        MainNode *mainNode = table[i].link;

        while (mainNode != NULL)
        {
            SubNode *subNode = mainNode->sub_link;

            if (subNode != NULL)
            {
                printf("║ %-5d ║ %-15s ║ %-10d ║ %-18s ║ %-10d ║\n",
                       i, mainNode->word, mainNode->file_count,
                       subNode->file_name, subNode->word_count);
                subNode = subNode->sub_link;
            }

            while (subNode != NULL)
            {
                printf("║ %-5s ║ %-15s ║ %-10s ║ %-18s ║ %-10d ║\n",
                       "", "", "", subNode->file_name, subNode->word_count);
                subNode = subNode->sub_link;
            }

            // Print row separator only if NOT the last mainNode
            if (!(i == last_i && mainNode == last_node))
            {
                printf("╠═══════╬═════════════════╬════════════╬════════════════════╬════════════╣\n");
            }

            mainNode = mainNode->main_link;
        }
    }

    // Table bottom
    printf("╚═══════╩═════════════════╩════════════╩════════════════════╩════════════╝\n\n");
    return SUCCESS;
}

int save_Database(HashTable *table, const char *filename)
{
    // Validate filename
    if (filename == NULL || strlen(filename) == 0)
    {
        printf("❌ Invalid filename\n");
        return FAILURE;
    }

    // Ensure filename ends with .txt
    const char *ext = strrchr(filename, '.'); // find last '.'
    if (ext == NULL || strcmp(ext, ".txt") != 0)
    {
        printf("❌ Error: Only .txt files are allowed for saving (given: %s)\n", filename);
        return FAILURE;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("❌ Error: Could not open file '%s' for writing\n", filename);
        return FAILURE;
    }

    printf("💾 Saving database to : %s\n", filename);

    // Loop through hash table
    for (int i = 0; i < 28; i++)
    {
        MainNode *mainNode = table[i].link;

        while (mainNode != NULL)
        {
            SubNode *subNode = mainNode->sub_link;

            // Start with #
            fprintf(fp, "#");

            // Write Index, Word, FileCount
            fprintf(fp, "%d;%s;%d;", i, mainNode->word, mainNode->file_count);

            // Write subnodes (FileName;WordCount …)
            while (subNode != NULL)
            {
                fprintf(fp, "%s;%d;", subNode->file_name, subNode->word_count);
                subNode = subNode->sub_link;
            }

            // End with #
            fprintf(fp, "#\n");

            mainNode = mainNode->main_link;
        }
    }

    fclose(fp);
    printf("✅ Database saved successfully to '%s'\n", filename);
    return SUCCESS;
}

int search_Database(HashTable *table, const char *word)
{
    if (word == NULL || strlen(word) == 0)
    {
        printf("❌ Invalid word input.\n");
        return FAILURE;
    }
    printf("🔍 Searching for the word: '%s'\n\n", word);

    // Find hash index for the word
    int index = get_Hash_Index(word);
    MainNode *mainNode = table[index].link;

    // Traverse the chain at this index
    while (mainNode != NULL)
    {
        if (strcmp(mainNode->word, word) == 0)
        {
            // Print the Search Result box header
            printf("╔══════════════════════════════════════╗\n");
            printf("║            🔎 Search Result          ║\n");
            printf("╚══════════════════════════════════════╝\n");

            // Print the word information
            printf("Word '%s' present in %d %s:\n", word, mainNode->file_count, (mainNode->file_count > 1) ? "files" : "file");

            // Print the table header
            printf("╔════════════════════════╦═════════════╗\n");
            printf("║ 📄 File Name           ║ 📝 Count    ║\n");
            printf("╠════════════════════════╬═════════════╣\n");

            // Print each file name and its word count
            SubNode *subNode = mainNode->sub_link;
            while (subNode != NULL)
            {
                printf("║ %-22s ║ %-11d ║\n",
                       subNode->file_name, subNode->word_count);
                subNode = subNode->sub_link;
            }

            // Print the table footer
            printf("╚════════════════════════╩═════════════╝\n");

            // Stop after displaying the result
            return SUCCESS;
        }

        mainNode = mainNode->main_link;
    }

    // If not found
    printf("❌ Word '%s' not found in database 😕\n", word);
    return FAILURE;
}

int search_and_select_word(HashTable *table, const char *prefix)
{
    if (table == NULL)
        return FAILURE;

    char valid_words[100][50]; // store words temporarily
    int word_count = 0;

    printf("🔍 Words matching '%s':\n", (prefix && strlen(prefix) > 0) ? prefix : "all");

    // Collect matching words
    for (int i = 0; i < 28; i++)
    {
        MainNode *node = table[i].link;
        while (node != NULL)
        {
            if (prefix == NULL || strlen(prefix) == 0 || strncmp(node->word, prefix, strlen(prefix)) == 0)
            {
                strcpy(valid_words[word_count], node->word);
                printf("%d. %s\n", word_count + 1, node->word);
                word_count++;
            }
            node = node->main_link;
        }
    }

    if (word_count == 0)
    {
        printf("❌ No words found.\n");
        return FAILURE;
    }

    int choice = -1;

    while (1) // keep asking until user chooses 0
    {
        printf("\nEnter the number of the word to view details (1-%d, 0 to exit): ", word_count);

        if (scanf("%d", &choice) != 1)
        {
            printf("❌ Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ; // clear invalid input
            continue;
        }

        getchar(); // consume newline

        if (choice == 0)
        {
            printf("➡️  Exiting partial search.\n");
            break;
        }

        if (choice < 1 || choice > word_count)
        {
            printf("❌ Number out of range. Please select a valid number.\n");
            continue;
        }

        char *selected_word = valid_words[choice - 1];

        // Display files and counts for the selected word
        int index = get_Hash_Index(selected_word);
        MainNode *mainNode = table[index].link;
        while (mainNode != NULL)
        {
            if (strcmp(mainNode->word, selected_word) == 0)
            {
                printf("\n📂 Word '%s' found in %d %s:\n", mainNode->word, mainNode->file_count,
                       (mainNode->file_count > 1) ? "files" : "file");
                printf("╔════════════════════════╦═════════════╗\n");
                printf("║ 📄 File Name           ║ 📝 Count    ║\n");
                printf("╠════════════════════════╬═════════════╣\n");

                SubNode *subNode = mainNode->sub_link;
                while (subNode != NULL)
                {
                    printf("║ %-22s ║ %-11d ║\n", subNode->file_name, subNode->word_count);
                    subNode = subNode->sub_link;
                }

                printf("╚════════════════════════╩═════════════╝\n");
                break;
            }
            mainNode = mainNode->main_link;
        }
    }

    return SUCCESS;
}

int update_Database(HashTable *database, const char *filename, FileList **file_list)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        perror("🚫 Error: Cannot open file ");
        return FAILURE;
    }

    int index, file_count, word_count;
    char word[50], file[50];
    char hash;

    while (fscanf(fp, " %c", &hash) == 1)
    {
        if (hash != '#')
        {
            printf("⚠️ Warning: Malformed entry in backup file (missing starting '#')\n");
            continue; // Skip malformed entry
        }

        if (fscanf(fp, "%d;%49[^;];%d;", &index, word, &file_count) != 3)
        {
            printf("⚠️ Warning: Invalid entry format in backup file. Skipping...\n");
            int c;
            while ((c = fgetc(fp)) != '\n' && c != EOF)
                ; // skip rest of line
            continue;
        }

        int hashIndex = get_Hash_Index(word);
        MainNode *mainNode = database[hashIndex].link;
        while (mainNode && strcmp(mainNode->word, word) != 0)
            mainNode = mainNode->main_link;

        for (int i = 0; i < file_count; i++)
        {
            if (fscanf(fp, "%49[^;];%d;", file, &word_count) != 2)
            {
                printf("⚠️ Warning: Incomplete file info for word '%s'. Skipping file...\n", word);
                int c;
                while ((c = fgetc(fp)) != '\n' && c != EOF)
                    ;
                continue;
            }

            if (is_file_in_filelist(file_list, file))
            {
                printf("\nℹ️  File '%s' already exists in database\n👉 Removing from file list...\n", file);
                remove_file_from_list(file_list, file);
            }

            // Insert word occurrences into database
            for (int j = 0; j < word_count; j++)
                insert_word(database, word, file);
        }

        // Skip any extra characters until next line
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF)
            ;
    }

    fclose(fp);

    printf("\n✅ Database updated successfully from backup file: %s\n", filename);
    return SUCCESS;
}

int is_file_in_filelist(FileList **head, const char *filename)
{
    FileList *temp = *head;
    // Check for duplicates
    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            return 1;
        }
        temp = temp->link;
    }

    return 0;
}

void insert_word(HashTable *table, const char *word, const char *filename)
{
    if (!table || !word || !filename)
        return;

    int index = get_Hash_Index(word);
    MainNode *main_curr = table[index].link;
    MainNode *main_prev = NULL;

    // Traverse main list at this index
    while (main_curr != NULL)
    {
        if (strcmp(main_curr->word, word) == 0) // Word found
        {
            SubNode *sub_curr = main_curr->sub_link;
            SubNode *sub_prev = NULL;

            // Traverse subnodes (files)
            while (sub_curr != NULL)
            {
                if (strcmp(sub_curr->file_name, filename) == 0) // File match
                {
                    sub_curr->word_count++; // increment word count
                    return;
                }
                sub_prev = sub_curr;
                sub_curr = sub_curr->sub_link;
            }

            // File not found → create new subnode
            SubNode *new_sub = (SubNode *)malloc(sizeof(SubNode));
            strcpy(new_sub->file_name, filename);
            new_sub->word_count = 1;
            new_sub->sub_link = NULL;

            if (sub_prev)
                sub_prev->sub_link = new_sub;
            else
                main_curr->sub_link = new_sub;

            main_curr->file_count++;
            return;
        }
        main_prev = main_curr;
        main_curr = main_curr->main_link;
    }

    // Word not found → create new main node
    MainNode *new_main = (MainNode *)malloc(sizeof(MainNode));
    strcpy(new_main->word, word);
    new_main->file_count = 1;
    new_main->main_link = NULL;

    // Create first subnode
    SubNode *new_sub = (SubNode *)malloc(sizeof(SubNode));
    strcpy(new_sub->file_name, filename);
    new_sub->word_count = 1;
    new_sub->sub_link = NULL;

    new_main->sub_link = new_sub;

    // Link into hash table
    if (main_prev == NULL)
        table[index].link = new_main;
    else
        main_prev->main_link = new_main;
}

void remove_file_from_list(FileList **head, const char *filename)
{
    FileList *current = *head;
    FileList *prev = NULL;

    while (current != NULL)
    {
        if (strcmp(current->filename, filename) == 0)
        {
            // Remove from main file list
            if (prev == NULL)
                *head = current->link;
            else
                prev->link = current->link;

            printf("✅ Removed file '%s' from file list\n", filename);

            free(current);
            return;
        }
        prev = current;
        current = current->link;
    }
    printf("ℹ️  No file '%s' in the list to remove\n", filename);
}
