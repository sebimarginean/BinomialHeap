# Binomial Heap Implementation in C++

## Overview

This project provides a detailed implementation of a Binomial Heap in C++. A Binomial Heap is an efficient data structure for implementing a priority queue, supporting a variety of operations including insertion, merge, minimum key extraction, and key decrease, all in logarithmic time.

## Features

- **Dynamic Creation**: Supports dynamic creation of binomial heaps.
- **Insertion**: Allows the insertion of nodes with a key and associated data.
- **Merge**: Enables merging two binomial heaps into one.
- **Minimum Key Extraction**: Supports extracting the node with the minimum key.
- **Decrease Key**: Facilitates decreasing the key of a node to a new lower value.
- **Traversal**: Provides methods for showing the content of the heap and displaying the structure of the binomial trees within the heap.

## Compilation and Usage

To compile the project, use a C++ compiler that supports C++11 or newer. The compilation command depends on your environment. For example, using `g++`:

```bash
g++ -std=c++11 main.cpp -o binomialHeap
