# The Artsy Project: Learn the art of programming!
**The open-source compiler edition for Ubuntu CLI!**

Language Creators: Andrew Esch and Albert Gonzales


## Operating System
Artsy is intended to run on Ubuntu 20.04. Other flavors of Debian may work as well, but these operating systems are untested with Artsy.

## Web Server and PHP
Artsy is intended to run on PHP 8.x with either the LAMP or LEMP stack (i.e., Apache or Nginx).

## Package Dependencies
The following packages need to be installed in Ubuntu for Artsy to function properly:
- make
- flex
- bison
- wabt
- build-essential
- gcc


To install these packages, run the following commands in your terminal:
```
sudo apt-get update
sudo apt-get install make flex bison wabt build-essential gcc
```

## Permissions
Ensure that the user has full read, write, and execute permissions for the entire project directory.

## Running Artsy
To execute the Artsy compiler for a specific file, navigate to the root directory for this project and execute the following command.

```
# Example: make artsy args="example-programs/addition.artsy"
make artsy args="(filename here)"
```


## Using the Artsy Programming Language
For detailed instructions on how to use the Artsy programming language, please refer to our [documentation website](https://drewesch.notion.site/Artsy-Coding-7b9021e7eb11475ca68ca2d7a60bdd1e).

## Artsy as a Live Code Editor
This open-source language is the basis for the official Artsy Project website. To test Artsy using a live code editor, visit [www.artsy-project.tech](https://www.artsy-project.tech/).
