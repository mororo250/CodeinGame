#include "BitBoard.h"

#include <iostream>

std::vector<int_fast64_t> const BitBoard::CELLS =
{ 0b0000000000000000000000000000000000000001000000000000000000000000
, 0b0000000000000000000000000000000000000010000000000000000000000000
, 0b0000000000000000000000000000000000000000000001000000000000000000
, 0b0000000000000000000000000000000000000000000000100000000000000000
, 0b0000000000000000000000000000000000000000100000000000000000000000
, 0b0000000000000000000000000000000001000000000000000000000000000000
, 0b0000000000000000000000000000000010000000000000000000000000000000
, 0b0000000000000000000000000000000000000100000000000000000000000000
, 0b0000000000000000000000000000000000000000000010000000000000000000
, 0b0000000000000000000000000000000000000000000000000001000000000000
, 0b0000000000000000000000000000000000000000000000000000100000000000
, 0b0000000000000000000000000000000000000000000000000000010000000000
, 0b0000000000000000000000000000000000000000000000010000000000000000
, 0b0000000000000000000000000000000000000000010000000000000000000000
, 0b0000000000000000000000000000000000100000000000000000000000000000
, 0b0000000000000000000000000001000000000000000000000000000000000000
, 0b0000000000000000000000000010000000000000000000000000000000000000
, 0b0000000000000000000000000100000000000000000000000000000000000000
, 0b0000000000000000000000000000000100000000000000000000000000000000
, 0b0000000000000000000000000000000000001000000000000000000000000000
, 0b0000000000000000000000000000000000000000000100000000000000000000
, 0b0000000000000000000000000000000000000000000000000010000000000000
, 0b0000000000000000000000000000000000000000000000000000000001000000
, 0b0000000000000000000000000000000000000000000000000000000000100000
, 0b0000000000000000000000000000000000000000000000000000000000010000
, 0b0000000000000000000000000000000000000000000000000000000000001000
, 0b0000000000000000000000000000000000000000000000000000001000000000
, 0b0000000000000000000000000000000000000000000000001000000000000000
, 0b0000000000000000000000000000000000000000001000000000000000000000
, 0b0000000000000000000000000000000000010000000000000000000000000000
, 0b0000000000000000000000000000100000000000000000000000000000000000
, 0b0000000000000000000001000000000000000000000000000000000000000000
, 0b0000000000000000000010000000000000000000000000000000000000000000
, 0b0000000000000000000100000000000000000000000000000000000000000000
, 0b0000000000000000001000000000000000000000000000000000000000000000
, 0b0000000000000000000000001000000000000000000000000000000000000000
, 0b0000000000000000000000000000001000000000000000000000000000000000 };

std::ostream& operator<<(std::ostream& os, BitBoard const& bitboard)
{
    std::cerr << "   " << bool(bitboard.m_bitboard & BitBoard::CELLS[25])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[24])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[23])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[22]) << std::endl;
    std::cerr << "  " << bool(bitboard.m_bitboard & BitBoard::CELLS[26])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[11])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[10])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[9])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[21]) << std::endl;
    std::cerr << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[27])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[12])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[03])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[02])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[8])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[20]) << std::endl;
    std::cerr << bool(bitboard.m_bitboard & BitBoard::CELLS[28])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[13])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[04])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[00])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[01])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[7])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[19]) << std::endl;
    std::cerr << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[29])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[14])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[05])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[06])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[18])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[36]) << std::endl;
    std::cerr << "  " << bool(bitboard.m_bitboard & BitBoard::CELLS[30])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[15])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[16])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[17])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[35]) << std::endl;
    std::cerr << "   " << bool(bitboard.m_bitboard & BitBoard::CELLS[31])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[32])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[33])
        << " " << bool(bitboard.m_bitboard & BitBoard::CELLS[34]) << std::endl;

	return os;
}