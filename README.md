# A project from the second ring of the core - pipex

*Pipex aims to deepen your understanding of the two concepts that you already know: Redirections and Pipes. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.*

*There is a bonus version in which you are not restricted to the use of two commands. You can enter multiple commands.*

> ## “The single biggest problem in communication is the illusion that it has taken place.”

<a name="0"></a>
# [Table of content](#0)
- [Introduction](#1)
- [Requirements that must be met](#2)
- [Possible errors that must be handled](#3)
- [Installation](#4)
- [Implementation](#5)
- [Resources](#6)

<a name="1"></a>
# [Introduction](#1)
Note that I used my own [libft](https://github.com/lspohle/42_pipex/blob/main/libft) [strncmp](https://github.com/lspohle/42_pipex/blob/main/libft/ft_strncmp.c) and further functions.

|Position of Argument|Argument|Description|
|:--:|:--------:|:----:|
|0|./pipex|The name of the program that will be executed.|
|1|file1|The file from which will be read.|
|2|cmd1|The first shell command that will be executed.|
|3|cmd2|The second shell command that will be executed.|
|4|file1|The file into which will be written.|

<a name="2"></a>
# [Requirements that must be met](#2)
- [x] It must behave exactly the same as the following shell command: < file1 cmd1 | cmd2 > file2.
- [x] It must take the following four arguments: file1 cmd1 cmd2 file2.
- [x] It must read from the first argument `file1` if necessary.
- [x] It must execute the second argument `cmd1` reading from `file1` and writing to the `pipe`.
- [x] It must execute the third argument `cmd2` reading from the `pipe` and writing into the `file2`.
- [x] It must write into the forth argument `file2`.
- [x] It must free all memory that has been allocated on the heap before exiting the process.
- [x] It must close all open file descriptors (not only those of the parent but also the ones of the child process).
- [x] It must comply with the style guide of 42 `Norminette`.

<a name="3"></a>
# [Possible errors that must be handled](#3)
- [x] It must handle the errors like the shell command.
- [x] It must throw an error if the user entered not exactely five argument.
- [x] It must throw an error if `file1` does not exist.
- [x] It must truncate the existing `file2` if it is not empty.
- [x] It must create a `file2` with appropriate permissions to write into if such does not exist.
- [x] It must execute `cmd2` even if `cmd1` failed.
- [x] It must throw an error if `cmd2` failed even if `cmd1` was executed successfully.
- [x] It must work even if single or double quotes are included in the command itself (awk '{count++} END {print count}').
- [x] It must exit in a clean manner just like the shell command does.

<a name="4"></a>
# [Installation](#4)
- Install *Pipex* by cloning the current repository. If you do not have an SSH key yet, you need to use the command using https. Otherwise, it is up to you to use either SSH or https.
     - SSH
      
      git clone git@github.com:lspohle/42_pipex.git
          
     - HTTPS
      
      git clone https://github.com:lspohle/42_pipex.git
      
- Go into the directory `42_pipex` and run the command `make` to compile. Run the command `make bonus` instead of `make` to enable entering multiple commands.
     
      make
      
<a name="5"></a>
# [Implementation](#5)
- It's completely up to you! You can choose the names of your files and the shell commands you wish to execute. *Pipex* is executed as follows.

       ./pipex infile cmd1 cmd2 outfile
- Please keep in mind that `Pipex` takes arguments from the terminal. Thus, you must use single or double quotation marks for every `cmd`that is splitted by space. The following example is for demonstration.

       ./pipex infile "ls -l" "grep Makefile" outfile

<a name="6"></a>
# [Resources](#6)
- [Unix Processes in C](https://youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
     - fork()
     - wait()
     - waitpid()
     - pipe()
     - dub()
     - dub2()
     - ...
- [File Descriptors](https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)
     - STDIN_FILENO
     - STDOUT_FILENO
     - STDERR_FILENO
- [Piping Strategy](https://www.youtube.com/watch?v=-J-nX4aiSP4&list=PLKUb7MEve0TjHQSKUWChAWyJPCpYMRovO&index=65)
