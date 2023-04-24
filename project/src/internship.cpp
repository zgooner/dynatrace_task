#include <chrono>
#include <fstream>
#include <iostream>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

#include "internship.h"

using json = nlohmann::json;
using date = boost::gregorian::date;
using date_duration = boost::gregorian::date_duration;

namespace internship {
    std::vector<operating_system> parsingJson(const std::string& jsonFileName, int elementsCount) {
        std::ifstream f(jsonFileName);
        json data = json::parse(f);

        std::vector<operating_system> operatingSystems;
        for (const auto& product : data) {
            if (!product.contains(NAME_NODE) && !product.contains(OPERATING_SYSTEM_NODE)) {
                continue;
            }

            if (product[OPERATING_SYSTEM_NODE]) {
                for (const auto& version : product[VERSIONS_NODE]) {
                    if (!version.contains(RELEASE_DATE_NODE)
                        || !version.contains(EOL_NODE)
                        || !version.contains(CYCLE_NODE)) {
                        continue;
                    }

                    if (version[RELEASE_DATE_NODE].type() != json::value_t::string
                        || version[EOL_NODE].type() != json::value_t::string) {
                        continue;
                    }

                    try {
                        auto release_date = date(boost::gregorian::from_string(version[RELEASE_DATE_NODE].get<std::string>()));
                        auto eol_date = date(boost::gregorian::from_string(version[EOL_NODE].get<std::string>()));
                        auto system_period = eol_date - release_date;

                        operatingSystems.push_back(
                                operating_system(
                                        product[NAME_NODE],
                                        version[CYCLE_NODE],
                                        system_period.days() + 1 // Include eol day
                                )
                        );
                    } catch (std::out_of_range& ex) {
                        continue;
                    } catch (boost::bad_lexical_cast& ex) {
                        continue;
                    } catch (json::type_error& e) {
                        continue;
                    }
                }
            }
        }

        std::sort(operatingSystems.begin(), operatingSystems.end(),
                  [](const auto& a, const auto& b) { return a.system_period > b.system_period; });

        return operatingSystems;
    }

    void printSolution(std::vector<operating_system> operatingSystems, int elementsCount) {
        for (int i = 0; i < elementsCount && i < operatingSystems.size(); i++) {
            auto& os = operatingSystems[i];
            std::cout << os.name << " " << os.cycle << " " << os.system_period << "\n";
        }
    }

    // do not remove this function
    void solution(const std::string& jsonFileName, int elementsCount) {
        // put the call to your solution here
        std::vector<operating_system> operatingSystems = parsingJson(jsonFileName, elementsCount);
        printSolution(operatingSystems, elementsCount);
    }
}