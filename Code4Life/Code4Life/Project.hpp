#pragma once

#include <iostream>

class Project
{
public:

    Project() = default;
    Project(Project const& other) = default;
    Project& operator=(Project const& other) = default;
    ~Project() = default;

    void get_info_project();

    friend std::ostream& operator<<(std::ostream& os, Project const& project);

private:

    int m_a;
    int m_b;
    int m_c;
    int m_d;
    int m_e;
};
