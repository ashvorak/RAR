#include <iostream>
#include <memory>

#include "FileCompressor.h"

const std::string compressOption = "-c";
const std::string decompressOption = "-d";

bool isArgumentsCorrect(int argc, char** argv)
{
    return argc == 3 && (argv[1] == compressOption || argv[1] == decompressOption);
}

int main(int argc, char** argv)
{
    if (isArgumentsCorrect(argc, argv)) {
        try {
            std::unique_ptr<FileCompressor> fileCompressor = std::make_unique<FileCompressor>();

            const auto fileName = argv[2];
            if (argv[1] == compressOption) {
                std::cout << "Compress..." << std::endl;
                fileCompressor->compress(fileName);
            } else {
                std::cout << "Decompress..." << std::endl;
                fileCompressor->decompress(fileName);
            }
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    } else {
        std::cout << "Wrong arguments" << std::endl;
    }
}