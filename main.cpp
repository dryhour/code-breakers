#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <algorithm>

const std::string filename = "input.txt";

std::string readFile() {
    std::string content;
    std::ifstream file(filename);

    std::getline(file, content);

    return content;
}

void appendFile(std::string& text) {
    std::ofstream file(filename, std::ios::app);
    file << text;
}

void overwriteFile(std::string text) {
    std::ofstream file(filename);
    file << text;
}

std::string cipher(std::string text, int shift, std::string mode) {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string encoded_message;

    for (char c : text) {
        if (std::isalpha(c)) {
            char lower_c = std::tolower(c);
            size_t index = alphabet.find(lower_c);
            char encoded_char = alphabet[(index + ((mode == "encode") ? shift : -shift) + 26) % 26];
            encoded_message += encoded_char;
        } else {
            encoded_message += c;
        }
    }

    return encoded_message;
}

std::string vigenere(std::string text, std::string key, std::string mode) {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string encoded_message;
    int i = 0;

    for (char c : text) {
        if (std::isalpha(c)) {
            char lower_c = std::tolower(c);
            size_t index = alphabet.find(lower_c);
            size_t shift = key[i % key.length()] - 'a';
            char encoded_char = alphabet[(index + ((mode == "encode") ? shift : -shift) + 26) % 26];
            encoded_message += encoded_char;
            i++;
        } else {
            encoded_message += c;
        }
    }

    return encoded_message;
}


void testCipher(
    std::string original, 
    std::string expected, 
    int shift, 
    std::string mode, 
    int test_number, 
    std::string cipher_type,
    std::string key
) {
    std::string encoded_message = (cipher_type=="vigenere") ? vigenere(original, key, mode) : cipher(original, shift, mode);
    overwriteFile(encoded_message);
    const bool passed = (readFile() == expected);
    if (passed == false) {
        std::cerr 
            << "=========TEST "<<std::to_string(test_number)<<"=========" << std::endl
            << "Original: " << original << std::endl
            << "Expected: " << expected << std::endl
            << "Got: " << readFile() << std::endl
            << "Result: " << (passed ? "Passed✅" : "Failed❌") << std::endl
            << "========================" << std::endl;
        throw std::invalid_argument("Test failed^");
    }
}

void tests() {
    // TEST CIPHER
    std::cout << std::endl << "=======================";
    std::cout << std::endl << "Testing Cipher Function";
    testCipher("Hello, World!", "khoor, zruog!", 3, "encode", 1, "cipher", "");
    testCipher(readFile(), "hello, world!", 3, "decode", 2, "cipher", "");
    testCipher("abcd", "bcde", 1, "encode", 3, "cipher", "");
    testCipher(readFile(), "abcd", 1, "decode", 4, "cipher", "");
    std::cout << "✅";

    // TEST ROT CIPHER
    std::cout << std::endl << "Testing ROT Function";
    testCipher("Hello", "uryyb", 13, "encode", 1, "rot", "");
    testCipher(readFile(), "hello", 13, "decode", 2, "rot", "");
    testCipher("fnynq", "salad", 13, "encode", 3, "rot", "");
    testCipher(readFile(), "fnynq", 13, "decode", 4, "rot", "");
    std::cout << "✅";

    // TEST VIGENERE CIPHER
    std::cout << std::endl << "Testing Vigenere Function";
    testCipher("Hello", "rijvs", 0, "encode", 1, "vigenere", "key");
    testCipher(readFile(), "hello", 0, "decode", 2, "vigenere", "key");
    testCipher("lwapp", "salad", 0, "encode", 3, "vigenere", "hello");
    testCipher(readFile(), "lwapp", 0, "decode", 4, "vigenere", "hello");
    std::cout << "✅";

    std::cout << std::endl << "=======================";

    std::cout << std::endl << "ALL TESTS PASSED✅" << std::endl;
    std::cout << "=======================" << std::endl << std::endl;

}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: ./program <inputFile> <outputFile> <transformation> [shift/key] [encode/decode]" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string transformation = argv[3];

    // Read from the actual input file
    std::ifstream inFile(inputFile);
    std::string content;
    std::getline(inFile, content);
    inFile.close();

    std::string result = "";

    if (transformation == "upper") {
        for (char c : content) result += std::toupper(c);

    } else if (transformation == "lower") {
        for (char c : content) result += std::tolower(c);

    } else if (transformation == "reverse") {
        result = content;
        std::reverse(result.begin(), result.end());

    } else if (transformation == "cipher") {
        if (argc < 6) { std::cerr << "Usage: ./program <in> <out> cipher <shift> <encode/decode>" << std::endl; return 1; }
        int shift = std::stoi(argv[4]);
        std::string mode = argv[5];
        result = cipher(content, shift, mode);

    } else if (transformation == "rot") {
        if (argc < 5) { std::cerr << "Usage: ./program <in> <out> rot <shift>" << std::endl; return 1; }
        int shift = std::stoi(argv[4]);
        std::string mode = (argc >= 6) ? argv[5] : "encode";
        result = cipher(content, shift, mode);

    } else if (transformation == "vigenere") {
        if (argc < 6) { std::cerr << "Usage: ./program <in> <out> vigenere <key> <encode/decode>" << std::endl; return 1; }
        std::string key = argv[4];
        std::string mode = argv[5];
        result = vigenere(content, key, mode);

    } else if (transformation == "tests") {
        tests();
        return 0;

    } else {
        std::cerr << "Unknown transformation: " << transformation << std::endl;
        return 1;
    }

    // Write to the actual output file
    std::ofstream outFile(outputFile);
    outFile << result;
    outFile.close();

    std::cout << "Result: " << result << std::endl;
    return 0;
}