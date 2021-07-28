#include "ModuleLaboratory.hpp"

ModuleLaboratory* ModuleLaboratory::s_module_laboratory = nullptr;

ModuleLaboratory* ModuleLaboratory::get_instance()
{
    if (s_module_laboratory == nullptr)
        s_module_laboratory = new ModuleLaboratory();

    return s_module_laboratory;
}
