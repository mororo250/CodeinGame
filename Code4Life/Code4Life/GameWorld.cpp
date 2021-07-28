#include "GameWorld.hpp"

GameWorld* GameWorld::s_game_world = nullptr;

GameWorld* GameWorld::get_instance()
{
    if (s_game_world == nullptr)
        s_game_world = new GameWorld();

    return s_game_world;
}

void GameWorld::get_projects_info()
{
    std::cin >> m_project_count;
    std::cin.ignore();

    m_projects.resize(m_project_count, Project());
    for (int i = 0; i < m_project_count; i++)
    {
        m_projects[i].get_info_project();
        std::cerr << m_projects[i] << std::endl;
    }
}

void GameWorld::update_world()
{
    for (Robot& robot : m_robots)
        robot.get_robot_info();

    ModuleMolecules* module_modlecules = ModuleMolecules::get_instance();
    module_modlecules->get_molecules_info();

    ModuleDiagnosis* module_diagnosis = ModuleDiagnosis::get_instance();
    module_diagnosis->get_diagnosis_info();

    m_round_number++; // Needs to go before run()

    m_robots[0].run();
}
