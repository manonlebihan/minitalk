# minitalk
Sixth 42 project : minitalk

## Description
The goal of this project was to be able to install a communication between two terminals.

## Installation
To use this project, you need to have a C compiler installed on your computer as well as git.
To install this, you need clone this repository.   
Once the repository is cloned, go into the folder and type the command `make`, once it's been typed, there should be two executable files, `client` and `server`.

## How to use
Once you've installed the project and you have the two executables files, open a new terminal tab.  
On the first tab, type `./server`, once it executes, you should have a PID number.  
On the second tab, type `./client [server-pid] [message]` where [server-pid] is the PID number you have in the first tab and [message] is the message you want to send.  
Once you did this, go back on the first tab and your message should be here.

To use the bonus in this project, you need to type the command `make bonus`. Once it's been typed, there should be two new executable files, `client_bonus` and `server_bonus`.  
You need to open two terminal tabs as before, instead of typing `./server` and `./client`, you'll need to type `./server_bonus` and `./client_bonus`. Then, you use it the same way.  
The client should write a message saying that the message has been sent, if there's no message, then something went wrong.
