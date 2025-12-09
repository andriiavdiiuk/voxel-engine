#include "BitArray.hpp"
#include <string>
#include "Core/Logger.hpp"
#include <bitset>
#include <limits>

namespace GameEngine
{
    BitArray::BitArray(size_t totalBits) : 
        buffer((totalBits + 7) / 8,0)
    {
    }

    void BitArray::writeBits(size_t index, size_t bitsCount, uint32_t bits)
    {
        if (bitsCount >= 32)
            bits &= std::numeric_limits<uint32_t>::max();
        else
            bits &= ((1u << bitsCount) - 1u); // Keep only lowest bitsCount bits

        size_t remainingBits = bitsCount;

        while (remainingBits > 0)
        {
            size_t byteIndex = index / 8;
            size_t bitOffsetInByte = index % 8;
            size_t bitsAvailable = 8 - bitOffsetInByte;
            size_t bitsToWrite = std::min(remainingBits, bitsAvailable);

            size_t bitIndexInInput = remainingBits - bitsToWrite;

            // Extract chunk of bits to write
            uint8_t chunk = (bits >> bitIndexInInput) & ((1u << bitsToWrite) - 1);

            // Align the chunk to its position in the target byte
            size_t targetShift = 8 - bitOffsetInByte - bitsToWrite;
            uint8_t shiftedChunk = chunk << targetShift;

            // Build a mask for the bits we're about to overwrite
            uint8_t writeMask = ((1u << bitsToWrite) - 1) << targetShift;

            // Clear target bits and insert the aligned chunk
            buffer[byteIndex] &= ~writeMask;
            buffer[byteIndex] |= shiftedChunk;

            index += bitsToWrite;
            remainingBits -= bitsToWrite;
        }
    }

    uint32_t BitArray::readBits(size_t index, size_t bitCount) const
    {
        if (bitCount > 32)
            bitCount = 32;

        uint32_t result = 0;
        size_t remainingBits = bitCount;

        while (remainingBits > 0)
        {
            size_t byteIndex = index / 8;
            size_t bitOffsetInByte = index % 8;
            size_t bitsAvailableInByte = 8 - bitOffsetInByte;
            size_t bitsToRead = std::min(remainingBits, bitsAvailableInByte);

            size_t shiftInByte = 8 - bitOffsetInByte - bitsToRead;
            uint8_t readMask = ((1u << bitsToRead) - 1u) << shiftInByte;
            uint8_t extracted = (buffer[byteIndex] & readMask) >> shiftInByte;

            // Align to most significat bit
            // Shift existing result left to make room for new bits
            result = (result << bitsToRead) | extracted;

            index += bitsToRead;
            remainingBits -= bitsToRead;
        }

        return result;
    }

}

