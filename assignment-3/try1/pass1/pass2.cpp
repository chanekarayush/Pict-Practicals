#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <numeric> // For std::accumulate

using namespace std;

// Function to get key from a map based on value
string get_key(const string &val, const map<string, string> &dict)
{
    for (const auto &pair : dict)
    {
        if (val == pair.second)
        {
            return pair.first;
        }
    }
    return "";
}

// Function to process parameter placeholders in the form (P,1) or (C,11)
pair<string, int> process_params(const string &param)
{
    regex pattern(R"(\(([^,]+),(\d+)\))");
    smatch match;
    if (regex_match(param, match, pattern))
    {
        string component1 = match[1];
        int component2 = stoi(match[2]);
        return {component1, component2};
    }
    return {"", 0};
}

// Function to convert a vector of strings into a space-separated string
string convert(const vector<string> &lst)
{
    return accumulate(lst.begin(), lst.end(), string(),
                      [](const string &a, const string &b)
                      {
                          return a + (a.length() > 0 ? " " : "") + b;
                      });
}

int main()
{
    // File paths
    const string mntFilePath = "mnt.txt";
    const string mdtFilePath = "mdt.txt";
    const string kpdtabFilePath = "kpdtab.txt";
    const string callsFilePath = "calls.txt";
    const string expcodeFilePath = "expcode.txt";
    const string aptabFilePath = "aptab.txt"; // File path for APTAB

    // Read MNT from file
    ifstream mntFile(mntFilePath);
    if (!mntFile)
    {
        cerr << "Error opening MNT file!" << endl;
        return 1;
    }
    map<int, map<string, string>> mnt;
    string line;

    // Skip header and separator line
    getline(mntFile, line); // Skip header
    getline(mntFile, line); // Skip separator

    while (getline(mntFile, line))
    {
        if (line.empty())
            continue;

        istringstream iss(line);
        int index;
        string name, pp, kp, mdtp, kpdtp;
        if (!(iss >> index >> name >> pp >> kp >> mdtp >> kpdtp))
        {
            cerr << "Error parsing line in MNT file: " << line << endl;
            continue;
        }

        mnt[index] = {{"name", name}, {"pp", pp}, {"kp", kp}, {"mdtp", mdtp}, {"kpdtp", kpdtp}};
    }
    mntFile.close();

    // Read MDT from file
    ifstream mdtFile(mdtFilePath);
    if (!mdtFile)
    {
        cerr << "Error opening MDT file!" << endl;
        return 1;
    }
    map<int, vector<string>> mdtMap;
    int index = 1;

    // Skip header and separator line
    // getline(mdtFile, line); // Skip header
    // getline(mdtFile, line); // Skip separator

    while (getline(mdtFile, line))
    {
        if (line.empty())
            continue;

        // if (line.find("MEND") != string::npos)
        // {
        //     continue;
        // }

        if (mdtMap.find(index) == mdtMap.end())
        {
            mdtMap[index] = {};
        }
        mdtMap[index].push_back(line);
        index++;
    }
    mdtFile.close();

    // Read KPD TAB from file
    ifstream kpdtabFile(kpdtabFilePath);
    if (!kpdtabFile)
    {
        cerr << "Error opening KPD TAB file!" << endl;
        return 1;
    }
    map<int, map<string, string>> kpdtab;

    // Skip header and separator line
    getline(kpdtabFile, line); // Skip header
    getline(kpdtabFile, line); // Skip separator

    while (getline(kpdtabFile, line))
    {
        if (line.empty())
            continue;

        istringstream iss(line);
        int index;
        string name, value;
        if (!(iss >> index >> name >> value))
        {
            cerr << "Error parsing line in KPD TAB file: " << line << endl;
            continue;
        }

        kpdtab[index] = {{"name", name}, {"value", value}};
    }
    kpdtabFile.close();

    // Open output file for expanded code
    ofstream expcodeFile(expcodeFilePath);
    if (!expcodeFile)
    {
        cerr << "Error opening EXPFILE file!" << endl;
        return 1;
    }

    // Open input file for the assembly code
    ifstream callsFile(callsFilePath);
    if (!callsFile)
    {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    // Open file to write APTAB contents
    ofstream aptabFile(aptabFilePath);
    if (!aptabFile)
    {
        cerr << "Error opening APTAB file!" << endl;
        return 1;
    }

    while (getline(callsFile, line))
    {
        if (line.empty())
            continue;

        // Split the line into words
        regex spacePattern(R"(\s+)");
        sregex_token_iterator iter(line.begin(), line.end(), spacePattern, -1);
        sregex_token_iterator end;
        vector<string> cmd(iter, end);

        if (cmd.empty())
            continue;

        string macroName = cmd[0];                         // Macro name is the first item
        vector<string> MPList(cmd.begin() + 1, cmd.end()); // Remaining items are parameters

        string mdtPointer, kpdtPointer, npp, nkp;

        // Find the macro in MNT
        bool foundMacro = false;
        for (const auto &entry : mnt)
        {
            const auto &key = entry.first;
            const auto &value = entry.second;
            if (value.at("name") == macroName)
            {
                mdtPointer = value.at("mdtp");
                kpdtPointer = value.at("kpdtp");
                npp = value.at("pp");
                nkp = value.at("kp");
                foundMacro = true;
                break;
            }
        }
        if (!foundMacro)
        {
            cerr << "Macro not found: " << macroName << endl;
            continue;
        }

        int totalParams = 0;
        try
        {
            totalParams = stoi(npp) + stoi(nkp);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid argument for stoi (npp or nkp): " << e.what() << endl;
            continue; // Skip this macro call
        }
        catch (const out_of_range &e)
        {
            cerr << "Out of range for stoi (npp or nkp): " << e.what() << endl;
            continue; // Skip this macro call
        }

        map<string, string> APTAB; // Create an Actual Parameter Table (APTAB)
        int aptPointer = 1;

        // Process parameters and build APTAB
        for (const string &parameter : MPList)
        {
            string param = parameter;
            if (param.back() == ',')
            {
                param.pop_back(); // Remove trailing comma
            }
            if (param.find('=') != string::npos)
            {
                size_t eqIndex = param.find('=');
                string paramName = param.substr(0, eqIndex);
                string paramValue = param.substr(eqIndex + 1);
                APTAB[paramName] = paramValue;
            }
            else
            {
                APTAB[to_string(aptPointer)] = param;
                aptPointer++;
            }
        }

        // Assign default values to parameters from KPD TAB
        for (const auto &entry : kpdtab)
        {
            const auto &key = entry.first;
            const auto &value = entry.second;
            if (get_key(value.at("name"), APTAB) == to_string(key) && value.at("value") != "---")
            {
                string paramKey = get_key(value.at("name"), APTAB);
                if (APTAB.find(paramKey) != APTAB.end() && !APTAB[paramKey].empty())
                {
                    APTAB[paramKey] = value.at("value");
                }
            }
        }

        // Write APTAB to file
        for (const auto &entry : APTAB)
        {
            aptabFile << entry.first << ": " << entry.second << endl;
        }
        aptabFile << endl; // Separate entries for different macro calls

        vector<string> macroStmts;

        // Traverse to the macro definition in MDT
        int mdtIndex;
        try
        {
            mdtIndex = stoi(mdtPointer);
        }
        catch (const invalid_argument &e)
        {
            cerr << "Invalid argument for stoi (mdtPointer): " << e.what() << endl;
            continue; // Skip this macro call
        }
        catch (const out_of_range &e)
        {
            cerr << "Out of range for stoi (mdtPointer): " << e.what() << endl;
            continue; // Skip this macro call
        }

        auto mdtEntry = mdtMap.find(mdtIndex);
        if (mdtEntry != mdtMap.end())
        {
            // Collect macro statements until "MEND"
            auto it = mdtEntry->second.begin();
            auto end = mdtEntry->second.end();

            while (it != end)
            {
                const string &mdtLine = *it;

                if (mdtLine.find("MEND") != string::npos)
                {
                    break; // Exit loop when "MEND" is found
                }
                macroStmts.push_back(mdtLine);

                ++it; // Move to the next element
            }
        }

        // Replace parameter references with values from APTAB
        for (string &macroStatement : macroStmts)
        {
            vector<string> macroCmd;
            sregex_token_iterator iter(macroStatement.begin(), macroStatement.end(), spacePattern, -1);
            sregex_token_iterator end;
            macroCmd.assign(iter, end);

            for (size_t i = 0; i < macroCmd.size(); ++i)
            {
                string &item = macroCmd[i];
                if (item.find('(') != string::npos)
                {
                    auto result = process_params(item);
                    string component1 = result.first;
                    int pos = result.second;
                    if (APTAB.find(to_string(pos)) != APTAB.end())
                    {
                        item = APTAB[to_string(pos)];
                    }
                    else if (APTAB.find(component1) != APTAB.end())
                    {
                        item = APTAB[component1];
                    }
                }
            }

            macroCmd[0] = "+" + macroCmd[0]; // Prefix with '+'
            string expandedLine = convert(macroCmd);
            expcodeFile << expandedLine << endl;
        }

        expcodeFile << endl; // Separate macro expansions
    }

    callsFile.close();
    expcodeFile.close();
    aptabFile.close(); // Close the APTAB file

    return 0;
}
