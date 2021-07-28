#include "ModuleDiagnosis.hpp"

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
