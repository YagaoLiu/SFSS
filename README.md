## Shortest Fully-Sanitized String ##

# Description #

Here is a C++ implementation for *Shortest Fully-Sanitized String* with integer alphabet.

## Compile ##

Run `make` to compile.

## How to use ##

`./sfss_int.o a Data n Sen m k Output`

  `a` should be an integer for the size of alphabet.

  `Data` should be the file name of the set of strings. In the file, each line is a string and each character is an integer and separated with space.

  `n` should be an integer representing the number of strings in the Dataset.

  `Sen` should be the file name of the sensitive patterns. Each line is a pattern and each character is an integer and separated with space.

  `m` should be an integer representing the number of sensitive patterns.

  `k` is the forbidden length.

  `Output` is the file name for the output
  
An example:
`./sfss_int.o 4 Text.txt 1 pattern.txt 2 3 res.txt`


## LIS ##
In the folder LIS it is an R implementation for the distance matrix based on LIS distance.
