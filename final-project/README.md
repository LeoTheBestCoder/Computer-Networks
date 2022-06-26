# EECS 3020: Introduction to Computer Networks Final Project

## Environment Requirements
* Ubuntu 18.04

## Getting Started
There are two ways to run the program. 

1. Compile the file manually. 
    ```
    g++ server.cpp -o server
    g++ client.cpp -o client
    ./server
    ./client
    ```

1. Compile the file via `Makefile`.
    ```
    make clean
    make
    ./server
    ./client
    ```