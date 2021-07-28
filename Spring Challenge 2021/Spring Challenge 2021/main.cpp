#include "Player.h"
#include "Timer.h"


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
