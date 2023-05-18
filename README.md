# The Artsy Project: Learn the art of programming!
**The open-source compiler edition for Ubuntu CLI!**

Language Creators: Andrew Esch and Albert Gonzales


## Operating System
Artsy is intended to run on Ubuntu 20.04. Other flavors of Debian may work as well, but these operating systems are untested with Artsy.

## Web Server
The Artsy compiler is intended to be utilized with a web server for dynamic loading. However, Artsy output can be viewed statically by refreshing the output.html page upon recompiling any program.

One option for quickly viewing Artsy output without a web server environment is to utilize VSCode's Live Server extension. Please see [Live Server's official extension](https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer) for more details.

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

## Running the Artsy Compiler
To execute the Artsy compiler using a source code file, navigate to the root directory for this project and execute the following command.

```
# Example: make artsy ARGS="example-programs/addition.artsy"
# Note, "ARGS" must be uppercase when executing this command.
make artsy ARGS="(filename here)"
```


## Viewing Artsy Output
To view the results after compiling an Artsy program on Ubuntu CLI, open the output.html page in one of the following modern web browsers:
- Chrome
- Firefox
- Microsoft Edge
- Safari
- Opera


## Using the Artsy Programming Language
For detailed instructions on how to use the Artsy programming language, please refer to our [documentation website](https://drewesch.notion.site/Artsy-Coding-7b9021e7eb11475ca68ca2d7a60bdd1e).

## Artsy as a Live Code Editor
This open-source language is the basis for the official Artsy Project website. To test Artsy using a live code editor, visit [www.artsy-project.tech](https://www.artsy-project.tech/).
