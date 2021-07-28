#pragma once

#include <list>
#include <vector>
#include <iostream>
#include <string>

#include "Uncopyable.h"

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
