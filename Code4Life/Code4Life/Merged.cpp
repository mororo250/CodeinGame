#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <valarray>
#include <algorithm>

struct Sample
{
    // Assign constructor.
    Sample():cost(0, 5) {};

    Sample& operator = (Sample const& lhs);
    friend bool operator == (Sample const& rhs, Sample const& lhs);
    friend std::ostream& operator<<(std::ostream& os, Sample const& sample);

    void get_sample_info();

    int                 sampleId;
    int                 carriedBy;
    int                 rank;
    std::string         expertiseGain;
    int                 health;
    
    std::valarray<int>  cost;
};
Sample& Sample::operator=(Sample const& lhs)
{
    sampleId        = lhs.sampleId;
    carriedBy       = lhs.carriedBy;
    rank            = lhs.rank;
    expertiseGain   = lhs.expertiseGain;
    health          = lhs.health;
    cost            = lhs.cost;
    return *this;
}

bool operator == (Sample const& rhs, Sample const& lhs)
{
    if (rhs.sampleId == lhs.sampleId)
        return true;
    else
        return false;
}

std::ostream& operator<<(std::ostream& os, Sample const& sample)
{
    if (sample.health == -1)
        os << "State: Undiagnosed\n";
    else
        os << "State: Diagnosed\n";

    os << "Sample Id:" << sample.sampleId << "\n";
    if (sample.carriedBy == 0)
        os << "Carried by: Player1\n";
    else if (sample.carriedBy == 1)
        os << "Carried by: Player2\n";
    else
        os << "Carried by: Cloud\n";

    os << "rank: " << sample.rank << "\n";
    os << "expertise Gain: " << sample.expertiseGain << "\n";
    os << "health: " << sample.health << "\n";

    os << "costA: " << sample.cost[0] << "\n";
    os << "costB: " << sample.cost[1] << "\n";
    os << "costC: " << sample.cost[2] << "\n";
    os << "costD: " << sample.cost[3] << "\n";
    os << "costE: " << sample.cost[4] << "\n";

    return os;
}

void Sample::get_sample_info()
{
    std::cin    >> sampleId
                >> carriedBy
                >> rank
                >> expertiseGain
                >> health
                >> cost[0]
                >> cost[1]
                >> cost[2]
                >> cost[3]
                >> cost[4];
    std::cin.ignore();
}

class Robot
{
public:
    enum States
    {
        ST_IDLE = 0,
        ST_COLLECTSAMPLE = 1,       // Collect samples at Samples
        ST_ANALYZESAMPLE = 2,       // Analyze  data files at the DIAGNOSIS.
        ST_GATHERMOLECULES = 3,     // Gather required molecules at the MOLECULES.
        ST_PRODUCEMEDICINES = 4,    // produce the medicines at the LABORATORY.
        ST_MOVING = 5               // intermediate state.    
    };

    Robot(std::string const& name);

    // Recieves all the robot input information.
    void get_robot_info();
    void run();
    void set_state(States new_state);

    inline States get_current_state() { return m_current_state; }

    friend std::ostream& operator<<(std::ostream& os, Robot const& robot);

private:

    // Define the state machine state functions
    void st_idle();
    void st_collect_sample();
    void st_analyze_sample();
    void st_gather_molecule();
    void st_produce_medicne();
    void st_moving();

    int choose_rank();                                          // Choose rank of the sample to be collected.
    bool choose_molecule(std::valarray<int> const& needed, std::valarray<int> const& needed_total);
    void update_sample_cost();                                  // Update sample cost with current expertise.
    bool is_sample_free(Sample const& sample);                  // Check if updated sample cost is zero. Call it after update_sample_cost.
    bool is_sample_valid();                                     // Check if cost is too high.
    bool is_sample_valid(Sample& sample);                       // Override for single Sample.
    int get_sample_priority(Sample const& sample);              // Priority can be 0, 1 or 2.
    void move_to_ready(std::list<Sample>::iterator sample_it);
    void update_reserve(std::list<Sample>::iterator sample_it);

    States              m_current_state;
    States              m_next_state;

    std::list<Sample>   m_samples_undiagnosed;                  // Vector can't be a pointer because Module Diagnosis vector 
    std::list<Sample>   m_samples_diagnosed;
    std::list<Sample>   m_samples_ready;
    std::string         m_name;
    std::string         m_target;
    int                 m_eta;
    int                 m_score;
    
    std::valarray<int>    m_storage;
    std::valarray<int>    m_expertise;
    std::valarray<int>    m_reserved;
};
#include <tuple>

#include <iostream>

class Project
{
public:

    Project() = default;
    Project(Project const& other) = default;
    Project& operator=(Project const& other) = default;
    ~Project() = default;

    void get_info_project();

    friend std::ostream& operator<<(std::ostream& os, Project const& project);

private:

    int m_a;
    int m_b;
    int m_c;
    int m_d;
    int m_e;
};
void Project::get_info_project()
{
    std::cin >> m_a
        >> m_b
        >> m_c
        >> m_d
        >> m_e;
    std::cin.ignore();
}

std::ostream& operator<<(std::ostream& os, Project const& project)
{
    os << "Project info:\n";

    os << "Needed expertise A:" << project.m_a << "\n";
    os << "Needed expertise B:" << project.m_b << "\n";
    os << "Needed expertise C:" << project.m_c << "\n";
    os << "Needed expertise D:" << project.m_d << "\n";
    os << "Needed expertise E:" << project.m_e << "\n";

    return os;
}

class Module
{
public:

    Module() {}
    virtual ~Module() = default;

private:
};

class ModuleDiagnosis : public Module
{
private:

    ModuleDiagnosis() = default;

    static ModuleDiagnosis* s_module_diagnosis;

public:

    ModuleDiagnosis(ModuleDiagnosis const& other) = delete;
    ModuleDiagnosis& operator=(ModuleDiagnosis const& other) = delete;

    void get_diagnosis_info();
    inline int get_sample_count() const { return m_sample_count; }
    Sample& get_max_health_sample();

    void get_undiagnosed_samples(std::list<Sample>& samples, int const robot_id = 0); // Id player = 0 / other = 1
    //void get_cloud_sample(); //todo cloud samples
    void update_undiagnosed_samples(std::list<Sample>& samples, int const robot_id = 0);
    
    static ModuleDiagnosis* get_instance();

private:

    int m_sample_count;
    std::vector<Sample> m_samples;
};
ModuleDiagnosis* ModuleDiagnosis::s_module_diagnosis = nullptr;

void ModuleDiagnosis::get_diagnosis_info()
{
    std::cin >> m_sample_count;
    std::cin.ignore();

    m_samples.resize(m_sample_count, Sample());

    for (int i = 0; i < m_sample_count; i++)
    {
        m_samples[i].get_sample_info();
    }
}

ModuleDiagnosis* ModuleDiagnosis::get_instance()
{
    if (s_module_diagnosis == nullptr)
        s_module_diagnosis = new ModuleDiagnosis();

    return s_module_diagnosis;
}

Sample& ModuleDiagnosis::get_max_health_sample()
{
    int max_health = 0;
    int i = 0;

    for (i++; i < m_sample_count; i++)
    {
        if (m_samples[i].health > m_samples[max_health].health && m_samples[max_health].carriedBy == -1)
            max_health = i;
    }

    if (m_samples[max_health].carriedBy != 1)
    {
       return m_samples[max_health];
    }
}

void ModuleDiagnosis::get_undiagnosed_samples(std::list<Sample>& samples, int const robot_id)
{
    if (robot_id != 0 && robot_id != 1)
    {
        std::cerr << "Not valid Robot id" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (Sample& sample : m_samples)
    {
        if (sample.carriedBy == robot_id && sample.cost[0] == -1)
        {
            // Check if this sample is already being carried.
            if (std::find(samples.begin(), samples.end(), sample) == samples.end())
                samples.push_back(sample);
        }
    }
}

void ModuleDiagnosis::update_undiagnosed_samples(std::list<Sample>& samples, int const robot_id)
{
    if (robot_id != 0 && robot_id != 1)
    {
        std::cerr << "Not valid Robot id" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (Sample& sample : samples)
    {
        auto inter_sample = std::find(m_samples.begin(), m_samples.end(), sample);
        // Check if the sample exist.
        if (inter_sample != m_samples.end())
            sample = *inter_sample; // Update Sample
        else
        {
            std::cerr << "the sample: " << sample.sampleId << " Isn't available." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}
class ModuleMolecules : public Module
{
private:

    ModuleMolecules():m_available(0, 5) {};

    static ModuleMolecules* s_module_molecules;

public:

    ModuleMolecules(ModuleMolecules const& other) = delete;
    ModuleMolecules& operator=(ModuleMolecules const& other) = delete;

    void get_molecules_info();
    bool enough_molecules(std::valarray<int> const& needed) const;

    static ModuleMolecules* get_instance();
private:

    std::valarray<int> m_available;
};
ModuleMolecules* ModuleMolecules::s_module_molecules = nullptr;

ModuleMolecules* ModuleMolecules::get_instance()
{
    if (s_module_molecules == nullptr)
        s_module_molecules = new ModuleMolecules();

    return s_module_molecules;
}

void ModuleMolecules::get_molecules_info()
{
    std::cin    >> m_available[0]
                >> m_available[1]
                >> m_available[2]
                >> m_available[3]
                >> m_available[4];
    std::cin.ignore();
}

bool ModuleMolecules::enough_molecules(std::valarray<int> const& needed) const
{
    if ((needed <= m_available).min() == true)
    {
        return true;
    }
    else
        return false;
}
class ModuleLaboratory : public Module
{
private:

    ModuleLaboratory() = default;

    static ModuleLaboratory* s_module_laboratory;

public:

    ModuleLaboratory(ModuleLaboratory const& other) = delete;
    ModuleLaboratory& operator=(ModuleLaboratory const& other) = delete;

    static ModuleLaboratory* get_instance();
};
ModuleLaboratory* ModuleLaboratory::s_module_laboratory = nullptr;

ModuleLaboratory* ModuleLaboratory::get_instance()
{
    if (s_module_laboratory == nullptr)
        s_module_laboratory = new ModuleLaboratory();

    return s_module_laboratory;
}
class ModuleSamples : public Module
{
private:

    ModuleSamples() = default;

    static ModuleSamples* s_module_samples;

public:

    ModuleSamples(ModuleSamples const& other) = delete;
    ModuleSamples& operator=(ModuleSamples const& other) = delete;

    static ModuleSamples* get_instance();
};
ModuleSamples* ModuleSamples::s_module_samples = nullptr;

ModuleSamples* ModuleSamples::get_instance()
{
    if (s_module_samples == nullptr)
        s_module_samples = new ModuleSamples();

    return s_module_samples;
}

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

Robot::Robot(std::string const& name)
    : m_name(name)
    , m_current_state(ST_IDLE)
    , m_next_state(ST_MOVING)
    , m_storage(0, 5)
    , m_expertise(0, 5)
    , m_reserved(0, 5)
{
}

void Robot::get_robot_info()
{
    std::cin    >> m_target
                >> m_eta
                >> m_score
                >> m_storage[0]
                >> m_storage[1]
                >> m_storage[2]
                >> m_storage[3]
                >> m_storage[4]
                >> m_expertise[0]
                >> m_expertise[1]
                >> m_expertise[2]
                >> m_expertise[3]
                >> m_expertise[4];
    std::cin.ignore();
}

void Robot::run()
{
    switch (m_current_state)
    {
    case ST_IDLE:
        st_idle();
        break;
    case ST_COLLECTSAMPLE:
        st_collect_sample();
        break;
    case ST_ANALYZESAMPLE:
        st_analyze_sample();
        break;
    case ST_GATHERMOLECULES:
        st_gather_molecule();
        break;
    case ST_PRODUCEMEDICINES:
        st_produce_medicne();
        break;
    case ST_MOVING:
        st_moving();
        break;
    }
    //std::cerr << *this << std::endl;
}

void Robot::set_state(States new_state)
{
    switch (new_state)
    {
    case ST_COLLECTSAMPLE:
        std::cout << "GOTO SAMPLES" << std::endl;
        m_current_state = ST_MOVING;
        m_next_state = ST_COLLECTSAMPLE;
        break;
    case ST_ANALYZESAMPLE:
        std::cout << "GOTO DIAGNOSIS" << std::endl;
        m_current_state = ST_MOVING;
        m_next_state = ST_ANALYZESAMPLE;
        break;
    case ST_GATHERMOLECULES:
        std::cout << "GOTO MOLECULES" << std::endl;
        m_current_state = ST_MOVING;
        m_next_state = ST_GATHERMOLECULES;
        break;
    case ST_PRODUCEMEDICINES:
        std::cout << "GOTO LABORATORY" << std::endl;
        m_current_state = ST_MOVING;
        m_next_state = ST_PRODUCEMEDICINES;
        break;
    case ST_IDLE:
        std::cerr << "Robot shouldnt go back to start" << std::endl;
        exit(EXIT_FAILURE);
        break;
    case ST_MOVING:
        std::cerr << "Moving is not a valid state to be set" << std::endl;
        exit(EXIT_FAILURE);
        break;
    }
}

void Robot::st_idle()
{
    set_state(ST_COLLECTSAMPLE);
}

void Robot::st_collect_sample()
{
    constexpr int MINIMUM_ROUNDS_MOVIMENT = 3 + 4;          // How many rounds are necessary walking. Samples -> Diagnosis -> Laboratory.
    constexpr int MINIMUM_ROUNDS_TASKS = 3;                 // How many rounds are necessary doing tasks. Collect, analyse and produce Medicine

    static unsigned int s_collected = 0;

    int const rounds_to_end = GameWorld::get_instance()->get_round_to_end();
    int const number_available_slot = 3 - (m_samples_undiagnosed.size() + m_samples_diagnosed.size() + s_collected);
    
    int const total_rounds = MINIMUM_ROUNDS_MOVIMENT + MINIMUM_ROUNDS_TASKS +
        s_collected * (MINIMUM_ROUNDS_TASKS - 1) + m_samples_diagnosed.size();

    if (rounds_to_end < total_rounds || number_available_slot == 0)
    {
        set_state(ST_ANALYZESAMPLE);
        ModuleDiagnosis::get_instance()->get_undiagnosed_samples(m_samples_undiagnosed, 0);

        s_collected = 0;                                    // Reset collected.
        return;
    }
    else if (rounds_to_end == total_rounds)                 // Bet on free sample.
    {
        std::cout << "CONNECT " << 2 << std::endl;
        s_collected = 3;                                    // Go to diagnosis in the next round.
        return;
    }
    else if (rounds_to_end <= (total_rounds + 5))            // Bet on free sample.
    {
        std::cout << "CONNECT " << 2 << std::endl;
        s_collected++;
        return;
    }
    else if (number_available_slot > 0)                     // Normal Rounds.
    {
        int rank = choose_rank();
        std::cout << "CONNECT " << rank << std::endl;
        s_collected++;
        return;
    }
    else
    {
        std::cerr << "This shouldn't happen Problem with ST_COLLECT STATE" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Robot::st_analyze_sample() // remove code repetiton.
{
    constexpr int MINIMUM_ROUNDS_MOVIMENT = 4;              // How many rounds are necessary walking. Diagnosis -> Laboratory.
    constexpr int MINIMUM_ROUNDS_TASKS = 2;                 // How many rounds are necessary doing tasks. Analyse and produce Medicine

    int const rounds_to_end = GameWorld::get_instance()->get_round_to_end();
    int total_rounds = MINIMUM_ROUNDS_MOVIMENT + m_samples_diagnosed.size() + m_samples_ready.size();

    // todo check if there are any available sample in the cloud.
    std::cerr << "Total Rounds:" << total_rounds << std::endl;
    std::cerr << "rounds to end:" << rounds_to_end << std::endl;

    if (rounds_to_end <= total_rounds + 2)
    {
        update_sample_cost();

        total_rounds = MINIMUM_ROUNDS_MOVIMENT + m_samples_ready.size();
        if (total_rounds == rounds_to_end || m_samples_undiagnosed.empty())
        {
            set_state(ST_PRODUCEMEDICINES); // If there are two free samples go to laboratory.
            return;
        }
    }

    if (!m_samples_undiagnosed.empty())
    {
        // Sample& sample = ModuleDiagnosis::get_instance()->get_max_health_sample();
        Sample& sample = m_samples_undiagnosed.back();
        m_samples_undiagnosed.pop_back();

        std::cout << "CONNECT " << sample.sampleId << std::endl;
        m_samples_diagnosed.push_back(std::move(sample));
    }
    else
    {
        update_sample_cost();

        if (m_samples_ready.size() >= 2)
        {
            set_state(ST_PRODUCEMEDICINES); // If there are two free samples go to laboratory.
            return;
        }

        if (is_sample_valid())
        {
            set_state(ST_GATHERMOLECULES);
            return;
        }
    }
}

void Robot::st_gather_molecule()
{
    constexpr int ROUNDS_MOVIMENT = 3;              // How many rounds are necessary walking. Molecules -> Laboratory.
    int const rounds_to_end = GameWorld::get_instance()->get_round_to_end();

    // Loop is for rounds where there is just enough molecules for a sample.
    // Todo remove loop.
    while (true)
    {
        auto sample = m_samples_diagnosed.end();

        std::valarray<int> needed(0, 5);
        std::valarray<int> needed_total(0, 5);

        for (auto [sample_it, priority, total_needed] = std::tuple{ m_samples_diagnosed.begin(), -1, 0 }; sample_it != m_samples_diagnosed.end(); sample_it++)
        {
            int priority_temp = get_sample_priority(*sample_it);

            std::valarray<int> needed_temp = sample_it->cost - (m_storage - m_reserved);
            
            for (int& temp : needed_temp)
                temp = std::max(temp, 0);

            if (ModuleMolecules::get_instance()->enough_molecules(needed_temp) &&
                (m_storage.sum() + needed_temp.sum() < 10))
            {

                std::cerr << *this << std::endl;

                std::cerr << "Priority:" << priority_temp << std::endl;
                std::cerr << "Total:" << std::endl;
                for (int& total : needed_total)
                    std::cerr << total << std::endl;

                if (priority_temp > priority)
                {
                    needed = needed_temp;

                    sample = sample_it;
                    priority = priority_temp;
                }

                if (priority_temp >= 1)
                    needed_total += needed_temp;
            }
        }

        // Todo: Improve code to compute if its possible to gather enough molecule for another sample.
        if (ROUNDS_MOVIMENT + m_samples_ready.size() == rounds_to_end || m_storage.sum() == 10)
        {
            if ((needed <= 0).min() == true && sample != m_samples_diagnosed.end())
            {
                update_reserve(sample);
            }

            set_state(ST_PRODUCEMEDICINES);
            return;
        }

        if (sample == m_samples_diagnosed.end()) // There are not enough molecules.
        {
            if (m_samples_ready.empty())  // If there isnt enough molecules for any sample WAIT.
                std::cout << "WAIT" << std::endl;
            else
                set_state(ST_PRODUCEMEDICINES);
        }
        else if (!choose_molecule(needed , needed_total))
        {
            update_reserve(sample);
            continue; // No output so continue to next interaction.
        }
        break; // out of while.
    }
}

void Robot::st_produce_medicne()
{
    constexpr int MAXIMUM_ROUNDS_MOVIMENT = 3 + 3 + 3 + 3;      // Laboratory -> Samples -> Diagnosis -> Molecules -> Laboratory.
    constexpr int ROUNDS_TASKS = 3 * 2 + 4;                     // How many rounds are necessary doing tasks.
    constexpr int NEEDED_ROUNDS = MAXIMUM_ROUNDS_MOVIMENT + ROUNDS_TASKS;

    int const rounds_to_end = GameWorld::get_instance()->get_round_to_end();

    if (!m_samples_ready.empty())
    {
        Sample& sample = m_samples_ready.front();
        std::cout << "CONNECT " << sample.sampleId << std::endl;
        m_reserved -= sample.cost;

        m_samples_ready.pop_front();
    }
    else
    {
        // If the robot is still carring sample and there are enough molecules gather molecule. 
        if (m_samples_diagnosed.size() > 1 || (!m_samples_diagnosed.empty() && NEEDED_ROUNDS > rounds_to_end))
            set_state(ST_GATHERMOLECULES);
        else
            set_state(ST_COLLECTSAMPLE);
    }
}

void Robot::st_moving()
{
    if (m_eta == 1)
    {
        m_current_state = m_next_state;
        m_next_state = ST_MOVING;
    }
    std::cout << "WAIT" << std::endl;
}

void Robot::update_sample_cost()
{
    ModuleDiagnosis::get_instance()->update_undiagnosed_samples(m_samples_diagnosed, 0);

    for (Sample& sample : m_samples_diagnosed)
    {
        sample.cost -= m_expertise;
        
        for (int& cost : sample.cost)
            cost = std::max(cost, 0);
    }

    // Check if there are two free samples
    auto sample_it = m_samples_diagnosed.begin();
    while (sample_it != m_samples_diagnosed.end())
    {
        if (is_sample_free(*sample_it))
            move_to_ready(sample_it++);
        else
            sample_it++;
    }
}

bool Robot::is_sample_free(Sample const& sample)
{
    if ((sample.cost == 0).min() == true)
        return true;
    else
        return false;
}

bool Robot::is_sample_valid()
{
    bool valid = true;
    auto sample_it = m_samples_diagnosed.begin();
    while (sample_it != m_samples_diagnosed.end())
    {
        if (is_sample_valid(*sample_it))
            sample_it++;
        else
        {
            std::cout << "CONNECT " << sample_it->sampleId << std::endl; // Store in the cloud.
            m_samples_diagnosed.erase(sample_it++);
            valid = false;
        }
    }
    return valid;
}

bool Robot::is_sample_valid(Sample& sample)
{
    int total_cost = sample.cost.sum();

    if ((sample.cost > 5).max() == true || total_cost > 8)
        return false;
    else
        return true;
}

int Robot::get_sample_priority(Sample const& sample)
{
    // Priority is determined by how many other samples are allowed to be researched together with it.
    
    bool is_sample_valid = false; // Check if sample is part of  m_samples_diagnosed
    
    int priority = 0;
         
    for (Sample const& sample_aux : m_samples_diagnosed)
    {
        if (sample_aux == sample)
        {
            is_sample_valid = true;
            continue;
        }
        
        if (((sample.cost + sample_aux.cost) > 5).max() == true)
            continue;

        if ((sample.cost + sample_aux.cost).sum() > 10)
            continue;

        priority++;
    }

    if (!is_sample_valid)
    {
        std::cerr << "This sample is not valid" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    return priority;
}

void Robot::move_to_ready(std::list<Sample>::iterator sample_it)
{
    m_samples_ready.splice(m_samples_ready.end(), m_samples_diagnosed, sample_it); // move samples form diagnosed to ready

    auto update_cost = [](int index, std::list<Sample>& samples_diagnosed)
    {
        for (Sample& sample : samples_diagnosed)
            sample.cost[index] = std::max(--sample.cost[index], 0);
    };


    if (m_samples_ready.back().expertiseGain == "A")
        update_cost(0, m_samples_diagnosed);
    else if (m_samples_ready.back().expertiseGain == "B")
        update_cost(1, m_samples_diagnosed);
    else if (m_samples_ready.back().expertiseGain == "C")
        update_cost(2, m_samples_diagnosed);
    else if (m_samples_ready.back().expertiseGain == "D")
        update_cost(3, m_samples_diagnosed);
    else if (m_samples_ready.back().expertiseGain == "E")
        update_cost(4, m_samples_diagnosed);
}

void Robot::update_reserve(std::list<Sample>::iterator sample_it)
{
    m_reserved += sample_it->cost;

    move_to_ready(sample_it); // Update vectors
}

int Robot::choose_rank()
{
    int expertise_total = m_expertise.sum();

    if ((expertise_total) < 9)
        return 1;
    else if ((expertise_total) < 15)
        return 2;
    else
        return 3;
}

bool Robot::choose_molecule(std::valarray<int> const& needed, std::valarray<int> const& needed_total)
{
    if (needed.max() == 0)
        return false;
    else
    {
        int max_value = 0;
        int index_of_max = 0;
        for (int i = 0; i < needed.size(); i++)
        {
            std::cerr << "Needed: " << needed[i] << std::endl;
            std::cerr << "Needed_Total: " << needed_total[i] << std::endl;

            if (needed_total.max() == 0)
            {
                if (needed[i] > max_value)
                {
                    max_value = needed_total[i];
                    index_of_max = i;
               }
            }
            else
            {
                if (needed_total[i] > max_value && (needed[i] > 0)) // choose most critical.
                {
                    max_value = needed_total[i];
                    index_of_max = i;
                }
            }
        }

        if (index_of_max == 0)
            std::cout << "CONNECT A" << std::endl;
        else if (index_of_max == 1)
            std::cout << "CONNECT B" << std::endl;
        else if (index_of_max == 2)
            std::cout << "CONNECT C" << std::endl;
        else if (index_of_max == 3)
            std::cout << "CONNECT D" << std::endl;
        else if (index_of_max == 4)
            std::cout << "CONNECT E" << std::endl;

        return true;
    }

    if (needed[0] > 0)
    std::cout << "CONNECT A" << std::endl;
    else if (needed[1] > 0)
    std::cout << "CONNECT B" << std::endl;
    else if (needed[2] > 0)
    std::cout << "CONNECT C" << std::endl;
    else if (needed[3] > 0)
    std::cout << "CONNECT D" << std::endl;
    else if (needed[4] > 0)
    std::cout << "CONNECT E" << std::endl;

}

std::ostream& operator<<(std::ostream& os, Robot const& robot)
{
    os << "Print Robot info: "<< robot.m_name << "\n\n";

    // Todo add state info.

    os << "Stored Molecules: \n";
    
    os << "Type A: " << robot.m_storage[0] << "\n";
    os << "Type B: " << robot.m_storage[1] << "\n";
    os << "Type C: " << robot.m_storage[2] << "\n";
    os << "Type D: " << robot.m_storage[3] << "\n";
    os << "Type E: " << robot.m_storage[4] << "\n\n";
    
    os << "Reserved Molecules: \n";

    os << "Type A: " << robot.m_reserved[0] << "\n";
    os << "Type B: " << robot.m_reserved[1] << "\n";
    os << "Type C: " << robot.m_reserved[2] << "\n";
    os << "Type D: " << robot.m_reserved[3] << "\n";
    os << "Type E: " << robot.m_reserved[4] << "\n\n";
    
    os << "Expertise: \n";
    
    os << "Type A: " << robot.m_expertise[0] << "\n";
    os << "Type B: " << robot.m_expertise[1] << "\n";
    os << "Type C: " << robot.m_expertise[2] << "\n";
    os << "Type D: " << robot.m_expertise[3] << "\n";
    os << "Type E: " << robot.m_expertise[4] << "\n\n";

    os << "Diagnosed samples:\n";
    for (Sample const& sample : robot.m_samples_diagnosed)
        os << sample << "\n";

    os << "Ready samples:\n";
    for (Sample const& sample : robot.m_samples_ready)
        os << sample << "\n";

    return os;
}

int main()
{
    // Initialize project
    GameWorld::get_instance()->get_projects_info();

    // game loop
    while (true)
        GameWorld::get_instance()->update_world();
}