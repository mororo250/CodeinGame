#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

struct Cell
{
    Cell& operator = (Cell const& lhs);
    friend bool operator == (Cell const& rhs, Cell const& lhs);
    friend std::ostream& operator<<(std::ostream& os, Cell const& cell);

    void get_cell_info(int const index);

    int m_index;                                  // 0 is the center cell, the next BitBoard::CELLS spiral outwards
    int m_richness;                               // 0 if the cell is unusable, 1-3 for usable BitBoard::CELLS
    int m_owner = 0;                              // 0 if is empty, 1 is I am the owner 2 otherwise.
    std::vector<int> m_neighbors;
};

struct Tree
{
    Tree& operator = (Tree const& lhs);
    friend bool operator == (Tree const& rhs, Tree const& lhs);

    void get_tree_info();

    int m_cell_index;                             // location of this tree
    int m_size;                                   // size of this tree: 0-3
    bool m_owner;                                 // 1 if this is my tree
    bool m_isDormant;                             // 1 if this tree is dormant
};