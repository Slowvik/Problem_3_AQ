Project was originally written in VSCode 1.87.0, compiled and run on Windows 10 with g++12.2.0. Minimum C++ version required: C++11.

Steps to run the code:
1. git clone https://github.com/Slowvik/Problem_3_AQ. Or simply download the version_queue.h header and use it in your code. main.cpp contains some sample operations on the queue.
2. On windows, simply compile with g++ main.cpp -o main

Features of the version queue:
1. It is assumed that VERSION NUMBERS are integers, as shown in the question. Floating point/strings will require further code.
2. Designed without using any STL containers/algorithms, it is based on a dynamic array which is resized if needed.
3. To maintain versions, an array of helper structs containing start and endpoints corresponding to a version number is used.
4. The version_queue has been templated so that it can work with different primitive types. Storing user-defined objects in it will further require overloading several operators (such as >, ==, etc).
5. The version_queue has been equipped with several functions that are commonly found in similar STL containers, such as front(), back(), size(), etc.
6. Iterator support for version_queue is available. version_queue can now be used with STL Algorithms and c++17 loops.
7. The main.cpp file contains sample operations performed and timed using the system clock.

Enqueue and Dequeue times:
1. Sample enqueue and dequeue operations involving 1,000 to 10,000,000 elements each are timed using the system clock. For 1,000,000 operations, the total time taken for either operation is of the order of ~10 ms. This increases lineraly as the number of operations increases, suggesting that it is O(N). This is expected since we are using a basic C++ array as the base container, and iterating over a continuous array takes O(N) time. There is some overhead due to resizing, which is required if the initla size of the container is not large enough.

Improvements scheduled:
1. Iterator support: backward iterator to be implemented with functions rbegin() and rend()
