#include "ModuleSample.hpp"

ModuleSamples* ModuleSamples::s_module_samples = nullptr;

ModuleSamples* ModuleSamples::get_instance()
{
    if (s_module_samples == nullptr)
        s_module_samples = new ModuleSamples();

    return s_module_samples;
}
