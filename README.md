# CallGraphUML

A C++ CLI tool that parses a (C/C++) codebase, builds its class‐/function‐call graph, and emits a UML-style diagram.
Inputting all the source files to a program, all class and function connections are mapped and connected while remaining / unused 
classes or functions are designated as independent and isolated.

We use LibClang’s C-API to parse a translation unit, walk its AST, and pick out:

1. Class declarations

2. Free‐function declarations

3. Function-call expressions


For the timeline of this project, the main components are: 
    1. Parsing through and collecting the classes/function
    2. Building a backend for UML graph that connects all these points
    3. Display the graph

Upcoming Checkpoint:
    - Keep track of current function we're in and the class it may be a part of (class implementation can be delayed)
    - Given we have a function that we're inside (trivial), mark down the function calls inside 
    - Mark all functions that are called and not existing

Note:
    Currently there is no implementation for adding any files we want to be scanned. That features is to be added shortly to make this application
    functional.
    - Future versions of the program may allow saving files so that we can add more as we go and then print out screen when we decide
