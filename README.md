# Huffman Encoding Project

## Introduction
This project focuses on Huffman Encoding, a popular technique for compressing data without losing any information. Its main function is to compress a text file, creating a smaller-sized version and a "key" to decode it, which is the Huffman Tree. For bigger files, this "key" is usually about 2KB in size. This method can greatly reduce file size, often cutting it down by up to 80%, especially with texts having fewer unique characters. In cases of texts with more unique characters, the reduction in size is usually about 50%.


## Features
- **Text File Compression**: Uses Huffman coding to compress text files effectively.
- **Decompression Option**: Decodes compressed files with the help of the created Huffman Tree.
- **Huffman Tree Storage**: Saves the Huffman Tree in a file, allowing it to be used again for decoding.
- **Operation Time Tracking**: Records and displays the duration of important tasks such as constructing the tree, saving it, and compressing/decompressing files.
- **Binary File Processing**: Manages the compression and decompression of binary files for better storage efficiency.
- **Error Management**:  Implements thorough error checks during file-related processes.


### Prerequisites
- C++ Compiler (GCC or Clang)
- Make (optional for building)

### Installing
1. Clone the repository to your local machine.
`git@github.com:Jiaorong0/Huffman-Encoding-Project.git`
2. Navigate to the cloned directory.
3. Compile and run.
`make run`
or
`g++ main.cpp -o main -std=c++11
./main`

## Usage
1. Put your text file (like input.txt) into the project folder.
2. When you start the software, it reads the text file, applies Huffman encoding, and creates an encoded file along with a Huffman Tree.
3. The encoded data is stored in a file named encoded.bin, and the Huffman Tree in huffman_tree.txt.
4. Next, the software automatically uses huffman_tree.txt to decode encoded.bin and stores the result in decoded.txt.




