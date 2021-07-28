#pragma once

#include "Module.hpp"

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
