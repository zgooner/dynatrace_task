#ifndef DYNATRACE_CPP_INTERNSHIP_2023_OPERATING_SYSTEM_H
#define DYNATRACE_CPP_INTERNSHIP_2023_OPERATING_SYSTEM_H

struct operating_system {
    std::string name;
    std::string cycle;
    int system_period;

    operating_system(std::string name, std::string cycle, int system_period) :
        name(name), cycle(cycle), system_period(system_period) {}
};

#endif //DYNATRACE_CPP_INTERNSHIP_2023_OPERATING_SYSTEM_H
