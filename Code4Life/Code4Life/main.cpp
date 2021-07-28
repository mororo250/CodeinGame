#include "Robot.hpp"
#include "GameWorld.hpp"

int main()
{
    // Initialize project
    GameWorld::get_instance()->get_projects_info();

    // game loop
    while (true)
        GameWorld::get_instance()->update_world();
}