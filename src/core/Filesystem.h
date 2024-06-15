#pragma once

#include "core/AnimationNode.h"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

namespace ComcoEditor
{
  template<typename T>
  void SaveToBinaryFile(const T* data, size_t data_size, size_t n, const std::string& filename)
  {
    std::ofstream ofs("./assets/" + filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Could not open file for writing." << std::endl;
        return;
    }

    ofs.write(reinterpret_cast<const char*>(data), n*data_size);
    // for(int i=0; i<n;++i)
    // {
    //     std::cout << ((AnimationNode*)data+i)->m_Transform.m_Position.x << std::endl;
    // }
    ofs.close();
  }

  template<typename T>
  T* LoadBinaryFile(const std::string& filename, size_t& __n)
  {
    std::ifstream ifs("./assets/" + filename, std::ios::binary | std::ios::ate);
    if (!ifs) {
        std::cerr << "Could not open file for reading." << std::endl;
        return nullptr;
    }

    std::streampos fileSize = ifs.tellg();
    ifs.seekg(0, std::ios_base::beg);

    __n = fileSize / sizeof(T);
    T* data = new T[__n];//(T*)malloc(fileSize);

    ifs.read(reinterpret_cast<char*>(data), fileSize);
    ifs.close();
    return data;
  }
}
