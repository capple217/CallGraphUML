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

Probably makes sense to start with (1) so that we know how we store these objects for future use.
    
