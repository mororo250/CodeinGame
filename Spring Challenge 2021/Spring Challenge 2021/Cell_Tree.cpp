#include "Cell_Tree.h"

Cell& Cell::operator=(Cell const& lhs)
{
    m_index     = lhs.m_index;
    m_richness  = lhs.m_richness;
    m_neighbors = lhs.m_neighbors;
    m_owner = lhs.m_owner;

    return *this;
}

void Cell::get_cell_info(int const index)
{
    m_index = index;
    m_neighbors.assign(6, -1);
    std::cin >> m_richness
        >> m_neighbors[0]
        >> m_neighbors[1]
        >> m_neighbors[2]
        >> m_neighbors[3]
        >> m_neighbors[4]
        >> m_neighbors[5];
    std::cin.ignore();

    m_owner = 0;
}

Tree& Tree::operator=(Tree const& lhs)
{
    m_cell_index = lhs.m_cell_index;
    m_size       = lhs.m_size;
    m_owner      = lhs.m_owner;
    m_isDormant  = lhs.m_isDormant;

    return *this;
}

void Tree::get_tree_info()
{
    std::cin >> m_cell_index
        >> m_size
        >> m_owner
        >> m_isDormant;
    std::cin.ignore();
}

bool operator==(Cell const& rhs, Cell const& lhs)
{
    return (rhs.m_index == lhs.m_index) ? true : false;
}

std::ostream& operator<<(std::ostream& os, Cell const& cell)
{
    os << "Cell " << cell.m_index << std::endl;
    os << "Richness " << cell.m_richness << std::endl;
    os << "Owner " << cell.m_owner << std::endl;

    return os;
}

bool operator==(Tree const& rhs, Tree const& lhs)
{
    return (rhs.m_cell_index == lhs.m_cell_index) ? true : false;
}
