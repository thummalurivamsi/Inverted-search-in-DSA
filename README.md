🎯 Inverted Search Database in C

This project is a terminal-based Inverted Search Database developed in the C programming language using DSA. It efficiently stores and retrieves word occurrences from large text files, enabling fast search queries across multiple documents. The system demonstrates the use of hash tables, linked lists, and file handling, making it a solid foundation for applications in information retrieval, search engines, and data analytics.

📌 Project Overview

Traditional search methods scan each document sequentially, which becomes inefficient as data grows. The Inverted Search Database overcomes this by maintaining a hash table-based index, mapping each word to a list of files and their occurrence counts. This allows for instant retrieval of all files containing a queried word.

The project supports adding new files, updating the database without duplicating existing entries, and querying words to retrieve detailed results, ensuring efficient and accurate search operations even for large datasets.

⚙️ Components / Tools Used

C Programming Language

GCC Compiler

Command-line Interface (CLI)

Hash Tables (for fast word indexing)

Linked Lists (for managing word occurrences)

Modular Programming Techniques

File Handling (for persistent storage)

📁 File Modules

main.c – Program entry point, handles user input and orchestrates database operations

create_database.c – Core logic for creating and updating the inverted index

operation.c – Handles all opeartions

utility.c – File reading, validation, and preprocessing

validate.c - for validating input

inverted_search.h - All function declarations

🧠 Working Principle

Reads files from the system and parses them word by word.

Each word is hashed and inserted into a hash table.

Each table entry maintains a linked list of files where the word appears, along with the count of occurrences.

Supports operations such as:

Adding new files without duplicating existing entries

Updating the database with additional files

Searching for a word and displaying all files containing it with counts

This ensures fast retrieval and accurate indexing for large datasets.

🔐 Input Validation & Error Handling

Ensures files exist before processing.

Skips duplicate files during database updates.

Handles empty or invalid input gracefully.

Prevents memory leaks through proper allocation and deallocation.

💡 Features

✅ Efficient search using an inverted index
✅ Supports addition and update of multiple files
✅ Displays file occurrence counts for searched words
✅ Prevents duplication and maintains database integrity
✅ Modular codebase for maintainability and extension
✅ Demonstrates dynamic memory management, hash tables, and linked lists
✅ Can be extended for search engines, plagiarism detection, and text analytics

📂 File Structure

inverted-search-database/

├── main.c                # Program entry point

├── create_database.c     # Database creation and update logic

├── opeartion.c           # all opeartions

├── utility.c             # usage files

├── validate.c            # For input validation

├── README.md             # Project documentation


📸 Project Media

Project demo 
👉 : https://drive.google.com/file/d/1AS6SvMZ9fxGQNcAk-8U6IhRTAlw-hQEC/view?usp=sharing

🖼️ Sample Terminal Output:

<img width="1920" height="1080" alt="1" src="https://github.com/user-attachments/assets/f0de341f-d10f-44f2-99e0-d0739f911005" />
<img width="1920" height="1080" alt="2" src="https://github.com/user-attachments/assets/5f8b73cf-b05a-4ad1-a6a0-2e47f00ae503" />


📈 Future Improvements

Support for phrase search and wildcard queries

Ranking files based on word frequency or relevance

GUI version for easier visualization

Export search results in CSV/JSON for further analysis

Optimized hash table with dynamic resizing

Support for real-time database updates from new files

👨‍💻 Developed By Anju
Embedded Systems & Data Structures Enthusiast
vamsithummaluri@gmai.com
