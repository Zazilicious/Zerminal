# Zerminal
Free and open source terminal emulator written in C
## How to compile and run on Linux
run the following command in the same directory that you have either cloned the repository or downloaded Zerminal.c:
### gcc -o zerminal zerminal.c `pkg-config --cflags --libs gtk+-3.0`
if you don't already have gcc installed, make sure to do-so before the previous step
## Run after Compile
to run the program after you've complied it, once again make sure you are in the same directory as Zerminal, and type the following command into your terminal:
### ./Zerminal
if everything was installed and compiled correctly, the terminal should be opened within your own terminal program!
In the future, the terminal will be entirely independent of other terminal emulators, but for now this will allow you to play around with the program while I work on it!
