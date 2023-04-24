#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <string>
#include "../src/internship.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <nlohmann/json.hpp>

using namespace internship;
using json = nlohmann::json;
using date = boost::gregorian::date;

const std::string VALID_JSON_FILENAME = "test/data/valid.json";
const std::string EMPTY_JSON_FILENAME = "test/data/empty.json";
const std::string MISSING_FIELDS_JSON_FILENAME = "test/data/missingFields.json";
const std::string INVALID_JSON_FILENAME = "test/data/invalidData.json";

TEST(ParsingJsonTest, ValidJsonData) {
    const int elementsCount = 2;
    std::vector<operating_system> operatingSystems = internship::parsingJson(VALID_JSON_FILENAME, elementsCount);

    ASSERT_EQ(operatingSystems.size(), elementsCount);
    EXPECT_EQ(operatingSystems[0].name, "almalinux");
    EXPECT_EQ(operatingSystems[0].cycle, "9");
    EXPECT_EQ(operatingSystems[0].system_period, 3659);
    EXPECT_EQ(operatingSystems[1].name, "alpine");
    EXPECT_EQ(operatingSystems[1].cycle, "3.17");
    EXPECT_EQ(operatingSystems[1].system_period, 732);
}

TEST(ParsingJsonTest, EmptyFile) {
    auto operatingSystems = internship::parsingJson(EMPTY_JSON_FILENAME, 10);
    EXPECT_TRUE(operatingSystems.empty());
}

TEST(ParsingJsonTest, MissingFields) {
    auto operatingSystems = internship::parsingJson(MISSING_FIELDS_JSON_FILENAME, 10);
    EXPECT_TRUE(operatingSystems.empty());
}

TEST(ParsingJsonTest, InvalidData) {
    auto operatingSystems = internship::parsingJson(INVALID_JSON_FILENAME, 10);

    EXPECT_EQ(operatingSystems.size(), 1);
    EXPECT_EQ(operatingSystems[0].name, "Windows");
    EXPECT_EQ(operatingSystems[0].cycle, "3");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}