#include <gtest/gtest.h>
#include <Common/BitArray.hpp>
#include <bitset>

TEST(BitArrayTest, ZeroSize) {
    GameEngine::BitArray ba = GameEngine::BitArray(0);
    auto buffer = ba.getBuffer();
    EXPECT_EQ(buffer.size(), 0);
}

TEST(BitArrayTest, MultipleWritetesSameSize) {
    GameEngine::BitArray ba = GameEngine::BitArray(16);
    ba.writeBits(0, 3, 0b100);
    ba.writeBits(3, 3, 0b101);
    ba.writeBits(6, 3, 0b111);
    ba.writeBits(9, 3, 0b011);
    ba.writeBits(12, 3, 0b001);

    EXPECT_EQ(ba.readBits(0, 3), 0b100);
    EXPECT_EQ(ba.readBits(3, 3), 0b101);
    EXPECT_EQ(ba.readBits(6, 3), 0b111);
    EXPECT_EQ(ba.readBits(9, 3), 0b011);
    EXPECT_EQ(ba.readBits(12, 3), 0b001);
}

TEST(BitArrayTest, MultipleWritesDifferentSize) {
    GameEngine::BitArray ba = GameEngine::BitArray(24);
    ba.writeBits(0, 2, 0b10);
    ba.writeBits(2, 3, 0b101);
    ba.writeBits(5, 2, 0b11);
    ba.writeBits(7, 1, 0b1);
    ba.writeBits(8, 4, 0b1001);
    ba.writeBits(12, 1, 0b0);
    ba.writeBits(13, 2, 0b11);

    EXPECT_EQ(ba.readBits(0, 2), 0b10);
    EXPECT_EQ(ba.readBits(2, 3), 0b101);
    EXPECT_EQ(ba.readBits(5, 2), 0b11);
    EXPECT_EQ(ba.readBits(7, 1), 0b1);
    EXPECT_EQ(ba.readBits(8, 4), 0b1001);
    EXPECT_EQ(ba.readBits(12, 1), 0b0);
    EXPECT_EQ(ba.readBits(13, 2), 0b11);
}

TEST(BitArrayTest, WriteExactly32Bits) {
    GameEngine::BitArray ba(32);
    uint32_t value = 0xffffffff;

    ba.writeBits(0, 32, value);
    EXPECT_EQ(ba.readBits(0, 32), value);
}

TEST(BitArrayTest, ZeroBitWrite) {
    GameEngine::BitArray ba(16);

    ba.writeBits(0, 0, 0b101010);
    EXPECT_EQ(ba.readBits(0, 16), 0);
}

TEST(BitArrayTest, OverlappingWrites) {
    GameEngine::BitArray ba(16);

    ba.writeBits(0, 4, 0b1111);
    ba.writeBits(2, 2, 0b00);
    EXPECT_EQ(ba.readBits(0, 4), 0b1100);
}
