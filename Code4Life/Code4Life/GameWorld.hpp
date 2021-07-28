#pragma once

#include "Project.hpp"
#include "Robot.hpp"

#include "ModuleDiagnosis.hpp"
#include "ModuleMolecules.hpp"
#include "ModuleLaboratory.hpp"
#include "ModuleSample.hpp"

class GameWorld
{
private:
    GameWorld() = default;

    static GameWorld* s_game_world;

public:

    GameWorld(GameWorld const& other) = delete;
    GameWorld& operator=(GameWorld const& other) = delete;

    static GameWorld* get_instance();

    void get_projects_info();
    void update_world();

    unsigned int get_round() { return m_round_number; }
    unsigned int get_round_to_end() { return 200 - m_round_number + 1; }

private:

    std::vector<Project>    m_projects;
    int                     m_project_count;
    
    std::vector<Robot>      m_robots = { Robot("Player1"), Robot("Player2") };

    unsigned int            m_round_number = 0;
};
