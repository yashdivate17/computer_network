#include <iostream>
using namespace std;

int main() {
    int a, b, c, d, prefix;
    char dot, slash;
    unsigned long ip, mask, network, broadcast, numAddresses;

    cout << "Enter IP address with prefix (a.b.c.d/prefix): ";
    cin >> a >> dot >> b >> dot >> c >> dot >> d >> slash >> prefix;

    if (prefix < 0 || prefix > 32) {
        cout << "Invalid prefix" << endl;
        return 0;
    }

    ip = (a * 16777216UL) + (b * 65536UL) + (c * 256UL) + d;

    if (prefix == 0) {
        mask = 0;
    }
    else {
        mask = 4294967295UL << (32 - prefix);  
    }

    network = ip & mask;

    broadcast = network | (~mask & 4294967295UL);

    if (prefix == 32) {
        numAddresses = 1;
    }
    else {
        numAddresses = 1UL << (32 - prefix);
    }
    int ma = (mask >> 24) & 255, mb = (mask >> 16) & 255, mc = (mask >> 8) & 255, md = mask & 255;
    int na = (network >> 24) & 255, nb = (network >> 16) & 255, nc = (network >> 8) & 255, nd = network & 255;
    int ba = (broadcast >> 24) & 255, bb = (broadcast >> 16) & 255, bc = (broadcast >> 8) & 255, bd = broadcast & 255;

    cout << "\nIP Address        : " << a << "." << b << "." << c << "." << d << "/" << prefix << endl;
    cout << "Subnet Mask       : " << ma << "." << mb << "." << mc << "." << md << endl;
    cout << "Network Address   : " << na << "." << nb << "." << nc << "." << nd << endl;
    cout << "Broadcast Address : " << ba << "." << bb << "." << bc << "." << bd << endl;
    cout << "No. of Addresses  : " << numAddresses << endl;

    if (numAddresses > 2) {
        unsigned long firstHost = network + 1;
        unsigned long lastHost = broadcast - 1;

        int fa = (firstHost >> 24) & 255, fb = (firstHost >> 16) & 255, fc = (firstHost >> 8) & 255, fd = firstHost & 255;
        int la = (lastHost >> 24) & 255, lb = (lastHost >> 16) & 255, lc = (lastHost >> 8) & 255, ld = lastHost & 255;

        cout << "First Usable Host : " << fa << "." << fb << "." << fc << "." << fd << endl;
        cout << "Last Usable Host  : " << la << "." << lb << "." << lc << "." << ld << endl;
    }
    else {
        cout << "No usable host range (point-to-point / single host subnet)" << endl;
    }

    return 0;
}