# Huffman Encoding Project

## Introduction
This Huffman Encoding project implements a widely used method for lossless data compression. The key feature of this project is its ability to encode a text file and produce both a compressed version and a "key" for decoding, represented by the Huffman Tree. The size of the Huffman Tree, or the "key", is typically around 2KB for larger files. The space savings from this encoding method can be substantial, often achieving up to 80% reduction in file size, especially for texts with a limited set of unique characters. For texts that have a higher number of unique characters, the space savings are generally around 50%.

## Features
- **File Encoding**: Efficiently encodes text files using the Huffman coding technique.
- **Decoding Capability**: Allows the decoding of encoded files using the generated Huffman Tree.
- **Huffman Tree Serialization**: Serializes the Huffman Tree to a file, enabling the reconstruction of the tree for later decoding.
- **Performance Measurement**: Measures and reports the time taken for key operations like tree building, serialization, and file encoding/decoding.
- **Binary File Handling**: Encodes and decodes binary files for efficient storage and retrieval.
- **Error Handling**: Robust error checking during file operations.

## Getting Started
These instructions will guide you on how to set up and run the Huffman Encoding project on your local machine for development and testing purposes.

### Prerequisites
Ensure you have the following installed:
- C++ Compiler (GCC or Clang)
- Make (optional for building)

### Installing
1. Clone the repository to your local machine.
`git clone git@github.com:IlmarsKuht/Huffman-coding.git`
2. Navigate to the cloned directory.
3. Compile and run.
`make run`
or
`g++ main.cpp -o main -std=c++11
./main`

## Usage
This application takes an input text file, encodes it, and then decodes it back to verify the encoding process. The steps are as follows:

1. Place your text file (e.g., `input.txt`) in the project directory.
2. Run the application. It will read the text file, perform Huffman encoding, and generate the encoded file and Huffman Tree.
3. The encoded file will be saved as `encoded.bin`, and the Huffman Tree as `huffman_tree.txt`.
4. The application will then automatically decode `encoded.bin` using `huffman_tree.txt` and save the output in `decoded.txt`.
