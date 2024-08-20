# Simple Shell Project

This project is a simple UNIX command line interpreter written in C. It is designed to replicate basic shell functionalities.

## What is a Shell? 😕

A shell is a program that lets you interact with your computer by typing commands. It takes the commands you enter, like opening files or running programs, and tells the computer's operating system to do those tasks. Think of it as a translator between you and the computer, helping you control and manage different functions through text-based input. Examples of shells include Bash and Zsh, which are commonly used on Unix-like systems.

## Features 📝

- **Command Execution**: The shell can execute basic commands.
- **Prompt**: Displays a prompt waiting for user input. After executing a command, the prompt is displayed again.
- **Error Handling**: Displays an error message if a command cannot be found or executed.
- **EOF Handling**: Supports the `Ctrl+D` command to exit the shell.

## Usage 🖥️

To compile the shell, use the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell
```

Once compiled, you can run the shell with:
```
./simple_shell
```
The shell will display a prompt where you can type commands.

```
$ ./simple_shell
$ ls
file1 file2 file3
$ pwd
/home/user
$ LSS
./simple_shell: Error: Command not found
$ ^D
$
```

## Built-in Commands 📑
+ exit: Exit the shell.
+ env: Print the current environment variables.

## Authors 😎
* **Axel Palombo** 
* **Jonathan Pérez**
