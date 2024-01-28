## Operation System - Task 1

### Table of Contents

1. [Question 1 - Debugging Exercise](#question-1---debugging-exercise)
2. [Question 2 - pifagor3 Program](#question-2---pifagor3-program)
3. [Question 3 - Encriptor Library](#question-3---encriptor-library)
4. [Question 4 - MyZip and MyUnzip](#question-4---myzip-and-myunzip)

### Question 1 - Debugging Exercise

This section contains two bugs, Bug A and Bug C, for debugging practice.

### Bugs Description

- **Bug A**: Program crashes due to division by zero.
- **Bug C**: Program crashes due to infinite recursion.

### Usage

1. Compile the program using the provided Makefile.
2. Run the program without debugger (`./buga`) or with debugger (`./buga_with_debugger`) for Bug A. 
   For Bug C, use `./bugc` and `./bugc_with_debugger` respectively.
3. Follow the prompts.

### Question 2 - pifagor3 Program

The `pifagor3` program checks if three input side lengths form a Pythagorean triple.

### Usage

1. Compile the program using the provided Makefile.
2. Run the program (`./pifagor3`) and enter the lengths of the triangle's sides.
3. Follow the prompts.

### Question 3 - Encriptor Library

This section describes the `encriptor` library, which provides encoding and decoding functionalities.

### Functions

- `createCodec`: Creates a codec structure based on the provided key.
- `encode`: Encodes the input text using the provided codec.
- `decode`: Decodes the input text using the provided codec.
- `freecodec`: Frees the memory allocated for the codec structure.

### Usage

1. Compile the library using the provided Makefile.
2. Run the programs for encoding and decoding with the appropriate arguments. 
For example: To encode a file named 'input.txt' and save the result to 'output.txt', use the following command in the terminal: `./encode input.txt output.txt`
Similarly, to decode a file named 'input.txt' and save the result to 'output.txt', use the following command: `./decode input.txt output.txt`
These commands allow you to perform encoding and decoding operations on files conveniently in the terminal.

### Question 4 - MyZip and MyUnzip

The `myzip` and `myunzip` programs compress, encrypt, decompress, and decrypt files.

### Dependencies

- `tar`: For archiving directories and files.
- Compression utility (`gzip`): For compressing the archived file.
- `gpg`: For encrypting and decrypting the compressed file.

### Usage

1. Compile the programs using the provided Makefile.
2. To run the programs, use the appropriate commands with the following arguments:
For myzip, provide the directory or file name to be compressed:`./myzip <directory_name>`
For myunzip, provide the name of the compressed file: './myunzip <compressed_file>'
After executing the commands, follow any prompts that appear during the compression or decompression processes.

`Note: ` In the `myzip` program, you will be prompted to enter the passphrase '12345678' for encryption.


### Assumptions and Considerations

- All external utilities are assumed to execute successfully.
- The input is assumed to be valid, and the programs are designed to operate with a single parameter.

