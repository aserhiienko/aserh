#include <gtest/gtest.h>
#include <markov.h>

namespace {
TEST(TestMarkov, TestTerminationRule) {
    std::vector<projects::MarkovRule> rules = {
        {"A", "apple"}, {"B", "bag"}, {"S", "shop"}, {"T", "the"}, {"the shop", "my brother"}, {"XYZ", "<terminate>"}};
    // I bought a bag of apples from my brother <terminate>
    // cout << "markov=\"" << markov("I bought a B of As from T S XYZ", rules) << "\"" << endl;

    std::string expected = "I bought a bag of apples from my brother <terminate>";
    std::string input = "I bought a B of As from T S XYZ";
    std::string actual = projects::Markov().run(input, rules);
    EXPECT_EQ(actual, expected);
}
} // namespace
