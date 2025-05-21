# Study Notes Compressor / Feedback Organizer

**Group:** Group08  
**Lab:** Friday 9:30am  
**Author:** Shawn (Tae Heon Lee) - 25133962

---

## Compile Instructions

To compile the program in normal mode:

make clean && make

To compile with **debug mode** enabled:

make debug

---

## How to Run

You can use the following commands:

./notes_app add         # Add a new feedback entry
./notes_app view        # View all feedback entries
./notes_app delete <id> # Delete a feedback entry by ID
./notes_app search <id> # Search for a feedback entry by ID


**Example:**

./notes_app add
./notes_app view
./notes_app delete 2
./notes_app search 1


---

## Features

	•	Linked list used for dynamic feedback storage
	•	XOR encryption to protect saved data
	•	Run-Length Encoding (RLE) for compression
	•	Search feedback by ID with the search command
	•	Persistent file storage in feedback.dat
	•	Command-line interface using runtime arguments
	•	Modular structure using separate .c and .h files
	•	Debug mode enabled using make debug and conditional compilation

---

## File Handling and Security

- Feedback is saved in a binary file (`feedback.dat`)
- Stored data is:
  - Escaped (to handle special characters like `:`)
  - Compressed using Run-Length Encoding (RLE)
  - Encrypted using a simple XOR-based method
- All reading and writing is done in binary mode

---

## Notes

- Uses **only standard libraries**: `<stdio.h>`, `<stdlib.h>`, `<string.h>`
- No external libraries or frameworks used
- Compatible with **GCC on Unix/macOS/Linux**
- Written in **pure C (C99)**

---

This program is submission-ready and implements:
- A modular, clean codebase
- Compression and encryption algorithms
- Robust file I/O
- Debug logging using `#ifdef DEBUG`

> Designed and implemented by Tae Heon Lee for UTS C Programming Project (48430)
