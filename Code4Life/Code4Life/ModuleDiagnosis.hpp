#pragma once

#include "Module.hpp"

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
