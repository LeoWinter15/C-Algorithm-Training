#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Letters ordered from hottest (O) to coolest (M)
    const string letters = "OBAFGKM";

    int T;
    cin >> T;

    while (T--) {
        string a, b;
        cin >> a >> b;

        // Compute rank: lower number = hotter
        auto rank = [&](const string& s) -> int {
            int letterIdx = static_cast<int>(letters.find(s[0]));
            int digit = s[1] - '0';
            return letterIdx * 10 + digit;
        };

        int ra = rank(a), rb = rank(b);

        if (ra < rb)
            cout << "hotter\n";
        else if (ra > rb)
            cout << "cooler\n";
        else
            cout << "same\n";
    }

    return 0;
}
