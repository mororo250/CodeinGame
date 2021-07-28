#include "Project.hpp"

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
