#pragma once

#include "Compression.h"

#include <vector>
#include <unordered_map>

class LzwCompression : public Compression
{
public:
    LzwCompression();
    ~LzwCompression();

    LzwCompression(const LzwCompression&);
    LzwCompression(LzwCompression&&) noexcept;
    LzwCompression& operator=(const LzwCompression&);
    LzwCompression& operator=(LzwCompression&&) noexcept;

    void compress(const std::string& inBuf, std::vector<u_int16_t>& outCodes) override;
    void decompress(const std::vector<u_int16_t>& inCodes, std::string& outBuf) override;
};
