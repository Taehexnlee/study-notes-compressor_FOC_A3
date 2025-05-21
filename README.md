# Study Notes Compressor / Feedback Organizer

**Group:** Group08  
**Lab:** Friday 9:30am  
**Author:** Shawn(Tae Heon Lee) - 25133962

## Compile Instructions

To compile the program, use the following command in terminal:

```bash
make clean && make
```

## How to Run

The program supports three commands:

- `./notes_app add` – Add a new feedback entry  
- `./notes_app view` – View all saved feedback  
- `./notes_app delete <id>` – Delete feedback by its ID  
- `./notes_app search <id>` – search feedback by its ID  

Example:
```bash
./notes_app add
./notes_app view
./notes_app delete 2
./notes_app search 1
```

## Features

- Feedback entries support:
  - XOR-based encryption for secure storage
  - Run-Length Encoding (RLE) for compression
- Data is saved to a binary file: `feedback.dat`
- Command-line interface:
  - `add` – Add new feedback
  - `view` – View all feedback entries
  - `delete <id>` – Delete a feedback entry by its ID
  - `search <keyword>` – Search feedback entries by keyword (subject, student name, or feedback content)
- Linked list used to manage dynamic feedback data
- Modular design using multiple `.c` and `.h` files
- Makefile included for easy compilation


## Notes

- Uses only standard C libraries: `<stdio.h>`, `<stdlib.h>`, `<string.h>`
- Implements custom C library structure with `.h` files
- Supports persistent data between runs using encrypted + compressed storage
