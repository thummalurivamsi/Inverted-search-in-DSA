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
👉 : https://drive.google.com/file/d/1m-nlNDHT6UJOAtXA8fsSr5vStGxv4m7H/view?usp=sharing

🖼️ Sample Terminal Output:

<img width="1920" height="1080" alt="1" src="https://github.com/user-attachments/assets/2869e206-7f34-45fd-bb23-f1fe1bd2e124" />
<img width="1920" height="1080" alt="2" src="https://github.com/user-attachments/assets/2a3e39a9-a0cd-44b6-9a65-590222c3f2e8" />
<img width="1920" height="1080" alt="3" src="https://github.com/user-attachments/assets/b48e45b6-cf7e-435e-ab02-0cc721275466" />
<img width="1920" height="1080" alt="create-1" src="https://github.com/user-attachments/assets/32025bd9-593d-467f-913b-6f133259465a" />
<img width="1920" height="1080" alt="create-2" src="https://github.com/user-attachments/assets/fda0367e-5d7c-486d-8854-8f7d7773029b" />
<img width="1920" height="1080" alt="search-1" src="https://github.com/user-attachments/assets/796d2c0f-9fad-4432-835f-63023ee4e703" />
<img width="1920" height="1080" alt="search_bychar-1" src="https://github.com/user-attachments/assets/925d1c58-33b2-49fb-82a0-483a21016854" />
<img width="1920" height="1080" alt="search_bychar-2" src="https://github.com/user-attachments/assets/3bd58054-310a-4416-8fc7-d4b55a579a11" />
<img width="1920" height="1080" alt="dis-1" src="https://github.com/user-attachments/assets/555548eb-ed9e-4657-966b-4597f4ffc889" />
<img width="1920" height="1080" alt="dis-2" src="https://github.com/user-attachments/assets/8af10de6-be75-4a53-a42f-7806979f9b25" />
<img width="1920" height="1080" alt="save" src="https://github.com/user-attachments/assets/13c8f1cc-5b5d-4165-a4bf-c790760ca38e" />
<img width="1920" height="1080" alt="update-1" src="https://github.com/user-attachments/assets/2442a830-7c38-438b-a3f2-4b1ce626c82b" />
<img width="1920" height="1080" alt="update-2" src="https://github.com/user-attachments/assets/0ef3af64-554a-445c-ab96-2fb3b9ec8743" />

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
