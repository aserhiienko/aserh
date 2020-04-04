#include"markov.h"
using namespace std;

string replace(string text, string a, string b) {
    auto location = text.find(a);
    if (location != string::npos) {
        text.replace(location, a.size(), b);
    }

    return text;
}
string projects::Markov::run(string input, vector<projects::MarkovRule> rules) {

    bool didApplyRule = false;
  
    do {
        didApplyRule = false;
        for (auto rule : rules) {
           // cout << "trying to apply: '" <<  rule.pattern << "' ->' " << rule.replacement << "'" << endl;
            auto processed = replace(input, rule.pattern, rule.replacement);
            if (processed != input) {
                //cout << "applied" << endl;
                didApplyRule = true;
                if (rule.replacement == "<terminate>") {
                    //cout << "Caught termination rule: '" << processed<< "'" << endl;
                    return processed;
                }

                input = processed;
              //  cout << "processed: '" << processed << "'" << endl;
                break;
            }
        }
    } while (didApplyRule);
    // }

   // cout << "No rule to apply: '" << input << "'" << endl;
    return input;
}
