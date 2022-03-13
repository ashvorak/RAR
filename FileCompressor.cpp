#include "FileCompressor.h"

#include <memory>
#include <vector>

#include "Utils.h"
#include "LzwCompression.h"

FileCompressor::FileCompressor(Algorithm algorithm)
{
    switch (algorithm) {
        case Algorithm::kLZW:
            m_compressAlgorithm = std::make_unique<LzwCompression>();
            break;
        default:
            break;
    }
}

FileCompressor::~FileCompressor() = default;

FileCompressor::FileCompressor(FileCompressor&&) noexcept  = default;

FileCompressor& FileCompressor::operator=(FileCompressor&&) noexcept = default;

void FileCompressor::compress(const std::string& fileName)
{
    if (!isFileExist(fileName)) {
        throw FileNotExistException();
    }
    const auto inBuff = readFromFile(fileName);
    std::vector<uint16_t> outCodes;
    m_compressAlgorithm->compress(inBuff, outCodes);

    writeToBinaryFile(fileName + ".out", outCodes);
}

void FileCompressor::decompress(const std::string& fileName)
{
    const auto inCodes = readFromBinaryFile(fileName);
    std::string outBuff;

    m_compressAlgorithm->decompress(inCodes, outBuff);
    writeToFile(fileName + ".out", outBuff);
}

FileCompressor::FileNotExistException::FileNotExistException() = default;

FileCompressor::FileNotExistException::~FileNotExistException() noexcept = default;

const char* FileCompressor::FileNotExistException::what() const noexcept {
    return "File not exist";
}
