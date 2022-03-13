#include "Utils.h"

#include <fstream>
#include <sstream>

bool isFileExist(const std::string& fileName)
{
    return std::filesystem::exists(fileName);
}

std::string readFromFile(const std::string& fileName)
{
    std::ifstream t(fileName);
    std::stringstream ss;
    ss << t.rdbuf();
    t.close();
    return ss.str();
}

std::vector<uint16_t> readFromBinaryFile(const std::string& fileName)
{
    std::ifstream stream(fileName, std::ios::in | std::ios::binary);
    std::vector<unsigned char> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    std::vector<uint16_t> data;
    for( unsigned int i=0;i < contents.size(); i+=2){
        uint16_t temp = ((unsigned short)contents[i+0]) | (((unsigned short)contents[i+1])<<8);
        data.push_back(temp);
    }

    return data;
}

void writeToFile(const std::string& fileName, const std::string& data)
{
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::binary);
    file << data;
    file.close();
}

void writeToBinaryFile(const std::string& fileName, const std::vector<uint16_t>& data)
{
    std::ofstream file;
    file.open(fileName, std::ios::binary | std::ios::out);
    file.write( reinterpret_cast<const char *>(&data[0]), data.size() * sizeof(uint16_t));
    file.close();
}
