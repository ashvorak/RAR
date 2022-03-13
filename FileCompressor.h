#pragma once

#include "Compression.h"

class FileCompressor final
{
public:
    enum class Algorithm {
        kLZW
    };

    explicit FileCompressor(Algorithm algorithm = Algorithm::kLZW);
    ~FileCompressor();

    FileCompressor(const FileCompressor&) = delete;
    FileCompressor(FileCompressor&&) noexcept;
    FileCompressor& operator=(const FileCompressor&) = delete;
    FileCompressor& operator=(FileCompressor&&) noexcept;

    void compress(const std::string& fileName);
    void decompress(const std::string& fileName);

    class FileNotExistException : public std::exception
    {
    public:
        FileNotExistException();
        ~FileNotExistException() noexcept override;

        [[nodiscard]] const char* what() const noexcept override;
    };

private:
    std::unique_ptr<Compression> m_compressAlgorithm;
};
