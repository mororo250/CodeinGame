#pragma once

#include <cstdint>
#include <vector>
#include <iostream>

struct BitBoard
{
	BitBoard() :m_bitboard(ZERO) {};
	BitBoard(int_fast64_t bitboard):m_bitboard(bitboard){}

	static constexpr int_fast8_t cols = 7;

	static constexpr int_fast8_t shiftNE = -(cols + 1);
	static constexpr int_fast8_t shiftE = 1;
	static constexpr int_fast8_t shiftSE = -cols;
	static constexpr int_fast8_t shiftSW = -shiftNE;
	static constexpr int_fast8_t shiftW = -shiftE;
	static constexpr int_fast8_t shiftNW = -shiftSE;

	inline void dilation() {m_bitboard = m_bitboard | (m_bitboard >> shiftNE) | (m_bitboard >> shiftE)  | (m_bitboard >> shiftSE)
		| (m_bitboard >> shiftSW) | (m_bitboard >> shiftW) | (m_bitboard >> shiftNW); }

	std::int_fast64_t m_bitboard;

	static const std::vector<int_fast64_t> CELLS;
	constexpr static int_fast64_t ZERO = 0b0000000000000000000000000000000000000000000000000000000000000000;

	inline BitBoard& operator=(BitBoard const& other) { m_bitboard = other.m_bitboard; return *this; }
	inline BitBoard& operator&=(BitBoard const& other) { m_bitboard &= m_bitboard & other.m_bitboard; return *this; }
	inline BitBoard& operator|=(BitBoard const& other) { m_bitboard |= other.m_bitboard; return *this; }
	inline BitBoard& operator^=(BitBoard const& other) { m_bitboard ^= other.m_bitboard; return *this; }
	inline BitBoard& operator<<=(BitBoard const& other) { m_bitboard <<= other.m_bitboard; return *this; }
	inline BitBoard& operator>>=(BitBoard const& other) { m_bitboard >>= other.m_bitboard; return *this; }


	inline BitBoard operator&(BitBoard const& other) { return BitBoard(m_bitboard & other.m_bitboard); }
	inline BitBoard operator|(BitBoard const& other) { return BitBoard(m_bitboard | other.m_bitboard); }
	inline BitBoard operator^(BitBoard const& other) { return BitBoard(m_bitboard ^ other.m_bitboard); }
	inline BitBoard operator~() { return BitBoard(~m_bitboard); }
	inline BitBoard operator<<(BitBoard const& other) { return BitBoard(m_bitboard << other.m_bitboard); }
	inline BitBoard operator>>(BitBoard const& other) { return BitBoard(m_bitboard >> other.m_bitboard); }

	friend std::ostream& operator<<(std::ostream& os, BitBoard const& node);
};