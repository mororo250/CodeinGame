#include "Sample.hpp"

Sample& Sample::operator=(Sample const& lhs)
{
    sampleId        = lhs.sampleId;
    carriedBy       = lhs.carriedBy;
    rank            = lhs.rank;
    expertiseGain   = lhs.expertiseGain;
    health          = lhs.health;
    cost            = lhs.cost;
    return *this;
}

bool operator == (Sample const& rhs, Sample const& lhs)
{
    if (rhs.sampleId == lhs.sampleId)
        return true;
    else
        return false;
}

std::ostream& operator<<(std::ostream& os, Sample const& sample)
{
    if (sample.health == -1)
        os << "State: Undiagnosed\n";
    else
        os << "State: Diagnosed\n";

    os << "Sample Id:" << sample.sampleId << "\n";
    if (sample.carriedBy == 0)
        os << "Carried by: Player1\n";
    else if (sample.carriedBy == 1)
        os << "Carried by: Player2\n";
    else
        os << "Carried by: Cloud\n";

    os << "rank: " << sample.rank << "\n";
    os << "expertise Gain: " << sample.expertiseGain << "\n";
    os << "health: " << sample.health << "\n";

    os << "costA: " << sample.cost[0] << "\n";
    os << "costB: " << sample.cost[1] << "\n";
    os << "costC: " << sample.cost[2] << "\n";
    os << "costD: " << sample.cost[3] << "\n";
    os << "costE: " << sample.cost[4] << "\n";

    return os;
}

void Sample::get_sample_info()
{
    std::cin    >> sampleId
                >> carriedBy
                >> rank
                >> expertiseGain
                >> health
                >> cost[0]
                >> cost[1]
                >> cost[2]
                >> cost[3]
                >> cost[4];
    std::cin.ignore();
}
