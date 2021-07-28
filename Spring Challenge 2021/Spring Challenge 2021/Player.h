#pragma once

#include "Florest.h"

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