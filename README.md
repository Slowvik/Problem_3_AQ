Steps to run the code:

1. git clone https://github.com/Slowvik/Problem_3_AQ
2. There is already a unix makefile present in /build, but a fresh executable(/makefile) can be generated as follows: (NOTE: NEW MAKEFILES ARE NO LONGER UPLOADED. Only CMakeLists will be updated)
3. On windows: "cmake .." will create Visual Studio solution files by default. I prefer compiling with the command line: "g++ main.cpp -o outfile"
4. On Linux: "cmake .." followed by "make" will create an executable called version_queue_tester (as specified in the CMakeLists.txt file)
5. Project was originally written in VSCode 1.87.0, compiled and run on Windows 10 with g++12.2.0. Minimumm C++ version required: C++11.

Features of the version queue:
1. It is assumed that version numbers are integers, as shown in the question. Floating point/strings will require further features.
2. Designed without using any STL containers/algorithms, it is based on a dynamic array which is resized if needed.
3. To maintain versions, an array of helper structs containing start and endpoints corresponding to a version number is used.
4. The version_queue has been templated so that it can work with different primitive types. Storing objects in it will further require overloading several operators (such as >, ==, etc).
5. The version_queue has been equipped with several functions that are commonly found in similar STL containers, such as front(), back(), size(), etc.
6. Iterator support for version_queue is not available currently. It can be implemented using a helper struct if required, for closer resemblance to an STL container or for use with STL algorithms.
7. The main.cpp file contains sample operations performed and timed using the system clock. 

Known Issues
> If the version_queue is declared within a scope (inside main), allocation/resizing fails at around ~50,000 elements. To navigate around this, it is advised to declare the version_queue OUTSIDE the scope as a global variable (if large queue sizes are required)
