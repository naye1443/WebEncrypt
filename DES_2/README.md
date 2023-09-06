## DES README
---
This file is an explanation about the DES implementation code.
This project was done in C++. I was able to produce a fully working version of DES.
The files structure of my project includes include files and src files, with .h files and .cpp files residing in the folders with respective files. I wanted to create a formal file structure so that it would be easy to locate the different files used. 
Within the bin directory, there are two exe types debug and relates. The only thing that resides in bin would be an executable within debug that was just a test to see if the original project would compile.


### MY APPROACH:
---
My Idea was to create a simple DES class that would have all the functions needed to encrypt data using the DES scheme. I had set constant tables that would be needed within the scheme as private members so that no one one would be able to access or change these constants. I had gotten these constants from online and copied and pasted from [here](https://github.com/alimasry/DES-Encryption/blob/master/Source.cpp.)
. Every box covered in class as a member function so that encryption would be modular and easy to implement. I had two major distinct functions, key_sched_des() and encrypt(). These function would do the main lifting where key_sched_des() would handle creating sub keys while encrypt would focus on computation of the rounds. The other functions were auxiliary functions to help the readability of the main two.

### PROBLEMS:
---
I was able to implement a random 64 bit key generator. I just generated random values using C++'s rand() function, and turned those values into bits. I did that until I was a string was 64 bits long. And then took away the excess bits
All the other problems were solved compared to my previous attempt to of the DES implementation.

### HOW TO BUILD AND RUN:
---
If you just enter:

> ```/usr/bin/clang++ -std=c++17 -stdlib=libc++ -c src/*cpp -I include/ -g && /usr/bin/clang++ DES.o main.o -o bin/DES -std=c++17 -stdlib=libc++ && bin/DES```

In the terminal with the folder DES_2 being the current working directory, the project should build and run.
Make sure you have Clang. If you don't hav clang you can use g++ compiler instead and just change the "-stdlib=libc++" to "-stdlib=c++17".

Or you can just use GNU make.

