#include "LzwCompression.h"

#include <sstream>

static constexpr int ASCII_TABLE_SIZE = 256;

LzwCompression::LzwCompression() = default;

LzwCompression::~LzwCompression() = default;

LzwCompression::LzwCompression(const LzwCompression&) = default;

LzwCompression::LzwCompression(LzwCompression&&) noexcept = default;

LzwCompression& LzwCompression::operator=(const LzwCompression&) = default;

LzwCompression& LzwCompression::operator=(LzwCompression&&) noexcept = default;

void LzwCompression::compress(const std::string& inBuf, std::vector<u_int16_t>& outCodes)
{
    if (inBuf.empty()) {
        return;
    }

    std::unordered_map<std::string, u_int16_t> dictionary;
    for (int code = 0; code < ASCII_TABLE_SIZE; ++code) {
        std::string sym(1, static_cast<char>(code));
        dictionary[sym] = code;
    }

    int code = ASCII_TABLE_SIZE;
    std::string str(1, inBuf[0]);
    for (int i = 1; i < inBuf.length(); ++i) {
        if (dictionary.find(str + inBuf[i]) != dictionary.end()) {
            str += inBuf[i];
        } else {
            outCodes.push_back(dictionary[str]);
            dictionary[str + inBuf[i]] = code++;
            str = inBuf[i];
        }
    }
    outCodes.push_back(dictionary[str]);
}

void LzwCompression::decompress(const std::vector<u_int16_t>& inCodes, std::string& outBuf)
{
    if (inCodes.empty()) {
        return;
    }

    std::unordered_map<u_int16_t, std::string> dictionary;
    for (int code = 0; code < ASCII_TABLE_SIZE; ++code) {
        std::string sym(1, static_cast<char>(code));
        dictionary[code] = sym;
    }

    std::string str;
    std::stringstream ss;
    u_int16_t code = inCodes[0];
    u_int16_t count = ASCII_TABLE_SIZE;
    std::string sym(1, static_cast<char>(code));
    ss << dictionary[code];
    for (int i = 1; i < inCodes.size(); ++i) {
        if (dictionary.find(inCodes[i]) != dictionary.end()) {
            str = dictionary[inCodes[i]];
        } else {
            str = dictionary[code];
            str += sym;
        }
        ss << str;

        sym = str[0];
        dictionary[count++] = dictionary[code] + sym;
        code = inCodes[i];
    }

    outBuf = ss.str();
}
