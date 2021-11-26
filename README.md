# ft_containers
(42 subject) Various basic structures for C++ !

## Table of Content

* [Technologies](#technologies)
* [Description](#description)
* [Installation](#installation)
* [Usage](#usage)
* [Utility](#utility)
* [Contributing](#contributing)

## Technologies

Project is created with:
* clang 13.0.0

## Description

The aim of this project is to recreate the most useful containers in C++ STL :
* Vector (array)
* List (chained list)
* Map (key:value structure)
* Stack (LIFO)
* Queue (FIFO)
All those containers must take a template type T in argument so it accepts every kind of variable.\
All the containers which originaly have iterators must have iterators reimplemented.

## Installation

Just pull the project !\
You just have to move the "includes" folder in another project so the .h files are compiled with your cpp files.

## Usage

````sh
clang++ -Wall -Wextra -Werror -I [path_to_the_includes_folder] #compiles your C++ project with the .h files
````

## Utility

I learned a lot about shell and unix during this project and it is quite satisfaying to see that you are able to code an entire shell environment at this stage of your studies (1 year after starting to code)

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
