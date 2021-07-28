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
class Uncopyable
{
protected:
	Uncopyable() {}
	~Uncopyable() {}

	// Prevent any class inheriting it from being copied.
	Uncopyable(Uncopyable const&) = delete;
	Uncopyable& operator=(Uncopyable const&) = delete;
};
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

class Player : public Uncopyable
{
public:

    void set_player_info();
    void set_trees_info(Tree* tree);

    void output();

    int get_sun_income();                     // todo:: consider sun position. 

private:

    std::vector<Tree*>::iterator get_most_valuable(std::vector<Tree*>& tree_vector);
    void seed(std::vector<Tree*>& tree_vector);
    void clean_tree_vectors();

    int m_sun;                                 // your sun points
    int m_score;                               // your current score
    
    std::vector<Tree*> m_large_trees;          // Size 3 trees.
    std::vector<Tree*> m_large_dormant_trees;  // Size 3 dormant trees.
    
    std::vector<Tree*> m_medium_trees;         // Size 2 trees.
    std::vector<Tree*> m_medium_dormant_trees; // Size 2 dormant trees.

    std::vector<Tree*> m_small_trees;          // Size 1 trees.
    std::vector<Tree*> m_small_dormant_trees;  // Size 1 dormant trees.
       
    std::vector<Tree*> m_seeds;                // Size 0 trees.
    std::vector<Tree*> m_seeds_dormant;        // Size 0 dormant trees.
};
#include <list>
#include <vector>
#include <iostream>
#include <string>


enum Action
{
    ACT_WAIT = 1 << 0,
    ACT_SEED_SMALL = 1 << 1,                                            // Seed From small tree.
    ACT_SEED_MEDIUM = 1 << 2,                                           // Seed From medium tree.
    ACT_SEED_LARGE = 1 << 3,                                            // Seed From large tree.
    ACT_GROWTOSMALL = 1 << 4,
    ACT_GROWTOMEDIUM = 1 << 5,
    ACT_GROWTOLARGE = 1 << 6,
    ACT_COMPLETE = 1 << 7,
};

struct ActionNode
{
    ActionNode(int sun_income, int sun_points, int seeds_count, int stree_count, int mtree_count, int ltree_count,
        int seeds_available_count, int stree_available_count, int mtree_available_count, int ltree_available_count);
    ActionNode(ActionNode const* const parent, Action action);

    ActionNode(ActionNode const& other) = default;
    ActionNode& operator=(ActionNode const& other) = default;

    ActionNode(ActionNode&& other);
    //ActionNode& operator=(ActionNode const&& other);

    ~ActionNode();

    friend bool operator ==(ActionNode const& rhs, ActionNode const& lhs);
    friend bool operator >(ActionNode const& rhs, ActionNode const& lhs);
    friend bool operator <(ActionNode const& rhs, ActionNode const& lhs);
    friend bool operator >=(ActionNode const& rhs, ActionNode const& lhs);
    friend bool operator <=(ActionNode const& rhs, ActionNode const& lhs);

    friend std::ostream& operator<<(std::ostream& os, ActionNode const& node);
    static std::string get_action_string(Action action);
    void print_tree();

    int get_depth();
    bool is_valid();

    Action m_action;                                                    // Previous action.
    int m_sun_income;
    int m_sun_points;

    int m_seeds_count;                                                  // Amount of seeds.
    int m_stree_count;                                                  // Amount of small trees.
    int m_mtree_count;                                                  // Amount of medium trees.
    int m_ltree_count;                                                  // Amount of large trees.

    int m_seeds_available_count;                                        // Amount of seeds.
    int m_stree_available_count;                                        // Amount of small trees.
    int m_mtree_available_count;                                        // Amount of medium trees.
    int m_ltree_available_count;                                        // Amount of large trees.

    ActionNode const* const m_parent;
    std::list<ActionNode*> m_childs;

private: void print_tree_helper(std::string& tree_string, std::string prefix, ActionNode const& node, bool is_last, int& numer_of_lines);
};

//class ActionTree
//{
//
//};

class MiniMax : public Uncopyable
{
public:
    MiniMax(int sun_income, int sun_points, int seeds_count, int stree_count, int mtree_count, int ltree_count,
        int seeds_available_count, int stree_available_count, int mtree_available_count, int ltree_available_count);

    ~MiniMax();

    void construct_tree();
    Action choose_action();                                                 // must be called after construct_tree.

private:
    Action early_choose_seed(ActionNode* node);
    void generate_childs(ActionNode* current, std::vector<Action>const& possible_actions, int depth = 0);
    ActionNode* get_best_child(ActionNode* node);

    ActionNode* m_root;
    int number_of_nodes = 0;                                                // Debug                                                
    //int debug_helper = 1;                                                   // Debug
    //int real_depth = 0;
};
#include <algorithm>

template<class T>
struct delete_ptr // Helper function to ease cleanup of container
{
    void operator () (T p)
    {
        delete p;
    }
};

template <class T>
void delete_all(T& container)
{
    typedef typename T::value_type value_type;
    std::for_each(container.begin(), container.end(), delete_ptr<value_type>());
    container.clear();
}

auto delete_nodes = delete_all<std::list<ActionNode*>>;

bool operator==(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs.m_sun_income == lhs.m_sun_income && rhs.m_sun_income == lhs.m_sun_points) ? true : false;
}

bool operator>(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs.m_sun_income > lhs.m_sun_income 
		|| (rhs.m_sun_income == lhs.m_sun_income && rhs.m_sun_points > lhs.m_sun_points) 
		|| (rhs.m_sun_income == lhs.m_sun_income && rhs.m_sun_points == lhs.m_sun_points 
			&& rhs.m_action > lhs.m_action)) ? true : false;
}

bool operator<(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs > lhs || rhs == lhs) ? false : true;
}

bool operator>=(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs < lhs) ? false : true;
}

bool operator<=(ActionNode const& rhs, ActionNode const& lhs)
{
	return (rhs > lhs) ? false : true;
}

std::ostream& operator<<(std::ostream& os, ActionNode const& node)
{
	os << "Node" << std::endl;
	os << "Action: " << ActionNode::get_action_string(node.m_action) << std::endl;
	os << "Income: " << node.m_sun_income << std::endl;
	os << "Sun Points: " << node.m_sun_points << std::endl;

	return os;
}

ActionNode::ActionNode(int sun_income, int sun_points, int seeds_count, int stree_count, int mtree_count, int ltree_count,
	int seeds_available_count, int stree_available_count, int mtree_available_count, int ltree_available_count)
: m_action(ACT_WAIT)
, m_sun_income(sun_income)
, m_sun_points(sun_points)
, m_seeds_count(seeds_count)
, m_stree_count(stree_count)
, m_mtree_count(mtree_count)
, m_ltree_count(ltree_count)
, m_seeds_available_count(seeds_available_count)
, m_stree_available_count(stree_available_count)
, m_mtree_available_count(mtree_available_count)
, m_ltree_available_count(ltree_available_count)
, m_parent(nullptr)
{
}

ActionNode::ActionNode(ActionNode const* const parent, Action action)
	: m_action(action)
	, m_sun_income(parent->m_sun_income)
	, m_sun_points(parent->m_sun_points)
	, m_seeds_count(parent->m_seeds_count)
	, m_stree_count(parent->m_stree_count)
	, m_mtree_count(parent->m_mtree_count)
	, m_ltree_count(parent->m_ltree_count)
	, m_seeds_available_count(parent->m_seeds_available_count)
	, m_stree_available_count(parent->m_stree_available_count)
	, m_mtree_available_count(parent->m_mtree_available_count)
	, m_ltree_available_count(parent->m_ltree_available_count)
	, m_parent(parent)
{
	switch (action)
	{
	case ACT_SEED_SMALL:
		m_sun_points -= m_seeds_count;
		m_stree_available_count--;
		m_seeds_count++;
		break;
	case ACT_SEED_MEDIUM:
		m_sun_points -= m_seeds_count;
		m_mtree_available_count--;
		m_seeds_count++;
		break;
	case ACT_SEED_LARGE:
		m_sun_points -= m_seeds_count;
		m_ltree_available_count--;
		m_seeds_count++;
		break;
	case ACT_GROWTOSMALL:
		m_sun_points -= 1 + m_stree_count;
		m_seeds_count--;
		m_seeds_available_count--;
		m_stree_count++;
		m_sun_income++;
		break;
	case ACT_GROWTOMEDIUM:
		m_sun_points -= 3 + m_mtree_count;
		m_stree_count--;
		m_stree_available_count--;
		m_mtree_count++;
		m_sun_income++;
		break;
	case ACT_GROWTOLARGE:
		m_sun_points -= 7 + m_ltree_count;
		m_mtree_count--;
		m_mtree_available_count--;
		m_ltree_count++;
		m_sun_income++;
		break;
	case ACT_COMPLETE:
		m_sun_points -= 4;
		m_ltree_count--;
		m_ltree_available_count--;
		m_sun_income--;
		break;
	case ACT_WAIT:
		m_sun_points += m_sun_income;
		m_seeds_available_count = m_seeds_count;
		m_stree_available_count = m_stree_count;
		m_mtree_available_count = m_mtree_count;
		m_ltree_available_count = m_ltree_count;
		break;

	default:
		std::cerr << "This action doesn't exist." << std::endl;
		exit(EXIT_FAILURE);
		break;
	}
}

ActionNode::ActionNode(ActionNode&& other)
: m_action(other.m_action)
, m_sun_income(other.m_sun_income)
, m_sun_points(other.m_sun_points)
, m_seeds_count(other.m_seeds_count)
, m_stree_count(other.m_stree_count)
, m_mtree_count(other.m_mtree_count)
, m_ltree_count(other.m_ltree_count)
, m_seeds_available_count(other.m_seeds_available_count)
, m_stree_available_count(other.m_stree_available_count)
, m_mtree_available_count(other.m_mtree_available_count)
, m_ltree_available_count(other.m_ltree_available_count)
, m_parent(other.m_parent)
, m_childs(std::move(other.m_childs))
{

}

ActionNode::~ActionNode()
{
	delete_nodes(m_childs);
}

std::string ActionNode::get_action_string(Action action)
{
	std::string action_str;
	switch (action)
	{
	case ACT_SEED_SMALL:
		action_str = "stree - seed";
		break;
	case ACT_SEED_MEDIUM:
		action_str = "mtree - seed";
		break;
	case ACT_SEED_LARGE:
		action_str = "ltree - seed";
		break;
	case ACT_GROWTOSMALL:
		action_str = "grows";
		break;
	case ACT_GROWTOMEDIUM:
		action_str = "growm";
		break;
	case ACT_GROWTOLARGE:
		action_str = "growl";
		break;
	case ACT_COMPLETE:
		action_str = "complete";
		break;
	case ACT_WAIT:
		action_str = "wait";
		break;
	default:
		std::cerr << "This action doesn't exist." << std::endl;
		exit(EXIT_FAILURE);
		break;
	}
	return action_str;
}

void ActionNode::print_tree()
{
	std::cerr << "Node depth:" << get_depth() << std::endl;
	std::string tree_string;
	int number_of_lines = 0;
	print_tree_helper(tree_string, "", *this, true, number_of_lines);
	std::cerr << tree_string << std::endl;
}

void ActionNode::print_tree_helper(std::string& tree_string, std::string prefix, ActionNode const& node, bool is_last, int& numer_of_lines)
{
	constexpr int max_lines = 50;
	if (numer_of_lines > 50)
	{
		return;
	}
	numer_of_lines++;

	tree_string += prefix;
	
	tree_string += (is_last ? "|___" : "|---");

	tree_string += get_action_string(node.m_action) + " " + std::to_string(node.m_sun_income) + " " + std::to_string(node.m_sun_points) + "\n";

	int i = 0;
	for (auto begin = node.m_childs.begin(), end = node.m_childs.end(); begin != end; ++begin)
	{
		auto aux_it = begin;
		print_tree_helper(tree_string, prefix + (is_last ? "    " : "|   "), *(*begin), (++aux_it == end), numer_of_lines);
	}
}

int ActionNode::get_depth()
{
	int depth = 0;
	for (auto aux_node : m_childs)
	{
		int aux_depth = 0;
		aux_depth = aux_node->get_depth();
		aux_depth++;
		if (aux_depth > depth)
			depth = aux_depth;
	}
	return depth;
}

bool ActionNode::is_valid()
{
	return (m_sun_income >= 0
		&& m_sun_points >= 0
		&& m_seeds_available_count >= 0
		&& m_seeds_count <= 2							// Todo: get a better rule here.
		&& m_stree_available_count >= 0
		&& m_mtree_available_count >= 0
		&& m_ltree_available_count >= 0) ? true : false;
}

MiniMax::MiniMax(int sun_income, int sun_points, int seeds_count, int stree_count, int mtree_count, int ltree_count,
	int seeds_available_count, int stree_available_count, int mtree_available_count, int ltree_available_count)
:m_root(new ActionNode(sun_income, sun_points, seeds_count, stree_count, mtree_count, ltree_count,
	seeds_available_count, stree_available_count, mtree_available_count, ltree_available_count))
{
}

MiniMax::~MiniMax()
{
	delete m_root;
}

Action MiniMax::early_choose_seed(ActionNode* node)
{
	//if (node == nullptr)
	//{
	//	std::cerr << "Node doesnt exit" << std::endl;
	//	exit(EXIT_FAILURE);
	//}

	if (node->m_ltree_available_count)
		return ACT_SEED_LARGE;
	else if (node->m_mtree_available_count)
		return ACT_SEED_MEDIUM;
	else
		return ACT_SEED_SMALL;
}

void MiniMax::generate_childs(ActionNode* node, std::vector<Action>const& possible_actions, int depth)
{
	constexpr int SEEDS_ACTION = (ACT_SEED_SMALL | ACT_SEED_MEDIUM | ACT_SEED_LARGE);

	if (depth == 1)
		return;

	for (auto it = possible_actions.begin(), end = possible_actions.end(); it != end; ++it)
	{
		ActionNode* child;
		
		if (*it == ACT_SEED_SMALL)
		{
			child = new ActionNode(node, early_choose_seed(node));
			it += 2;
		}
		else
		{
			child = new ActionNode(node, *it);
		}
		
		if (!child->is_valid())		// Delete if its not a valid action
		{
			delete child;
			continue;
		}
		else
		{
			number_of_nodes++;
		
			//if (number_of_nodes > 2000 * debug_helper)
			//{
			//	std::cerr << "depth: " << m_root.get_depth() << std::endl;
			//	debug_helper++;
			//}
			//std::cerr << "depth " << depth << std::endl;
			//std::cerr << child << std::endl;
			if (*it == ACT_WAIT)
				generate_childs(child, possible_actions, depth + 1);
			else
				generate_childs(child, possible_actions, depth);
			node->m_childs.push_back(child);
		}
	}
}

void MiniMax::construct_tree()
{
	std::vector<Action>vec_possible_actions;
	if (Florest::get_instance()->get_day() < 17)
	{
		vec_possible_actions.insert(vec_possible_actions.end(), 
			{ ACT_WAIT
			, ACT_SEED_SMALL
			, ACT_SEED_MEDIUM
			, ACT_SEED_LARGE
			, ACT_GROWTOSMALL
			, ACT_GROWTOMEDIUM
			, ACT_GROWTOLARGE});
	}
	else
	{
		vec_possible_actions.insert(vec_possible_actions.end(),
			{ ACT_WAIT
			, ACT_GROWTOSMALL
			, ACT_GROWTOMEDIUM
			, ACT_GROWTOLARGE
			, ACT_COMPLETE });
	}
	generate_childs(m_root, vec_possible_actions, 0);
	std::cerr << "Number of nodes: " << number_of_nodes << std::endl;
	//m_root->print_tree();														
}

ActionNode* MiniMax::get_best_child(ActionNode* node)
{
	ActionNode* best_child = nullptr;

	for (auto aux_node : node->m_childs)
	{
		{
			ActionNode* aux_best_child = get_best_child(aux_node);
			if (aux_best_child != nullptr)
			{
				aux_node->m_sun_points = aux_best_child->m_sun_points;
				aux_node->m_sun_income = aux_best_child->m_sun_income;
			}
		}

		if (best_child == nullptr)
			best_child = aux_node;
		else
		{
			if (*aux_node > *best_child)
				best_child = aux_node;
		}
	}
	return best_child;
}

Action MiniMax::choose_action()
{																// Debug
	ActionNode* best_child = get_best_child(m_root);
	//std::cerr << ActionNode::get_action_string(best_child->m_action) << std::endl;			// Debug
	return best_child->m_action;
}
#include <chrono>

class Timer
{
public:
	Timer() = default;

	void start();
	void stop();
	void split();

private:

	std::chrono::steady_clock::time_point begin;
};
#include <iostream>


void Timer::start()
{
	begin = std::chrono::steady_clock::now();
}

void Timer::stop()
{
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "us" << std::endl; 
}

void Timer::split()
{
	stop();
}


auto delete_trees = delete_all<std::vector<Tree*>>;

void Player::set_player_info()
{
    std::cin >> m_sun
        >> m_score;
    std::cin.ignore();
}

void Player::set_trees_info(Tree* tree)
{
    if (tree->m_isDormant == 0)
    {
        switch (tree->m_size)
        {
        case 0:
            m_seeds.push_back(tree);
            break;

        case 1:
            m_small_trees.push_back(tree);
            break;

        case 2:
            m_medium_trees.push_back(tree);
            break;

        case 3:
            m_large_trees.push_back(tree);
            break;

        default:
            std::cerr << "Not valid tree size" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        switch (tree->m_size)
        {
        case 0:
            m_seeds_dormant.push_back(tree);
            break;

        case 1:
            m_small_dormant_trees.push_back(tree);
            break;

        case 2:
            m_medium_dormant_trees.push_back(tree);
            break;

        case 3:
            m_large_dormant_trees.push_back(tree);
            break;

        default:
            std::cerr << "Not valid tree size" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void Player::output()
{
    MiniMax minimax(get_sun_income(), m_sun, m_seeds.size() + m_seeds_dormant.size(),
        m_small_trees.size() + m_small_dormant_trees.size(), m_medium_trees.size() + m_medium_dormant_trees.size(), 
        m_large_trees.size() + m_large_dormant_trees.size(), m_seeds.size(), m_small_trees.size(),
        m_medium_trees.size(), m_large_trees.size());

    Timer time;
    time.start();
    minimax.construct_tree();
    std::cerr << "Time to construct tree: ";
    time.stop();
    time.start();
    Action action = minimax.choose_action();
    std::cerr << "Time to choose action: ";
    time.stop();

    switch (action)
    {
    case ACT_SEED_SMALL:
    {
        seed(m_small_trees);
        break;
    }
    case ACT_SEED_MEDIUM:
    {
        seed(m_medium_trees);
        break;
    }
    case ACT_SEED_LARGE:
    {
        seed(m_large_trees);
        break;
    }
    case ACT_GROWTOSMALL:
    {
        Tree* tree = *get_most_valuable(m_seeds);
        std::cout << "GROW " << tree->m_cell_index << std::endl;
        break;
    }
    case ACT_GROWTOMEDIUM:
    {
        Tree const* tree = *get_most_valuable(m_small_trees);
        std::cout << "GROW " << tree->m_cell_index << std::endl;
        break;
    }
    case ACT_GROWTOLARGE:
    {
        Tree const* tree = *get_most_valuable(m_medium_trees);
        std::cout << "GROW " << tree->m_cell_index << std::endl;
        break;
    }
    case ACT_COMPLETE:
    {
        Tree const* tree = *get_most_valuable(m_large_trees);
        std::cout << "COMPLETE " << tree->m_cell_index << std::endl;
        break;
    }
    case ACT_WAIT:
    {
        std::cout << "WAIT" << std::endl;
        break;
    }
    }

    clean_tree_vectors();                                               // Free trees.
}

int Player::get_sun_income()
{
    return 3 * (m_large_trees.size() + m_large_dormant_trees.size())
        +  2 * (m_medium_trees.size() + m_medium_dormant_trees.size())
        +  1 * (m_small_trees.size() + m_small_dormant_trees.size());
}

std::vector<Tree*>::iterator Player::get_most_valuable(std::vector<Tree*>& tree_vector)
{
    if (tree_vector.empty())
    {
        std::cerr << "There isnt any tree of this type available" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<Tree*>::iterator most_valuable = tree_vector.begin();
    Cell most_valuable_cell = Florest::get_instance()->get_cell((*most_valuable)->m_cell_index);

    if (most_valuable_cell.m_richness == 3)
        return most_valuable;

    for (auto& aux : tree_vector)
    {
        Cell const& aux_cell = Florest::get_instance()->get_cell(aux->m_cell_index);

        if (aux_cell.m_richness > most_valuable_cell.m_richness)
        {
            *most_valuable = aux;
            most_valuable_cell = aux_cell;
            if (most_valuable_cell.m_richness == 3)
                return most_valuable;
        }
    }
    return most_valuable;
}

void Player::seed(std::vector<Tree*>& tree_vector)
{
    while (!tree_vector.empty())
    {
        std::vector<Tree*>::iterator tree = get_most_valuable(tree_vector); // todo: improve this search.
        int cell_index = Florest::get_instance()->get_best_neighbor_cell((*tree)->m_size, (*tree)->m_cell_index);
        if (cell_index != -1) // todo: Improve this solution.
        {
            std::cout << "SEED " << (*tree)->m_cell_index << " " << cell_index << std::endl;
            break;
        }

        // Remove element from tree.
        delete* tree;
        tree_vector.erase(tree);
    }
    // If there isnt any possible spot to be seeded.
    if (tree_vector.empty())
        std::cout << "WAIT" << std::endl;
}

void Player::clean_tree_vectors()
{
    delete_trees(m_seeds);
    delete_trees(m_seeds_dormant);

    delete_trees(m_small_trees);
    delete_trees(m_small_dormant_trees);

    delete_trees(m_medium_trees);
    delete_trees(m_medium_dormant_trees);

    delete_trees(m_large_trees);
    delete_trees(m_large_dormant_trees);
}


int main()
{
    Florest* florest = Florest::get_instance();
    florest->set_cells_info();

    Player player1, player2;

    // game loop
    while (1)
    {
        florest->set_florest_info();

        Timer game_loop_timer;
        game_loop_timer.start();

        player1.set_player_info();

        int oppSun;                                     // opponent's sun points
        int oppScore;                                   // opponent's score
        bool oppIsWaiting;                              // whether your opponent is asleep until the next day
        std::cin >> oppSun
            >> oppScore
            >> oppIsWaiting;
        std::cin.ignore();

        int numberOfTrees;                              // the current amount of trees
        std::cin >> numberOfTrees;
        std::cin.ignore();

        for (int i = 0; i < numberOfTrees; i++)
        {
            Tree* tree = new Tree;
            tree->get_tree_info();
            
            florest->set_cell_owner(tree);
            if (tree->m_owner == 1)
                player1.set_trees_info(tree);
        }

        florest->set_bitboards();
        //Florest::get_instance()->debug_cells();

        int numberOfPossibleMoves;
        std::cin >> numberOfPossibleMoves;
        std::cin.ignore();

        for (int i = 0; i < numberOfPossibleMoves; i++)
        {
            std::string possibleMove;
            getline(std::cin, possibleMove);
        }

        
        player1.output();

        Florest::get_instance()->reset_cell_owner(); // reset ownership of all cells.

        std::cerr << "Time for one round:";
        game_loop_timer.stop();
    }
}