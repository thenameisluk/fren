#pragma once
#include "stdint.h"
#include <fstream>
#include <iostream>
#include <string>

class dataArray
{
private:
    uint8_t *data;
    uint32_t size;

public:
    uint8_t *getData();
    uint32_t getSize();
    dataArray();
    dataArray(std::string filename);
    dataArray(uint8_t *data, uint32_t size);
    dataArray(dataArray &data);
    ~dataArray();
    uint8_t* steal();
    void save(std::string filename);
    void reSize(uint32_t size);
    void push(uint8_t value);
    bool getBit(uint32_t place, uint8_t bit);
    uint8_t &operator[](uint32_t place);
};

uint8_t staticDSize(uint32_t value); // 0101101
// like string view but kinda diffrent
class PbView
{
private:
    uint32_t place = 0;
    uint8_t bit = 0;
    uint8_t nowValue = 0;
    uint8_t *data;

public:
    PbView(dataArray &data);
    PbView(uint8_t *data);
    // takes the pointer to start of the array
    void reset();
    bool readBit();
    uint32_t readDynamic();
    uint32_t readStatic(uint8_t size);
    // advanced
    template <typename T>
    T readCast();
};
// writes data
class PbWriter
{
private:
    uint8_t current;
    uint8_t bit;
    dataArray data;

public:
    PbWriter();
    void clear();
    void writeBit(bool value);
    void writeDynamic(uint32_t value);
    void writeStatic(uint32_t value, uint8_t size);
    // advanced
    template <typename T>
    // do not cast class/struct that contains pointers
    void writeCast(T data);
    dataArray exportData();
};


template <typename T>
void PbWriter::writeCast(T data)
{
    T value = data;
    uint8_t *valuePTR = (uint8_t *)(&value);
    uint32_t size = sizeof(T);
    for (uint32_t i = 0; i < size; i++)
    {
        writeStatic(valuePTR[i], 8);
    }
};

template <typename T>
T PbView::readCast()
{
    T out;
    uint32_t size = sizeof(T);
    uint8_t *outPTR = (uint8_t *)(&out);
    for (uint32_t i = 0; i < size; i++)
    {
        outPTR[i] = readStatic(8);
    }
    return out;
};