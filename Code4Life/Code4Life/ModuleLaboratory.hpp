#pragma once

#include "Module.hpp"

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
