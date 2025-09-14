/*
  Documentation
  Name         : Vamsi Thummaluri
  Date         : 8/9/25
  Description  : INVERTED SEARCH  project
*/

#include "inverted_search.h"

// Main read_and_validate function
int read_and_validate(int argc, char **argv, FileList **file_list)
{
    for (int i = 1; i < argc; i++)
    {
        char *filename = argv[i];
        printf("\n🔍 Validating %s\n", filename);

        int result = validate_file(filename);

        if (result == FAILURE)
        {
            printf("❌ Skipping file %s due to validation error\n", filename);
            continue; // Don't proceed with this file
        }
        else if (result == FILE_EMPTY)
        {
            printf("⚠️  File is Empty.Skipping empty file %s\n", filename);
            continue; // Skip but warn
        }

        // If validation passed
        if (insert_file(file_list, filename) == FAILURE)
        {
            printf("⚠️  File %s is already in the list. Skipping duplicate... 🔁\n", filename);
        }
        else
        {
            printf("✅ File %s added successfully! 📂\n", filename);
            printf("✅ Done\n");
        }
    }
    return SUCCESS;
}

// This function validates a single file (checks extension, existence, and emptiness)
// Validate a single file (checks extension, existence, and emptiness)
int validate_file(const char *filename)
{
    char *ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".txt") != 0)
    {
        printf("❌ Error: Invalid file extension for %s. Expected .txt 📄\n", filename);
        return FAILURE;
    }

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("🚫 Error: Cannot open file ");
        return FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0)
    {
        // printf("⚠️  Warning: File %s is empty\n", filename);
        fclose(file);
        return FILE_EMPTY;
    }

    fclose(file);
    return SUCCESS;
}

// Function to validate if the given file exists and can be opened for reading
// Function to insert filename at the end if it does not already exist
int insert_file(FileList **head, const char *filename)
{
    FileList *temp = *head;
    // Check for duplicates
    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            // printf("⚠️  File %s is already in the list. Skipping duplicate... 🔁\n", filename);
            return FAILURE;
        }
        temp = temp->link;
    }

    // Create new node
    FileList *newNode = (FileList *)malloc(sizeof(FileList));
    if (!newNode)
    {
        printf("❌ Error: Memory allocation failed 💥\n");
        return FAILURE;
    }
    strcpy(newNode->filename, filename);
    newNode->link = NULL;

    // Insert at end
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        temp = *head;
        while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = newNode;
    }

    printf("✅ %s added to the list successfully! 📄\n", filename);
    return SUCCESS;
}

int validate_backup_file(char *filename)
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

    // Check file availability
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("⚠️  Error: File '%s' not found in current directory\n", filename);
        return FAILURE;
    }

    // Check if file is empty
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size == 0)
    {
        printf("⚠️  Error: File '%s' is empty\n", filename);
        fclose(fp);
        return FAILURE;
    }

    // --- Check first character
    fseek(fp, 0, SEEK_SET);
    int firstChar = fgetc(fp);
    if (firstChar != '#')
    {
        printf("⚠️  Error: Backup file must start with '#'\n");
        fclose(fp);
        return FAILURE;
    }

    // --- Check last character
    fseek(fp, -2, SEEK_END); // Move to last byte
    int lastChar = fgetc(fp);
    if (lastChar != '#')
    {
        printf("⚠️  Error: Backup file must end with '#'\n");
        fclose(fp);
        return FAILURE;
    }

    fclose(fp);
    printf("✅ Backup file '%s' is valid\n", filename);
    return SUCCESS;
}
