#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <valarray>
#include <algorithm>

struct Sample
{
    // Assign constructor.
    Sample():cost(0, 5) {};

    Sample& operator = (Sample const& lhs);
    friend bool operator == (Sample const& rhs, Sample const& lhs);
    friend std::ostream& operator<<(std::ostream& os, Sample const& sample);

    void get_sample_info();

    int                 sampleId;
    int                 carriedBy;
    int                 rank;
    std::string         expertiseGain;
    int                 health;
    
    std::valarray<int>  cost;
};
