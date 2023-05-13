# Authors
- ROSEAU Baptiste [broseau@enseirb-matmeca.fr](mailto:broseau@enseirb-matmeca.fr)
- JOLIVET Arthur [ajolivet@enseirb-matmeca.fr](mailto:ajolivet@enseirb-matmeca.fr)

# ADT
This repository contains some common C Abstract Data Types (ADT).
An ADT is defined by it's set of functions, and not how those functions are implemented. That is why you can't access it's structure's definition
in your code, and should only use pointers.

The different ADT implemented on this repository are:
- Stack
- Queue
- Dequeue
- Set

Binary Search Tree (BST) is currently not implemented.

Explanations for these ADTs are located in [ADT.md](./ADT.md).


## How to build
#### Requirements
To build project, the following commands must be installed and reachable from `PATH`:
- make
- gcc

Optional commands
- valgrind
- doxygen

#### Instructions
You can build the project from `Makefile` using `make build`.
The following commands are available :
```
make [help]         #To show the available commands
make build          #To build the project
make test           #To build and start all the tests
make vtest          #To build and start the tests with valgrind check
make clean          #To remove objects files, executables and installation
make <test_name>    #To build <test_name> only
```

Each ADT's .c and .h is located in different folders by using the following convention:
```
<ADT>/<ADT>.c
<ADT>/<ADT>.h
```


## How to use
The following explanations concerns all of the ADTs in this repository.

Note that all of the ADTs's implementaion require the following functions from [utils.c](./C/utils.c).
- `assert_not_null`
- `exit_on_error`
- `safe_malloc`

In order to use those ADTs in your project, follow these instrcuctions:
1. Copy/Paste the `<ADT>/*` and `common/*` from this repository into your project's folder.
2. Modify the header's path in the #include from the \<ADT\>.c if necessary.
4. Add the new files in your Makefile or CMakeLists.txt if you have one.

You can do the same for the tests. Note that every test require the `common_tests_utils.c` and `common_tests_utils.h`.


## How does it work
All of those ADTs are stocking _void*_ pointers, that is why you will have to give a pointer to that object and not the object itself.


### Copy or not copy ?
There are two diferents way of creating an empty ADT:
- \<ADT\>__empty_copy_enabled(...);
- \<ADT\>__empty_copy_disabled(...);


### Reasons
If copies are enabled, there will be creation of dynamically allocated copies for all the added elements.
If not, the element itself is stocked into the ADT.
For example:
```c
    struct set *set_cpy = set__empty_copy_enabled(...);
    struct set *set_no_cpy = set__empty_copy_disabled(...);
    for (int i = 0; i < 4; i++){
        set__add(set_cpy, &i);
        set__add(set_no_cpy, &i)
    }
```

At the end of this code, because *i*'s value changes, we will have:
- set_cpy = {0 1 2 3}
- set_no_cpy = {3} (You can't add the same element twice in a set, it's not {3 3 3 3})

That is why, if you don't want to stock a pointer to a specific object, but only it's value, prefer *copy_enabled* instead of *copy_disabled*.
However, if you **do** want to stock a pointer to the object itself, **DO NOT FREE IT** before removing it from the ATD. Even if you do, you are still able to free the ADT without a segmentaion fault, but if you try to read this object's value, you will end up with a segmentaion fault.

For sorted ADTs, you **HAVE TO** give a comparison function.
Try to do it with a constant complexity (O(1)).

### Requiered functions
In order to be able to copy, free, debug or compare the elements you want to add in the set, you have to provide the following functions:
- `void* copy_op(void*);`
- `void delete_op(void*);`
- `void debug_op(const int*);`
- `int compare_op(void*, void*);`

Note that `compare_op` is only required on sorted ADTs, `copy_op` and `delete_op` are only required if copy is enabled.
