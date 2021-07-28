#pragma once

#include "Sample.hpp"

class Robot_base
{
public:
    Robot_base();


private:
    std::string         m_target;
    int                 m_eta;
    int                 m_score;

    std::valarray<int>    m_storage;
    std::valarray<int>    m_expertise;
};

class Robot_observer
{

};

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