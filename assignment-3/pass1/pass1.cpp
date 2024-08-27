#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <regex>

using namespace std;

// Function to get key from a map based on value
string get_key(const string& val, const map<int, string>& dict) {
    for (const auto& pair : dict) {
        if (val == pair.second) {
            return to_string(pair.first);
        }
    }
    return "";
}

// Function to print stuff fancily
template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw(width) << setfill(separator) << t;
}

int main() {
    // Clear the terminal screen
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

    // File paths
    const string inputFilePath = "program2.txt";
    const string mdtFilePath = "mdt.txt";
    const string mntFilePath = "mnt.txt";
    const string pntabFilePath = "pntab.txt";
    const string kpdtabFilePath = "kpdtab.txt";

    // Open input file
    ifstream inputFile(inputFilePath);
    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    // Open output files
    ofstream mdtFile(mdtFilePath, ios::app);
    if (!mdtFile) {
        cerr << "Error opening MDT file!" << endl;
        return 1;
    }

    ofstream mntFile(mntFilePath);
    if (!mntFile) {
        cerr << "Error opening MNT file!" << endl;
        return 1;
    }

    ofstream pntabFile(pntabFilePath);
    if (!pntabFile) {
        cerr << "Error opening PNTAB file!" << endl;
        return 1;
    }

    ofstream kpdtabFile(kpdtabFilePath);
    if (!kpdtabFile) {
        cerr << "Error opening KPD TAB file!" << endl;
        return 1;
    }

    /// @brief Vector for Macro Name table
    map<int, map<string, string>> mnt;

    /// @brief Vector for Parameter Number Table
    map<string, map<int, string>> pntab;

    /// @brief Vector for Keyword Parameter Table
    map<int, map<string, string>> kpdtab;

    /// @brief This is used to separate the different macros in the MNT 
    string macroName;

    /// Starting index for kpdtab
    int kpdtabIndex = 1;

    /// kpdt pointer 
    int kpdtabLoc = 1;

    /// Index for macro name table
    int mntIndex = 1;

    /// Macro Definition table pointer
    int mdtLoc = 1;

    /// true if macro exist in MNT false if macro doesn't exist in mnt
    bool mSign = false;
    /// true if macro is define and false if macro is not
    bool mDef = false;

    /// Regex pattern to split on one or more spaces
    regex pattern ("\\s+");

    string line;
    while (getline(inputFile, line)) {
        if (line.empty()) continue;

        // Split the line into words
        sregex_token_iterator iter(line.begin(), line.end(), pattern, -1);
        sregex_token_iterator end;

        vector<string> cmd(iter, end);

        // When 'MACRO' is encountered
        if (cmd.size() == 1 && cmd[0] == "MACRO") {
            mSign = true;
            continue;
        }

        // If macro definition has been encountered
        if (mSign) {
            macroName = cmd[0];
            pntab[macroName] = {};
            int paramCnt = 0;
            int pp = 0;
            int kp = 0;

            // Process parameters
            for (size_t i = 1; i < cmd.size(); ++i) {
                string parameter = cmd[i];
                if (parameter.find(',') != string::npos) {
                    // removes commas
                    parameter.erase(parameter.find(','), 1);
                }
                // checks if argument is positional or parameter
                if (parameter.find('&') != string::npos && parameter.find('=') == string::npos) {
                    paramCnt++;
                    pp++;
                    pntab[macroName][paramCnt] = parameter.substr(1);
                } 
                // checks if argument is keyword arg
                else if (parameter.find('&') != string::npos && parameter.find('=') != string::npos) {
                    paramCnt++;
                    if (kp == 0) {
                        kpdtabLoc = kpdtabIndex;
                    }

                    kp++;
                    size_t eqIndex = parameter.find('=');
                    string paramName = parameter.substr(1, eqIndex - 1);
                    string paramDefValue = (parameter.length() > eqIndex + 1) ? parameter.substr(eqIndex + 1) : "---";

                    pntab[macroName][paramCnt] = paramName;
                    kpdtab[kpdtabIndex] = { {"index", to_string(kpdtabIndex)}, {"name", paramName}, {"value", paramDefValue} };

                    kpdtabIndex++;
                }
            }

            mSign = false;
            mDef = true;
            mnt[mntIndex] = { {"index", to_string(mntIndex)}, {"name", macroName}, {"pp", to_string(pp)}, {"kp", to_string(kp)}, {"mdtp", to_string(mdtLoc)}, {"kpdtp", (kp > 0 ? to_string(kpdtabLoc) : "---")} };

            mntIndex++;
            continue;
        }

        if (mDef) {
            mdtLoc++;
            string callLine;

            for (const string& command : cmd) {
                string paramCommand = command;
                if (paramCommand.find(',') != string::npos) {
                    paramCommand.erase(paramCommand.find(','), 1);
                }
                if (paramCommand.find('&') != string::npos) {
                    string replParamValue = "(P," + get_key(paramCommand.substr(1), pntab[macroName]) + ")";
                    callLine += replParamValue + " ";
                } else {
                    callLine += paramCommand + " ";
                }
            }

            mdtFile << callLine << endl;
            continue;
        }

        if (cmd.size() == 1 && cmd[0] == "MEND") {
            mdtLoc++;
            mDef = false;
            mdtFile << "MEND" << endl;
            continue;
        }
    }

    inputFile.close();
    mdtFile.close();

    // Write MNT file
    for (const auto& pair : mnt) {
        int key = pair.first;
        const map<string, string>& value = pair.second;
        mntFile << "Index: " << key << endl;
        for (const auto& kv : value) {
            mntFile << kv.first << ": " << kv.second << endl;
        }
        mntFile << endl;
    }
    mntFile.close();

    // Write PNTAB file
    for (const auto& pair : pntab) {
        const string& macro = pair.first;
        const map<int, string>& params = pair.second;
        pntabFile << "Macro: " << macro << endl;
        for (const auto& kv : params) {
            pntabFile << "Param " << kv.first << ": " << kv.second << endl;
        }
        pntabFile << endl;
    }
    pntabFile.close();

    // Write KPD TAB file
    for (const auto& pair : kpdtab) {
        int key = pair.first;
        const map<string, string>& value = pair.second;
        kpdtabFile << "Index: " << key << endl;
        for (const auto& kv : value) {
            kpdtabFile << kv.first << ": " << kv.second << endl;
        }
        kpdtabFile << endl;
    }
    kpdtabFile.close();

    return 0;
}
