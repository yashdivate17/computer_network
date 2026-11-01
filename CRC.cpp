#include <iostream>
#include <string>

using namespace std;

string modulo2Divide(string dividend, const string& generator) {
    if (generator.size() < 2) {
        throw invalid_argument("The generator must contain at least two bits.");
    }

    for (char bit : dividend) {
        if (bit != '0' && bit != '1') {
            throw invalid_argument("Binary values may contain only 0 and 1.");
        }
    }

    for (char bit : generator) {
        if (bit != '0' && bit != '1') {
            throw invalid_argument("The generator must contain only 0 and 1.");
        }
    }

    if (generator.front() != '1') {
        throw invalid_argument("The generator must start with 1.");
    }

    const size_t remainderLength = generator.size() - 1;

    for (size_t i = 0; i + generator.size() <= dividend.size(); ++i) {
        if (dividend[i] == '1') {
            for (size_t j = 0; j < generator.size(); ++j) {
                // XOR is modulo-2 addition: equal bits produce 0,
                // different bits produce 1.
                dividend[i + j] = (dividend[i + j] == generator[j]) ? '0' : '1';
            }
        }
    }

    return dividend.substr(dividend.size() - remainderLength);
}

string encode(const string& data, const string& generator) {
    string paddedData = data + string(generator.size() - 1, '0');
    string remainder = modulo2Divide(paddedData, generator);
    return data + remainder;
}

bool hasError(const string& codeword, const string& generator) {
    string remainder = modulo2Divide(codeword, generator);
    return remainder.find('1') != string::npos;
}

int main() {
    try {
        string data;
        string generator;

        cout << "Enter data bits: ";
        cin >> data;

        cout << "Enter generator bits: ";
        cin >> generator;

        string transmittedFrame = encode(data, generator);
        cout << "CRC remainder: "
             << transmittedFrame.substr(data.size()) << '\n';
        cout << "Transmitted frame: " << transmittedFrame << '\n';

        cout << "\nEnter received frame to check: ";
        string receivedFrame;
        cin >> receivedFrame;

        if (receivedFrame.size() < generator.size()) {
            throw invalid_argument("The received frame is shorter than the generator.");
        }

        if (hasError(receivedFrame, generator)) {
            cout << "Result: Error detected in the received frame.\n";
        } else {
            cout << "Result: No error detected.\n";
        }
    } catch (const exception& error) {
        cerr << "Input error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
