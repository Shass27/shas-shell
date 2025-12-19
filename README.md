# Shas-Shell: A Custom UNIX-Like Command Line Interpreter

**Author:** Shaswath S  
**Language:** C (Standard 11)  
**Build System:** CMake

---

## 1. Abstract

Shas-Shell is a lightweight, custom-built command-line interpreter (shell) designed to emulate the core functionalities of standard UNIX shells (such as Bash or Zsh). Developed in C, this project serves as a practical exploration of operating system concepts, specifically process management, signal handling, memory allocation, and the execution lifecycle of system commands.

The shell provides an interactive interface for users to execute standard system programs and utilizes a set of built-in commands for session management. It features a modular architecture that separates tokenization, parsing, and execution logic, ensuring maintainability and extensibility.

---

## 2. System Architecture

The project is structured into distinct modules, each handling a specific phase of the shell's Read-Eval-Print Loop (REPL).

### 2.1 Main Execution Loop (`exec.c`)

> **Note:** `exec.c` serves as the `main.c` entry point for this project.

This module initializes the shell and enters an infinite loop that drives the user session. Its primary responsibilities include:

- **Prompt Generation:** Dynamically renders a color-coded prompt displaying the shell name (`shas-shell`) and the current working directory.
- **Input Acquisition:** Utilizes `getline()` to capture user input from `stdin`.
- **Environment Variable Expansion:** Implements logic to detect and expand environment variables (tokens beginning with `$`) before command execution.
- **History Management:** Dynamically allocates memory to store a history of commands entered during the current session.

### 2.2 Tokenization (`tokeniser.c`)

This module is responsible for lexical analysis. It takes the raw input string and splits it into discrete tokens based on whitespace delimiters. It employs dynamic memory reallocation to handle command lines of varying lengths and argument counts.

### 2.3 Parsing (`parser.c`)

The parser accepts the array of tokens produced by the tokeniser and organizes them into a structured command entity (defined in `command.h`). This separation allows the shell to distinguish between the executable command and its subsequent arguments.

### 2.4 Execution Engine (`run.c`)

This module handles the execution of non-built-in system commands. It utilizes the UNIX system calls `fork()` to create child processes and `execvp()` to replace the child process image with the requested program. The parent process waits for the child's termination using `waitpid()`, ensuring synchronous execution.

### 2.5 Built-in Command Handler (`builtin.c`)

This module contains the implementation logic for commands that must be executed within the shell's own process space (e.g., changing the directory) rather than spawning a new process.

---

## 3. Key Features

### 3.1 Built-in Commands

The Shas-Shell includes a suite of internal commands developed to manage the shell environment. These are prioritized over system executables.

- `cd <directory>`: Changes the current working directory. Supports absolute and relative paths. If no argument is provided, it defaults to the user's `HOME` directory.
- `history`: Displays a numbered list of all commands executed in the current session, allowing users to review their workflow.
- `help`: Prints a manual detailing the available built-in commands and their usage syntax.
- `exit`: Gracefully terminates the shell session and frees allocated memory.

### 3.2 System Command Execution

The shell is fully capable of executing standard terminal commands and binaries found in the system's `PATH`.

- **Examples:** `ls -la`, `pwd`, `grep`, `mkdir`, `top`, etc.
- **Mechanism:** Leverages `execvp`, allowing users to run any installed UNIX utility with arguments.

### 3.3 Dynamic Prompt

The prompt provides immediate context to the user by displaying the current working directory in blue and the shell name in green.

- **Format:** shas-shell:current_directory>

### 3.4 Environment Variable Support

The shell supports the expansion of environment variables.

- **Usage:** `$VAR_NAME`
- **Example:** `echo $USER` or `cd $HOME` will be expanded to their respective values before execution.

---

## 4. Installation and Usage

### Prerequisites

- GCC Compiler (supporting C11 standard)
- CMake (Version 3.26 or higher)
- Linux/UNIX environment

### Compilation Instructions

1. Clone the Repository:
   git clone <repository-url>
   cd Shas-Shell

2. Build with CMake:
   cmake .
   make

### Running the Shell

Once compiled, the executable `Shas_Shell` will be created.

Run command:
./Shas_Shell

---

## 5. Technical Implementation Details

- **Memory Management:** The shell extensively uses `malloc` and `realloc` to handle dynamic input sizes. It includes cleanup routines to free tokens and command structures after every execution cycle to prevent memory leaks.
- **Error Handling:** The shell provides feedback for common errors, such as "directory not found" for `cd` or "cmd not found" if `execvp` fails to locate a binary.

Refer to the Test_Cases.pdf to see the UNIX terminal commands running.

---

## 6. Future Scope

Future iterations of the Shas-Shell aim to include:

- I/O Redirection (`>`, `<`) and Piping (`|`)
- Background process execution (`&`)
- Signal handling (e.g., catching `SIGINT` / Ctrl+C)
