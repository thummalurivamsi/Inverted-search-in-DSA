/*
  Documentation
  Name         : Vamsi Thummaluri
  Date         : 8/9/25
  Description  : INVERTED SEARCH  project
*/

#include "inverted_search.h"

HashTable *create_HashTable()
{

    // allocate space for 28 HashTable structs
    HashTable *table = (HashTable *)malloc(28 * sizeof(HashTable));
    if (!table)
    {
        printf("Memory allocation failed for HashTable\n");
        exit(1);
    }

    // initialize all 28 indexes
    for (int i = 0; i < 28; i++)
    {
        table[i].index = i;   // store index number
        table[i].link = NULL; // initially no words
    }

    return table;
}

int create_Database(HashTable *table, FileList *file_list)
{
    FileList *temp = file_list;
    // Starting message
    printf("🚀 Creating Database ... ⏳\n\n");

    while (temp != NULL) // open files one by one
    {
        FILE *fp = fopen(temp->filename, "r");
        if (!fp)
        {
            printf("🚫 Error: Cannot open file %s\n", temp->filename);
            temp = temp->link;
            continue;
        }

        printf("\n📂 Processing %s\n", temp->filename);

        char word[50];
        while (fscanf(fp, "%s", word) != EOF) // read word by word
        {
            int index = get_Hash_Index(word);

            MainNode *mnode = table[index].link;
            MainNode *prev_mnode = NULL;

            // search for word in main node list
            while (mnode != NULL && strcmp(mnode->word, word) != 0)
            {
                prev_mnode = mnode;
                mnode = mnode->main_link;
            }

            if (mnode == NULL)
            {
                // word not found → create new main node
                MainNode *new_mnode = (MainNode *)malloc(sizeof(MainNode));
                strcpy(new_mnode->word, word);
                new_mnode->file_count = 1;
                new_mnode->sub_link = NULL;
                new_mnode->main_link = NULL;

                // create subnode for first file
                SubNode *new_snode = (SubNode *)malloc(sizeof(SubNode));
                strcpy(new_snode->file_name, temp->filename);
                new_snode->word_count = 1;
                new_snode->sub_link = NULL;

                new_mnode->sub_link = new_snode;

                // attach new main node to hash table
                if (prev_mnode == NULL)
                    table[index].link = new_mnode;
                else
                    prev_mnode->main_link = new_mnode;

                printf("➕ Added new word '%s' from file %s\n", word, temp->filename);
            }
            else
            {
                // word already exists, check subnodes (file list)
                SubNode *snode = mnode->sub_link;
                SubNode *prev_snode = NULL;

                while (snode != NULL && strcmp(snode->file_name, temp->filename) != 0)
                {
                    prev_snode = snode;
                    snode = snode->sub_link;
                }

                if (snode == NULL)
                {
                    // new file → add new subnode
                    SubNode *new_snode = (SubNode *)malloc(sizeof(SubNode));
                    strcpy(new_snode->file_name, temp->filename);
                    new_snode->word_count = 1;
                    new_snode->sub_link = NULL;

                    if (prev_snode == NULL)
                        mnode->sub_link = new_snode;
                    else
                        prev_snode->sub_link = new_snode;

                    mnode->file_count++;
                    printf("📄 New file entry for word '%s' in file %s\n", word, temp->filename);
                }
                else
                {
                    // same file → increment word count
                    snode->word_count++;
                    printf("🔼 Incremented count of word '%s' in file %s → %d times\n",
                           word, temp->filename, snode->word_count);
                }
            }
        }

        fclose(fp);
        printf("✅ Database created successfully for %s\n", temp->filename);
        temp = temp->link;
    }
    // Return Succes
    return SUCCESS;
}
