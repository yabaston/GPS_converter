#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "GpsData.h"

using namespace std;

std::vector<std::string> SplitIntoWords(const std::string& text) {
    std::vector<std::string> words;
    words.reserve(text.size());
    std::string word;

    size_t i = 0;
    size_t index = text.find(',', 0);
    for (; index < text.size();) {
        words.push_back(text.substr(i, (index - i)));
        i = ++index;
        index = text.find(',', i);
        if (!index) {
            break;
        }
    }
    words.push_back(text.substr(i, text.size() - i));

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}



int main(int argc, char* argv[]) {
    //setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        cout << "Wrong arguments" << endl;
        return -1;
    }

    string input_filename = string(argv[1]);

    if (argc == 3 && argv[2][0] == '-') {
        if (argv[2][1] - '0' == 2) {
            SET_DELTA(24);
        } else if (argv[2][1] - '0' == 3) {
            SET_DELTA(30);
        } else {
            cout << "Unknown option" << endl;
            return -1;
        }
    }

    ifstream input_stream{input_filename, ios::in};
    if (!input_stream.is_open()) {
        cout << "Failed to open input file: " << input_filename << endl;
        return -1;
    }

    string output_filename = input_filename.substr(0, input_filename.size() - 4) + ".txt";
    ofstream os(output_filename, ios::out);
    if (!os.is_open()) {
        cout << "Failed to create output file: " << output_filename << endl;
        return -1;
    }

    //Data GPS_data;
    vector<vector<Data>> result = {};
    result.reserve(40000);

    string str;
    bool is_first = true;
    if (input_stream.good()) {
        while (getline(input_stream, str)) {
            vector<string> line = {};
            if (is_first) {
                line = SplitIntoWords(str);
                os << line[0] << ";" << line[1] << ";" << line[2] << ";" << line[3] << ";" << line[4] << ";" << "Frame\n";
                is_first = false;
            } else {
                line = SplitIntoWords(str);
                Data data(line);
                data.CalculateFrame();
                GPS gps = data.GetGpsData();
                os << setprecision(10) << data.GetCts() << ";" << data.GetDate() << ";"
                   << gps.LAT << ";" << gps.LON << ";" << gps.ALT << ";"
                   << data.GetFrame() << "\n";
            }

        }
    }

    input_stream.close();
    os.close();

    return 0;
}
