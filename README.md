# Linux Shell



###	 To Compile :
```
make
```

### To use the Assembler :
In interactive mode
```
./bin/M-shell
```
Or to start in batch mode
```
./bin/M-shell batch_file
```


## Main features

* Process creation in background & foreground.
* garbage collection per line. memory-leaks free and memory-errors free. small memory footprint.
* Interactive & Batch mode support.
* History of previous commands and Logs of processes details.
* Supports commands cd, echo, pwd, history, exit and expressions.
* Supports variable definition and retrieval.



## Data Structures implemented in the shell

```
          +-------------------------+
          |                         |
          |     Data Structures     |
          |                         |
          +-------------------------+
                       |
                       |
                       v
             +---------+----------+
             |                    |
             | Singly Linked List |
             |                    |
             +--------------------+
```

* Implementation of Singly Linked List with Arrays Handles the storage of the sequential data in the Shell.
* Hash Maps was used in previous version to implement the garbage collection process, but it was removed due to huge constant overhead in compare to linked list or vector,
since the terminal is simple enough with not huge free/reallocation calls, then it is still O(1) in malloc() but with much better overhead, specially that in each new line
the whole structures needs to be initialized again, so using lists improve the efficiency.




## Modules in the shell

```
                 +--------------------+    +--------------------+
                 |                    |    |                    |
                 |  Directory Module  |    |  File I/O Module   |
                 |                    |    |                    |
                 +---------+----------+    +---------+----------+
                           ^                         ^
+--------------------+     |                         |     +--------------------+
|                    |     |                         |     |                    |
|  Signals Handler   +<----------------------------------->+     Shell I/O      |
|                    |     |                         |     |                    |
+--------------------+     |                         |     +--------------------+
                           |      Shell Modules      |
+--------------------+     |                         |     +--------------------+
|                    |     |                         |     |                    |
|   Memory Manager   +<----------------------------------->+      Text I/O      |
|                    |     |                         |     |                    |
+--------------------+     |                         |     +--------------------+
                           v                         v
                +----------+---------+     +---------+----------+
                |                    |     |                    |
                |    Modes Module    |     |  Executors Module  |
                |                    |     |                    |
                +--------------------+     +--------------------+
```


* In the Shell, Every module contains several classes, each class specified by an Interface and have a unique return type with a set of unique return values.
* Set of unique return values are set for each class for easier debugging and more helpful error reporting to the user.
* The Modularity in the design helps in expanding/modifying the functionality of a module independently from other modules.<br />


* Directory Module : Handles the work with the current directory and moving from and to different directories.
* Text I/O Module : Handles the work with terminal and files in low level manner.
* File I/O Module : Handles the work with files in a high level manner and delegate the low level handling to Text I/O Module.
* Shell I/O Module : Handles the input and the output in the terminal plus doing processing in the input.
* Modes Module : Contains different Modes like Interactive or Batch mode. New modes can be added later if needed.
* Signals Handler Module : Handle the needed signals received from the operating system.
* Memory Manager Module : Implementation of a garbage collector to handle allocation and freeing of the data.
* Executors Module : Implementation of several Executors to execute the user input - as cd, echo, pwd, history, exit and expressions - , Can be expanded if needed.




## Notes

* the makefile was taken from [mbcrawfo/GenericMakefile](https://github.com/mbcrawfo/GenericMakefile), Thank you.