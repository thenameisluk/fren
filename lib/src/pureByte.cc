#include "../include/pureByte.hpp"
uint8_t *dataArray::steal()
{
    uint8_t* out = data;
    this->size = 0;
    this->data = nullptr;
    return out;
};
uint8_t *dataArray::getData()
{
    return data;
};
uint32_t dataArray::getSize()
{
    return size;
};
dataArray::dataArray()
{
    this->size = 0;
    this->data = nullptr;
}
dataArray::dataArray(std::string filename)
{
    std::ifstream infile(filename, std::ios::binary);
    if (!infile.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    infile.seekg(0, infile.end);
    size_t file_size = infile.tellg();
    infile.seekg(0, infile.beg);
    data = new uint8_t[file_size];
    infile.read(reinterpret_cast<char *>(data), file_size);
    infile.close();
};
dataArray::dataArray(uint8_t *data, uint32_t size)
{
    this->size = size;
    if (this->size == 0)
        this->data = nullptr;
    else
    {
        this->data = new uint8_t[size];
        for (uint32_t i = 0; i < size; i++)
        {
            this->data[i] = data[i];
        }
    }
};
dataArray::dataArray(dataArray &data)
{
    this->size = data.size;
    if (this->size == 0)
        this->data = nullptr;
    else
    {
        this->data = new uint8_t[this->size];
        for (uint32_t i = 0; i < this->size; i++)
        {
            this->data[i] = data.data[i];
        }
    }
};
dataArray::~dataArray()
{
    if (this->data == 0 || this->data == nullptr)
        return;
    else
    {
        delete[] this->data;
    }
};
void dataArray::save(std::string filename)
{
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.is_open())
    {
        throw std::runtime_error("Failed to write file: " + filename);
    }
    outfile.write(reinterpret_cast<char *>(this->data), size);
    outfile.flush();
    outfile.close();
};
void dataArray::reSize(uint32_t size)
{
    if (this->size == size)
        return;

    if (size == 0)
    {
        if (this->data == nullptr)
            return;

        delete[] this->data;
        this->data = nullptr;

        return;
    }
    uint8_t *newData = new uint8_t[size];
    for (uint32_t i = 0; i < size; i++)
    {
        if (this->size > i)
            newData[i] = this->data[i];
        else
            newData[i] = 0;
    }
    delete[] this->data;
    this->data = newData;
    this->size = size;
};
void dataArray::push(uint8_t value)
{
    reSize(this->size + 1);
    data[this->size - 1] = value;
};
bool dataArray::getBit(uint32_t place, uint8_t bit)
{
    if (place >= this->size)
        return false;
    return bool((this->data[place] >> (bit & 0b00000111)) & 0b00000001);
};
uint8_t &dataArray::operator[](uint32_t place)
{
    if (place >= this->size)
        throw "you are trying to access value that is not inside this dataArray";
    return this->data[place];
};

// helper function

// tells you how much bytes you need for a number
uint8_t staticDSize(uint32_t value)
{
    if (value < 2)
        return 1;
    else
    {
        uint32_t candidate = 2;
        uint32_t possible = 4;
        while (true)
        {
            if (value < possible)
                return candidate;
            candidate++;
            possible <<= 1;
        }
    }
}

// PbView

PbView::PbView(dataArray &data) : data(data.getData())
{
    reset();
};
PbView::PbView(uint8_t *data) : data(data)
{
    reset();
};
void PbView::reset()
{
    place = 0;
    bit = 0b10000000;
    nowValue = data[place];
};
// reads one bit
bool PbView::readBit()
{
    if (bit == 0)
    {
        place++;
        nowValue = data[place];
        bit = 0b10000000;
    }
    bool out = nowValue & (bit);
    bit >>= 1;
    return out;
};
// reads data like 11110 where 110 is 3 and 0 is 1
uint32_t PbView::readDynamic()
{
    uint32_t out = 1;
    while (readBit())
    {
        // increment until get 0 bit
        out++;
    }
    return out;
};
// reads data like 10110 where 101(3) is 5 and 0(1) is 1
uint32_t PbView::readStatic(uint8_t size)
{
    uint32_t out = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        out <<= 1;
        out |= (uint32_t)readBit();
    }
    return out;
};

// PbWriter
PbWriter::PbWriter()
{
    clear();
};
// clears everyting
void PbWriter::clear()
{
    data.reSize(0);
    current = 0;
    bit = 0b10000000;
};
// writes exactly one bit
void PbWriter::writeBit(bool value)
{
    if (bit == 0)
    {
        bit = 0b10000000;
        data.push(current);
        current = 0;
    }
    if (value)
        current |= bit;
    bit >>= 1;
};
// writes value like 1111111110 where 1 is 0 and 4 is 1110
void PbWriter::writeDynamic(uint32_t value)
{
    for (uint32_t i = 0; i < value - 1; i++)
    {
        writeBit(true);
    }
    if (value != 0)
        writeBit(false);
};
// wites value like 101001 where 3(4) is 100 and 3(5) is 101
void PbWriter::writeStatic(uint32_t value, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        writeBit((value >> (size - (1 + i))) & 1);
    }
};

// gives you data you've written
dataArray PbWriter::exportData()
{
    dataArray out = data;
    if (bit != 0b10000000)
        out.push(current);
    return out;
};