#pragma once
#include <vector>
#include <cstdint>

namespace GameEngine
{
    class BitArray
    {
    public:
        BitArray(size_t totalBits);
        ~BitArray() = default;

        void writeBits(size_t index, size_t bitsCount, uint32_t bits);
        uint32_t readBits(size_t index, size_t bitsCount) const;
        const std::vector<uint8_t>& getBuffer() const { return buffer; };

    private:
        std::vector<uint8_t> buffer;
    };
}   