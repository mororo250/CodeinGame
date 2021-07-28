#pragma once

#include "Cell_Tree.h"
#include "Uncopyable.h"
#include "BitBoard.h"

class Florest : public Uncopyable
{
private:
    Florest() = default;

    static Florest* s_florest;

public:

    static Florest* get_instance();

    void set_cells_info();
    int get_best_neighbor_cell(int max_distance, int cell_index);
    inline Cell get_cell(int index) { return m_cells[index]; }

    void set_cell_owner(Tree const* const tree);
    void reset_cell_owner();                                     // reset ownership at the end of the turn.
    
    void set_florest_info();
    inline int get_day() { return m_day; }
    inline int get_nutrients() { return m_nutrients; }

    void set_bitboards();                                               // After set_cell_owner.

    void debug_cells();
private:

    std::vector<Cell> m_cells;                                          // todo: change to binary tree.
    int m_day;
    int m_nutrients;

    BitBoard m_board;
    BitBoard m_board_orange;
    BitBoard m_board_green;
    BitBoard m_board_yellow;

    BitBoard m_stree_shadow_NE;
    BitBoard m_stree_shadow_E;
    BitBoard m_stree_shadow_SE;
    BitBoard m_stree_shadow_SW;
    BitBoard m_stree_shadow_W;
    BitBoard m_stree_shadow_NW;

    BitBoard m_mtree_shadow_NE;
    BitBoard m_mtree_shadow_E;
    BitBoard m_mtree_shadow_SE;
    BitBoard m_mtree_shadow_SW;
    BitBoard m_mtree_shadow_W;
    BitBoard m_mtree_shadow_NW;

    BitBoard m_ltree_shadow_NE;
    BitBoard m_ltree_shadow_E;
    BitBoard m_ltree_shadow_SE;
    BitBoard m_ltree_shadow_SW;
    BitBoard m_ltree_shadow_W;
    BitBoard m_ltree_shadow_NW;

    BitBoard m_player1;
    BitBoard m_player1_seeds;
    BitBoard m_player1_stree;
    BitBoard m_player1_mtree;
    BitBoard m_player1_ltree;
    BitBoard m_player2;
    BitBoard m_player2_seeds;
    BitBoard m_player2_stree;
    BitBoard m_player2_mtree;
    BitBoard m_player2_ltree;

    BitBoard m_empty;
    BitBoard m_seeds;
    BitBoard m_stree;
    BitBoard m_mtree;
    BitBoard m_ltree;
};