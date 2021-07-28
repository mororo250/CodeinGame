#pragma once

#include "Module.hpp"

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