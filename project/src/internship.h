#pragma once
#include <string>
#include <vector>
#include "operating_system.h"

namespace internship {
    const std::string NAME_NODE= "name";
    const std::string OPERATING_SYSTEM_NODE = "os";
    const std::string VERSIONS_NODE = "versions";
    const std::string RELEASE_DATE_NODE = "releaseDate";
    const std::string EOL_NODE = "eol";
    const std::string CYCLE_NODE = "cycle";

    std::vector<operating_system> parsingJson(const std::string& jsonFileName, int elementsCount);
    void printSolution(std::vector<operating_system> operatingSystems, int elementsCount);

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount);
}