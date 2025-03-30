# Multi-threaded Merge Sort in C++

This project implements a multi-threaded merge sort algorithm in C++. The program uses threads to parallelize the sorting process, making it more efficient for large datasets.

## Compilation Instructions

To compile the program, run the following command in your terminal:

```bash
git clone https://github.com/akashkinkarpandey/MultiThreaded-Merge-Sort.git 
g++ -o multithreadedsortcomparison src/main.cpp src/sorting/parallelMergeSort.cpp src/sorting/simpleMergeSort.cpp -I. -pthread
./multithreadedsortcomparison.exe
```
