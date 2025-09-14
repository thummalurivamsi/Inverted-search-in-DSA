#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations of data structures
struct MainNode;
struct SubNode;
struct FileList;

// Return codes for functions
#define SUCCESS 1
#define FAILURE 0
#define FILE_EMPTY -1

// Hash table structure storing words and their linked list
typedef struct HashTable
{
    int index;             // Hash index
    struct MainNode *link; // Pointer to list of words in this bucket
} HashTable;

// Linked list structure to manage file names
typedef struct FileList
{
    char filename[20];     // File name
    struct FileList *link; // Pointer to next file in list
} FileList;

// Main node structure representing a word and the files containing it
typedef struct MainNode
{
    char word[20];              // Word text
    int file_count;             // Number of files where this word appears
    struct SubNode *sub_link;   // Linked list of files containing this word
    struct MainNode *main_link; // Pointer to next word in the hash bucket
} MainNode;

// Sub node structure representing occurrences of the word in a file
typedef struct SubNode
{
    char file_name[20];       // File where the word appears
    int word_count;           // Frequency of the word in the file
    struct SubNode *sub_link; // Pointer to next file in list
} SubNode;

// Used to track backup files that have been processed already
typedef struct UsedBackup
{
    char filename[100];      // Backup file name
    struct UsedBackup *next; // Pointer to next used backup
} UsedBackup;

// ================== Function Prototypes ==================

// Validation functions
int validate_file(const char *filename);                            // Check if file is valid
int read_and_validate(int argc, char **argv, FileList **file_list); // Parse and validate input files
int validate_backup_file(char *filename);                           // Check backup file format

// File list management
int insert_file(FileList **head, const char *filename);            // Add file to list
void remove_file_from_list(FileList **head, const char *filename); // Remove file from list
void print_file_list(FileList *head);                              // Print all files in list
void free_FileList(FileList *head);                                // Free memory allocated to file list
int is_file_in_filelist(FileList **head, const char *filename);    // Check if file exists in list

// Hash operations
int get_Hash_Index(const char *word); // Generate hash index for word

// For save file
void load_last_saved_file(char *filename);
void save_last_saved_file(const char *filename);

// Database operations
HashTable *create_HashTable();                              // Initialize hash table
int create_Database(HashTable *table, FileList *file_list); // Build database from files
int display_Database(HashTable *table);                     // Display all entries in the database
int save_Database(HashTable *table, const char *filename);  // Save database to a file
void free_Database(HashTable *table, int size);             // Free memory allocated to database

// Search and insertion
int search_Database(HashTable *table, const char *word); // Search for a word in the database
int search_and_select_word(HashTable *table, const char *prefix);
void insert_word(HashTable *table, const char *word, const char *filename); // Insert or update a word

// Update database
int update_Database(HashTable *database, const char *filename, FileList **file_list); // Update from new file

// Backup file tracking
int is_backup_used(const char *filename);    // Check if backup was used
void mark_backup_used(const char *filename); // Mark a backup as used

#endif // INVERTED_SEARCH_H
