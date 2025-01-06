# Simple Shell Project

## 🧐 What is a Simple Shell?

Simple Shell is a simple UNIX command interpreter that allows users to execute commands in a command-line environment. This project is part of the Holberton School training program.

## 🤓 Curriculum Topics Covered

The implementation of this shell demonstrates understanding and application of several key concepts in systems programming, including:

+ **Memory Management:** Use of dynamic memory allocation (`malloc`, `free`) and proper handling of memory resources.

+ **System Calls:** Integration of system-level functions like `execve`,  `fork`, `wait`, `access`, and `getline`.

+ **Process Management:** Creation and synchronization of processes using `fork` and `wait`.

+ **Environment Variables:** Accessing and utilizing environment variables such as `PATH`.

+ **String Manipulation:** Use of standard C string functions (`strtok`, `strdup`, `strcspn`, `strcmp`).

+ **File I/O:** Utilizing standard input and output for command-line interaction.

## 🦁 Flowchart

![Texto alternativo](https://github.com/Jonatha32/holbertonschool-simple_shell/blob/main/Start%20Program.jpg)

## 😐 Files Description

### `Simple_Shell.c`

The entry point of the program. It:
+ Displays a custom shell prompt (Simple_Shell$).
+ Reads user input using getline.
+ Parses and processes commands by calling exe_com().
+ Handles program termination and cleanup.

### `shell.h`

Header file containing function prototypes, necessary library imports, and any shared macros or global variables used across the project.

### `man_1_simple_shell`

Manual page for the shell. Provides documentation on usage, examples, and features of the shell.

###  `AUTHORS`

A file listing the contributors/authors of the project.

###  `Flowchart`

Flowchart

## 🤠 Features

- Execution of commands in both interactive and non-interactive modes.
- Error handling similar to the UNIX shell.
- Support for basic commands and program execution.

## 💻 Compilation

To compile the shell, use the following command:

```bash
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
```

## ✋ Expected Outut:

+ *For valid commands:* The output of the command as executed by the system.
+ *For invalid commands:* An error message in the format: `<command>: Command not found`.
+ *For `exit`:* The shell terminates gracefully

## 😎 Authors

* **[Bruno Salle](https://github.com/sallebruno)**
* **[Kevin Acosta](KevinAcostaa)**
* **[Jonathan Pérez](https://github.com/Jonatha32)**
