#include<string>
#include<vector>
namespace projects{
struct MarkovRule{
std::string pattern= "";
std::string replacement= "";

};
struct Markov{
std:: string run (std::string text, std::vector<MarkovRule> rules);

};
}
