#include "Florest.h"

Florest* Florest::s_florest = nullptr;

Florest* Florest::get_instance()
{
    if (s_florest == nullptr)
        s_florest = new Florest();

    return s_florest;
}
void Florest::set_cells_info()
{
    int numberOfCells; // 37
    std::cin >> numberOfCells;
    std::cin.ignore();

    m_cells.assign(numberOfCells, Cell());

    for (int i = 0; i < numberOfCells; i++)
    {
        int index;
        std::cin >> index;
        m_cells[index].get_cell_info(index);

        switch (m_cells[index].m_richness)
        {
        case 1:
            m_board_orange |= BitBoard::CELLS[i];
            break;
        case 2:
            m_board_yellow |= BitBoard::CELLS[i];
            break;
        case 3:
            m_board_green |= BitBoard::CELLS[i];
            break;
        }
    }
    m_board = m_board_orange | m_board_yellow | m_board_green;
}

int Florest::get_best_neighbor_cell(int max_distance, int cell_index)
{
    // The best cell is the one closer to the center.
    int best_neighbor = -1;
    for (int i = 0; i < max_distance; i++)
    {
        for (int& index : m_cells[cell_index].m_neighbors)
        {
            if (index >= 0 && (best_neighbor == -1 || best_neighbor > index))
            {
                if (m_cells[index].m_owner == 0 && m_cells[index].m_richness > 0)        // Check if cell is available.
                    best_neighbor = index;
            }
        }
        cell_index = best_neighbor;
    }
    return cell_index;
}

void Florest::set_cell_owner(Tree const* const tree)
{
    if (tree->m_owner)
    {
        switch (tree->m_size)
        {
        case 0:
            m_player1_seeds |= BitBoard::CELLS[tree->m_cell_index];
            break;
        case 1:
            m_player1_stree |= BitBoard::CELLS[tree->m_cell_index];
            break;
        case 2:
            m_player1_mtree |= BitBoard::CELLS[tree->m_cell_index];
            break;
        case 3:
            m_player1_ltree |= BitBoard::CELLS[tree->m_cell_index];
            break;
        }
    }
    else
    {
        switch (tree->m_size)
        {
        case 0:
            m_player2_seeds |= BitBoard::CELLS[tree->m_cell_index];
            break;
        case 1:
            m_player2_stree |= BitBoard::CELLS[tree->m_cell_index];
            break;
        case 2:
            m_player2_mtree |= BitBoard::CELLS[tree->m_cell_index];
            break;
        case 3:
            m_player2_ltree |= BitBoard::CELLS[tree->m_cell_index];
            break;
        }
    }
}

void Florest::reset_cell_owner()
{
    m_player1_seeds = BitBoard::ZERO;
    m_player1_stree = BitBoard::ZERO;
    m_player1_mtree = BitBoard::ZERO;
    m_player1_ltree = BitBoard::ZERO;

    m_player2_seeds = BitBoard::ZERO;
    m_player2_stree = BitBoard::ZERO;
    m_player2_mtree = BitBoard::ZERO;
    m_player2_ltree = BitBoard::ZERO;

    for (auto& aux : m_cells) 
        aux.m_owner = 0;


}

void Florest::set_florest_info()
{
    int day;                                        // the game lasts 24 days: 0-23
    std::cin >> day;
    std::cin.ignore();

    int nutrients;                                  // the base score you gain from the next COMPLETE action
    std::cin >> nutrients;
    std::cin.ignore();
}

void Florest::set_bitboards()
{
    m_player1 = m_player1_seeds | m_player1_stree | m_player1_mtree | m_player1_ltree;
    m_player2 = m_player2_seeds | m_player2_stree | m_player2_mtree | m_player2_ltree;

    m_empty = ~(m_player1 | m_player2);
    m_seeds = m_player1_seeds | m_player2_seeds;
    m_stree = m_player1_stree | m_player2_stree;
    m_mtree = m_player1_mtree | m_player2_mtree;
    m_ltree = m_player1_ltree | m_player2_ltree;

    m_ltree_shadow_NE = (m_ltree >> 3 * BitBoard::shiftNE) | (m_ltree >> 2 * BitBoard::shiftNE) | (m_ltree >>  BitBoard::shiftNE) & m_board;
    m_ltree_shadow_E = (m_ltree >> 3 * BitBoard::shiftE) | (m_ltree >> 2 * BitBoard::shiftE) | (m_ltree >> BitBoard::shiftE) & m_board;
    m_ltree_shadow_SE = (m_ltree >> 3 * BitBoard::shiftSE) | (m_ltree >> 2 * BitBoard::shiftSE) | (m_ltree >> BitBoard::shiftSE) & m_board;
    m_ltree_shadow_SW = (m_ltree >> 3 * BitBoard::shiftSW) | (m_ltree >> 2 * BitBoard::shiftSW) | (m_ltree >> BitBoard::shiftSW) & m_board;
    m_ltree_shadow_W = (m_ltree >> 3 * BitBoard::shiftW) | (m_ltree >> 2 * BitBoard::shiftW) | (m_ltree >> BitBoard::shiftW) & m_board;
    m_ltree_shadow_NW = (m_ltree >> 3 * BitBoard::shiftNW) | (m_ltree >> 2 * BitBoard::shiftNW) | (m_ltree >>  BitBoard::shiftNW) & m_board;

    m_mtree_shadow_NE = ((m_mtree >> 2 * BitBoard::shiftNE) | (m_mtree >> BitBoard::shiftNE) | m_ltree_shadow_NE) & m_board;
    m_mtree_shadow_E = ((m_mtree >> 2 * BitBoard::shiftE) | (m_mtree >> BitBoard::shiftE) | m_ltree_shadow_E) & m_board;
    m_mtree_shadow_SE = ((m_mtree >> 2 * BitBoard::shiftSE) | (m_mtree >> BitBoard::shiftSE) | m_ltree_shadow_SE) & m_board;
    m_mtree_shadow_SW = ((m_mtree >> 2 * BitBoard::shiftSW) | (m_mtree >> BitBoard::shiftSW) | m_ltree_shadow_SW) & m_board;
    m_mtree_shadow_W = ((m_mtree >> 2 * BitBoard::shiftW) | (m_mtree >> BitBoard::shiftW) | m_ltree_shadow_W) & m_board;
    m_mtree_shadow_NW = ((m_mtree >> 2 * BitBoard::shiftNW) | (m_mtree >> BitBoard::shiftNW) | m_ltree_shadow_NW) & m_board;

    m_stree_shadow_NE = ((m_stree >> BitBoard::shiftNE) | m_mtree_shadow_NE) & m_board;
    m_stree_shadow_E = ((m_stree >> BitBoard::shiftE)   | m_mtree_shadow_E) & m_board;
    m_stree_shadow_SE = ((m_stree >> BitBoard::shiftSE) | m_mtree_shadow_SE) & m_board;
    m_stree_shadow_W = ((m_stree >> BitBoard::shiftW)   | m_mtree_shadow_W) & m_board;
    m_stree_shadow_NW = ((m_stree >> BitBoard::shiftNW) | m_mtree_shadow_NW) & m_board;

    //std::cerr << m_stree_shadow_NE << std::endl;
    //std::cerr << m_mtree_shadow_NE << std::endl;
    //std::cerr << m_ltree_shadow_NE << std::endl;
    std::cerr << m_stree_shadow_E << std::endl;
    std::cerr << m_mtree_shadow_E << std::endl;
    std::cerr << m_ltree_shadow_E << std::endl;
    //std::cerr << m_stree_shadow_SE << std::endl;
    //std::cerr << m_stree_shadow_SW << std::endl;
    //std::cerr << m_stree_shadow_W << std::endl;
    //std::cerr << m_stree_shadow_NW << std::endl;
}

void Florest::debug_cells()
{
    for (auto& aux : m_cells)
        std::cerr << aux << std::endl;
}
