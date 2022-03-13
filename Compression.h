#pragma once

#include <string>

class Compression
{
public:
    Compression() = default;
    ~Compression() = default;

    virtual void compress(const std::string& inBuf, std::vector<u_int16_t>& outCodes) = 0;
    virtual void decompress(const std::vector<u_int16_t>& inCodes, std::string& outBuf) = 0;
};