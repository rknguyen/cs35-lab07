#include <iostream>
#include <typeinfo>
#include "./argparse/argparse.hpp"

#define debug(x) cerr << #x << " : " << typeid(x).name() << " = " << x << '\n'

using namespace std;

void fetch_args(int argc, const char** argv, string &d, string &n, int &k) {
    argparse::ArgumentParser program("main");
    program.add_argument("-d").required();
    program.add_argument("-n").required();
    program.add_argument("-k").required().action([](const string& s) {
        return stoi(s);
    });

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        cerr << err.what() << endl;
        cerr << program;
        exit(0);
    }

    d = program.get<string>("-d");
    n = program.get<string>("-n");
    k = program.get<int>("-k");
}

int main(int argc, const char** argv) {
    int k;
    string d, n;

    fetch_args(argc, argv, d, n, k);

    debug(d);
    debug(n);
    debug(k);    

    return 0;
}
