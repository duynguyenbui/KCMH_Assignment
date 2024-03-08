#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

class DFA {
private:
    vector<string> Q;
    vector<string> Sigma;
    string q0;
    vector<string> F;
    unordered_map<string, unordered_map<string, string> > delta;

public:
    DFA(vector<string> _Q, vector<string> _Sigma, vector<string> _F, unordered_map<string, unordered_map<string, string> > _delta) {
        Q = _Q;
        Sigma = _Sigma;
        q0 = Q[0];
        F = _F;
        delta = _delta;
    }

    string validate(string str) {
        string state = q0;
        for (char ch : str) {
            string s(1, ch);
            if (Sigma.end() == find(Sigma.begin(), Sigma.end(), s)) {
                return "NO";
            }
            state = delta[state][s];
        }
        if (find(F.begin(), F.end(), state) != F.end()) 
            return "YES";
        return "NO";
    }
};

int main() {
    ifstream inputFile("input.txt");
    int n, m;
    inputFile >> m >> n;
    vector<string> Q(m), Sigma(n), F;

    for (int i = 0; i < m; ++i) {
        inputFile >> Q[i];
    }
    for (int i = 0; i < n; ++i) {
        inputFile >> Sigma[i];
    }
    string f;
    inputFile >> f;
    F.push_back(f);

    unordered_map<string, unordered_map<string, string> > delta;

    for (int i = 0; i < n * m; i++) {
        string nstart, char_, ndest;
        inputFile >> nstart >> char_ >> ndest;
        if (delta.find(nstart) != delta.end()) {
            delta[nstart].insert(make_pair(char_, ndest));
        } else {
            unordered_map<string, string> temp;
            temp.insert(make_pair(char_, ndest));
            delta.insert(make_pair(nstart, temp));
        }

    }

    inputFile.close();
    DFA dfa(Q, Sigma, F, delta);
    string input_str;
    cout << "Enter the string to validate: ";
    cin >> input_str;
    cout << dfa.validate(input_str) << endl;
    return 0;
}
