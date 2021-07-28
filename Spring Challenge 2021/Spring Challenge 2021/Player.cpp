#include "Player.h"
#include "MiniMax.h"
#include "Timer.h"
#include "Utility.h"


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
