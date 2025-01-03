# Syhmac's C program for multiplying matrices

## Initial goals
1. Input matrices are stored in two separate `.txt` files.
2. Program checks if the matrices can be multiplied.
3. Program does multiplication on two 2D arrays - referred only by the RAM.
4. The result matrix is being saved to the external `.txt` file.
5. RAM is allocated automatically.
6. No memory leaks, RAM is correctly freed.
7. Input matrices takes any integers from 0 to 100.
8. Read-friendly code.
9. Function based code.

## Input file format
Both input files are formated in the same way. In this repository, you will find 2 example files.
(The files are in the `cmake-build-debug` directory, where the compiled program is stored.)
To multiply different matrix, replace the contents of the example files following the rules below.  

In the first line, you should include a size of the matrix. First number describes the amount of columns.
Second number - separated by a single whitespace - describes the number of rows.
For example:
```
3 4
```
Means that the matrix will have 3 rows and 4 columns.

Following lines should include the matrix of the size defined in the first line.
Every item of the matrix should be separated by a single whitespace. For example:
``` 
4 3
6 2 3
2 3 4
9 8 7
1 9 2
```
Where first line defines the size, and following lines include the matrix.

## Output file format
Program will create a file called `result.txt` if the input matrices can be multiplied.
Result file will contain the result matrix where items in rows are seperated by a single whitespace.
Rows are seperated by a newline character. For example:
```
13 12 8 11 
23 16 16 23 
21 17 13 19 
13 12 8 11 

```

## Building
Build using CMake 3.29 or newer using `CMakeList.txt`