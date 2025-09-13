/*
  Documentation
  Name         : Vamsi Thummaluri
  Date         : 8/9/25
  Description  : INVERTED SEARCH  project
*/

#include "inverted_search.h"

int get_Hash_Index(const char *word)
{
    char c = tolower(word[0]);

    if (c >= 'a' && c <= 'z')
        return c - 'a'; // 0–25
    else if (isdigit(c))
        return 26; // numbers
    else
        return 27; // punctuation
}

UsedBackup *used_backups = NULL;

// Function to check if backup file was already used
int is_backup_used(const char *filename)
{
    UsedBackup *temp = used_backups;
    while (temp)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            return 1; // already used
        }
        temp = temp->next;
    }
    return 0;
}

// Add backup file to used list
void mark_backup_used(const char *filename)
{
    UsedBackup *newNode = malloc(sizeof(UsedBackup));
    strcpy(newNode->filename, filename);
    newNode->next = used_backups;
    used_backups = newNode;
}

// Load last saved file into the buffer passed by caller
void load_last_saved_file(char *filename)
{
    FILE *fp = fopen("saved_file.txt", "r");
    if (fp != NULL)
    {
        if (fgets(filename, 100, fp) != NULL)
        {
            filename[strcspn(filename, "\n")] = 0; // remove newline
        }
        fclose(fp);
    }
    else
    {
        strcpy(filename, "backup.txt"); // default
    }
}

// Save the filename passed by caller
void save_last_saved_file(const char *filename)
{
    FILE *fp = fopen("saved_file.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "%s\n", filename);
        fclose(fp);
    }
    else
    {
        printf("⚠️  Could not save saved_last file\n");
    }
}

void free_Database(HashTable *table, int size)
{
    if (table == NULL)
    {
        printf("⚠️ Database already freed or not created\n");
        return;
    }

    for (int i = 0; i < size; i++)
    {
        MainNode *main_curr = table[i].link;
        while (main_curr)
        {
            // Free subnodes first
            SubNode *sub_curr = main_curr->sub_link;
            while (sub_curr)
            {
                SubNode *sub_temp = sub_curr;
                sub_curr = sub_curr->sub_link;
                free(sub_temp);
            }

            // Free mainnode
            MainNode *main_temp = main_curr;
            main_curr = main_curr->main_link;
            free(main_temp);
        }
    }

    free(table);
    printf("✅ Database memory freed successfully!\n");
}

void free_FileList(FileList *head)
{
    if (head == NULL)
    {
        printf("⚠️ File list is already empty.\n");
        return;
    }

    FileList *temp;
    while (head)
    {
        temp = head;
        head = head->link;
        free(temp);
    }

    printf("✅ File list memory freed successfully!\n");
}

void print_file_list(FileList *head)
{
    while (head != NULL)
    {
        printf("%s -> ", head->filename);
        head = head->link;
    }
    printf("NULL\n");
}
