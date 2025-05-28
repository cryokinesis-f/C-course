Written on MacOS 
for Mac use clang 
clang -std=c99 -Wall -Wextra -pedantic <file-name>.c -o <file-name>

in Huffman supertask you should use
./h <flag> <input-file> <output-file>
flags: c (for compress)
       d (for decompress)


example: ./h c input.txt test.bin
         ./h d test.bin output.txt
