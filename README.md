# ADT
This repository conatins some common Abstract Data Types (ADT) only in C language (for the moment).

This is currently in development:
Finished:
- Stack
- Queue
- Dequeue
- Set
Requiered:
- Binary Search Tree
- Documentation
- More tests

An ADT is defined by it's set of functions, and not how those functions are implemented. That is why you can't access it's structure's definition.

The different ADT implemented on this repository are:
- Stack
- Queue
- Dequeue
- Set
- Binary Search Tree (BST)

Explanations for these ADTs are located in [ADT.md](./ADT.md).
More tests are required, they will come soon.

## Authors
- ROSEAU Baptiste [broseau@enseirb-matmeca.fr](mailto:broseau@enseirb-matmeca.fr)
- JOLIVET Arthur [ajolivet@enseirb-matmeca.fr](mailto:ajolivet@enseirb-matmeca.fr)

## How to build
#### Requirements
To build project, the following commands must be installed and reachable from `PATH`:
- make
- gcc

Optional commands
- valgrind
- doxygen

#### Instructions
You can build the project from `Makefile`.
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

## How to use it ?
The following explanations concerns all of the ADTs in this repository.

Note that all of the ADTs's implementaion require the following functions from [utils.c](./C/utils.c).
- assert_not_null
- exit_on_error
- safe_malloc

In order to use those ADTs in your project, follow these instrcuctions:
1. Copy/Paste the \<ADT\>.c and the \<ADT\>.h from this repository into your project's folder.
2. Modify the header's path in the #include from the \<ADT\>.c if necessary.
3. Copy/Paste the functions from [utils.c](./C/utils.c) into your own common file. Same for [utils.h](./C/utils.h). If you don't have a common file, you can use directly the [common](./C/common) folder.
4. Modify the header's path in the #include from the \<ADT\>.c if necessary.
5. Add the new files in your Makefile or CMakeLists.txt if you have one.

You can do the same for the tests. Note that every test require the *common_tests_utils.c* and *common_tests_utils.h*.

## How does it works ?
All of those ADTs are stocking _void*_ pointers, that is why you will have to give a pointer to that object and not the object itself.

### Copy or not copy ?
There are two diferents way of creating an empty ADT:
- \<ADT\>__empty_copy_enabled(...);
- \<ADT\>__empty_copy_disabled(...);

Note that there **are** parameters instead of "...", but it will be explained later.

#### Reasons
If copies are enabled, there will be creation of dynamically allocated copies for all the added elements.
If not, the element itself is stocked into the ADT.
For example:
```
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

That is why, if you don't want to stock a pointer to a specific object, but only it's value, prefer *copy_enabled* istead of *copy_disabled*.
However, if you **do** want to stock a pointer to the object itself, **DO NOT FREE IT** before removing it from the ATD. Even if you do, you are still able to free the ADT without a segmentaion fault, but if you try to read this object's value, you will end up with a segmentaion fault.

For sorted ADTs, you **HAVE TO** give a specific value (on the object's structure or, the result of an operation), to compare two objects. This value will **NEVER, EVER CHANGES**.
If you don't, you will break the sort, and have unexpected behaviors.
Try to do it with a constant complexity (O(1)).

#### Requiered functions
In order to be able to copy, free, debug or compare the elements you want to add in the set, the following functions are required:
- void* copy_op(void*);
- void delete_op(void*);
- void debug_op(const int*);
- int compare_op(void*, void*);

Note that *compare_op* is only required on sorted ADTs, *copy_op* and *delete_op* are only required if copy is enabled.
Here is the real prototype of \<ADT\>__empty():
- \<ADT\>__empty_copy_enabled(void *copy_op, void *delete_op, void *compare_op, void *debug_op);
- \<ADT\>__empty_copy_disabled(void *compare_op, void *debug_op);
