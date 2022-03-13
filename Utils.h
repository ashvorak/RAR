#pragma once

#include <string>
#include <vector>

bool isFileExist(const std::string& fileName);

std::string readFromFile(const std::string& fileName);
std::vector<uint16_t> readFromBinaryFile(const std::string& fileName);

void writeToFile(const std::string& fileName, const std::string& data);
void writeToBinaryFile(const std::string& fileName, const std::vector<uint16_t>& data);
