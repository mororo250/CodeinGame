#include "ModuleMolecules.hpp"

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
