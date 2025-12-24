#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


void sort(std::string& a, std::string& b, std::string& c) {
    // implement sort here
    std::vector<std::string> words;
    words.push_back(a);
    words.push_back(b);
    words.push_back(c);

    sort(words.begin(), words.end());

    a = words[0];
    b = words[1];
    c = words[2];
}

int main(int argc, char const* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " a b c" << std::endl;
        return 1;
    }

    std::string a = argv[1];
    std::string b = argv[2];
    std::string c = argv[3];

    sort(a, b, c);

    std::cout << a << ' ' << b << ' ' << c << std::endl;

    return 0;
}
