#include <bits/stdc++.h>
#include <iostream>
#include <filesystem>
using namespace std;

// Structure to store opcode information
struct OpcodeTableEntry
{
    string opcode;
    string class_type;
    string mnemonic;
};

// Hard-coded opcode information
struct OpcodeTableEntry optable[18] = {
    {"STOP", "Instruction", "00"},
    {"ADD", "Instruction", "01"},
    {"SUB", "Instruction", "02"},
    {"MULT", "Instruction", "03"},
    {"MOVER", "Instruction", "04"},
    {"MOVEM", "Instruction", "05"},
    {"COMP", "Instruction", "06"},
    {"BC", "Instruction", "07"},
    {"DIV", "Instruction", "08"},
    {"READ", "Instruction", "09"},
    {"PRINT", "Instruction", "10"},
    {"START", "AssemblerDirective", "01"},
    {"END", "AssemblerDirective", "02"},
    {"ORIGIN", "AssemblerDirective", "03"},
    {"EQU", "AssemblerDirective", "04"},
    {"LTORG", "AssemblerDirective", "05"},
    {"DC", "Declaration", "01"},
    {"DS", "Declaration", "02"}};

/**
 * @brief Fetches the index of opcode in the opcode table.
 *
 * @param opcode The mnemonic opcode to search for.
 * @return Index of the opcode in the table, or -1 if not found.
 */
int findOpcodeIndex(string opcode)
{
    for (int i = 0; i < 18; ++i)
    {
        if (optable[i].opcode == opcode)
            return i;
    }
    return -1;
}

/**
 * @brief Fetches the register ID based on the register name.
 *
 * @param regName The register name (AREG, BREG, CREG, DREG).
 * @return Corresponding register ID (1-4) or -1 if invalid.
 */
int getRegisterID(string regName)
{
    if (regName == "AREG")
        return 1;
    else if (regName == "BREG")
        return 2;
    else if (regName == "CREG")
        return 3;
    else if (regName == "DREG")
        return 4;
    else
        return -1;
}

/**
 * @brief Fetches the condition code based on the condition name.
 *
 * @param conditionName The condition name (LT, LE, EQ, GT, GE, ANY).
 * @return Corresponding condition code (1-6) or -1 if invalid.
 */
int getConditionCode(string conditionName)
{
    if (conditionName == "LT")
        return 1;
    else if (conditionName == "LE")
        return 2;
    else if (conditionName == "EQ")
        return 3;
    else if (conditionName == "GT")
        return 4;
    else if (conditionName == "GE")
        return 5;
    else if (conditionName == "ANY")
        return 6;
    else
        return -1;
}

// Structure to store symbol table entries
struct SymbolTable
{
    int index;
    string name;
    string address;
};

struct SymbolTable symtab[10]; // Symbol table array

/**
 * @brief Checks if a symbol is already present in the symbol table.
 *
 * @param symbol The symbol to check.
 * @return True if symbol is present, false otherwise.
 */
bool isSymbolPresent(string symbol)
{
    for (int i = 0; i < 10; ++i)
    {
        if (symtab[i].name == symbol)
            return true;
    }
    return false;
}

/**
 * @brief Fetches the index of a symbol in the symbol table.
 *
 * @param symbol The symbol to search for.
 * @return Index of the symbol in the table, or -1 if not found.
 */
int findSymbolIndex(string symbol)
{
    for (int i = 0; i < 10; ++i)
    {
        if (symtab[i].name == symbol)
            return i;
    }
    return -1;
}

// Structure to store literal table entries
struct LiteralTable
{
    int index;
    string name;
    string address;
};

struct LiteralTable littab[10]; // Literal table array

/**
 * @brief Checks if a literal is already present in the literal table.
 *
 * @param literal The literal to check.
 * @return True if literal is present, false otherwise.
 */
bool isLiteralPresent(string literal)
{
    for (int i = 0; i < 10; ++i)
    {
        if (littab[i].name == literal)
            return true;
    }
    return false;
}

/**
 * @brief Fetches the index of a literal in the literal table.
 *
 * @param literal The literal to search for.
 * @return Index of the literal in the table, or -1 if not found.
 */
int findLiteralIndex(string literal)
{
    for (int i = 0; i < 10; ++i)
    {
        if (littab[i].name == literal)
            return i;
    }
    return -1;
}

// Structure to store pool table entries
struct PoolTable
{
    int index;
    string literal_number;
};

struct PoolTable pooltab[10]; 

int main()
{
    ifstream inputFile;
    inputFile.open("input2.txt"); 

    ofstream intermediateCodeFile, symbolTableFile, literalTableFile;
    const char *path1 = "intermediateCode.txt";
    const char *path2 = "symbolTable.txt";
    const char *path3 = "literalTable.txt";
    intermediateCodeFile.open(path1);
    symbolTableFile.open(path2);
    literalTableFile.open(path3);

    string label, opcode, operand1, operand2;
    int symbolCount = 0, literalCount = 0, undefinedLiteralCount = 0, poolCount = 0, locationCounter = 0;

    cout << "\n -- ASSEMBLER PASS-1 OUTPUT --" << endl;
    cout << "\n <LABEL\tOPCODE\tOPERAND1\tOPERAND2\tLOCATION_COUNTER\tINTERMEDIATE_CODE>" << endl;

    while (!inputFile.eof())
    {
        inputFile >> label >> opcode >> operand1 >> operand2;
        int opcodeIndex;
        string intermediateCode, lc;

        opcodeIndex = findOpcodeIndex(opcode); // Fetch the opcode index
        intermediateCode = "(" + optable[opcodeIndex].class_type + "," + optable[opcodeIndex].mnemonic + ") ";

        if (opcode == "START")
        {
            lc = "---";
            if (operand1 != "NAN")
            {
                locationCounter = stoi(operand1);
                intermediateCode += "(C," + operand1 + ")  NAN";
            }
        }

        if (opcode == "EQU")
        {
            lc = "---";
            intermediateCode += " NAN     NAN";
            if (isSymbolPresent(label))
            {
                symtab[findSymbolIndex(label)].address = symtab[findSymbolIndex(operand1)].address;
            }
            else
            {
                symtab[symbolCount].index = symbolCount + 1;
                symtab[symbolCount].name = label;
                symtab[symbolCount].address = symtab[findSymbolIndex(operand1)].address;
                symbolCount++;
            }
        }

        else if (label != "NAN")
        {
            if (isSymbolPresent(label))
            {
                symtab[findSymbolIndex(label)].address = to_string(locationCounter);
            }
            else
            {
                symtab[symbolCount].index = symbolCount + 1;
                symtab[symbolCount].name = label;
                symtab[symbolCount].address = to_string(locationCounter);
                symbolCount++;
            }
        }

        if (opcode == "ORIGIN")
        {
            string token1, token2;
            char operation;
            stringstream ss(operand1);
            size_t found = operand1.find('+');
            if (found != string::npos)
                operation = '+';
            else
                operation = '-';
            getline(ss, token1, operation);
            getline(ss, token2, operation);
            lc = "---";
            if (operation == '+')
            {
                locationCounter = stoi(symtab[findSymbolIndex(token1)].address) + stoi(token2);
                intermediateCode += "(S,0" + to_string(symtab[findSymbolIndex(token1)].index) + ")+" + token2 + " NAN";
            }
            else
            {
                locationCounter = stoi(symtab[findSymbolIndex(token1)].address) - stoi(token2);
                intermediateCode += "(S,0" + to_string(symtab[findSymbolIndex(token1)].index) + ")-" + token2 + " NAN";
            }
        }

        if (opcode == "LTORG")
        {
            cout << "  " << label << "\t" << opcode << "\t" << operand1 << "\t\t" << operand2 << "\t\t";
          for (int i = literalCount - undefinedLiteralCount; i < literalCount; ++i)
            {
                lc = to_string(locationCounter);
                intermediateCode = "(DL,01) (C,";
                string character(1, littab[i].name[2]);
                intermediateCode += character + ")    NAN";
                littab[i].address = to_string(locationCounter);
                locationCounter++;
                if (i < literalCount - 1)
                    cout << lc << "\t\t\t\t" << intermediateCode << "\n\t\t\t\t";
                else
                    cout <<"\t\t"<< lc << "\t\t\t\t" << intermediateCode << endl;
                intermediateCodeFile << lc << "\t" << intermediateCode << endl;
            }

            pooltab[poolCount].literal_number = "#" + to_string(littab[literalCount - undefinedLiteralCount].index);
            pooltab[poolCount].index = poolCount + 1;
            poolCount++;
            undefinedLiteralCount = 0;
            continue;
        }

        if (opcode == "END")
        {
            lc = "---";
            intermediateCode += " NAN     NAN";
            cout << "  " << label << "\t" << opcode << "\t" << operand1 << "\t\t" << operand2 << "\t\t" << lc << "\t\t\t" << intermediateCode << endl;
            intermediateCodeFile << lc << "\t" << intermediateCode << endl;
            if (undefinedLiteralCount)
            {
                for (int i = literalCount - undefinedLiteralCount; i < literalCount; ++i)
                {
                    lc = to_string(locationCounter);
                    intermediateCode = "(DL,01) (C,";
                    string character(1, littab[i].name[2]);
                    intermediateCode += character + ")    NAN";
                    littab[i].address = to_string(locationCounter);
                    locationCounter++;
                    cout << "\t\t\t\t\t\t" << lc << "\t\t\t\t" << intermediateCode << endl;
                    intermediateCodeFile << lc << "\t" << intermediateCode << endl;
                }
                pooltab[poolCount].literal_number = "#" + to_string(littab[literalCount - undefinedLiteralCount].index);
                pooltab[poolCount].index = poolCount + 1;
                poolCount++;
            }
            break;
        }

        if (opcode == "DC" || opcode == "DS")
        {
            lc = to_string(locationCounter);
            if (opcode == "DS")
            {
                intermediateCode += "(C," + operand1 + ")    NAN";
                locationCounter += stoi(operand1);
            }
            else
            {
                string character(1, operand1[1]);
                intermediateCode += "(C," + character + ")";
                locationCounter++;
            }
        }

        if (opcode != "START" && opcode != "END" && opcode != "ORIGIN" && opcode != "EQU" && opcode != "LTORG" && opcode != "DC" && opcode != "DS")
        {
            if (operand2 == "NAN")
            {
                if (operand1 == "NAN")
                {
                    lc = to_string(locationCounter);
                    locationCounter++;
                    intermediateCode += " NAN     NAN";
                }
                else
                {
                    if (isSymbolPresent(operand1))
                    {
                        intermediateCode += "(S,0" + to_string(symtab[findSymbolIndex(operand1)].index) + ")";
                        lc = to_string(locationCounter);
                        locationCounter++;
                    }
                    else
                    {
                        symtab[symbolCount].index = symbolCount + 1;
                        symtab[symbolCount].name = operand1;
                        symbolCount++;
                        intermediateCode += "(S,0" + to_string(symtab[findSymbolIndex(operand1)].index) + ")";
                        lc = to_string(locationCounter);
                        locationCounter++;
                    }
                }
            }
            else
            {
                if (opcode == "BC")
                    intermediateCode += "(" + to_string(getConditionCode(operand1)) + ")     ";
                else
                    intermediateCode += "(" + to_string(getRegisterID(operand1)) + ")     ";

                if (operand2[0] == '=') // operand2 is a literal
                {
                    littab[literalCount].index = literalCount + 1;
                    littab[literalCount].name = operand2;
                    literalCount++;
                    undefinedLiteralCount++;
                    intermediateCode += "(L,0" + to_string(littab[findLiteralIndex(operand2)].index) + ")";
                }
                else // operand2 is a symbol
                {
                    if (isSymbolPresent(operand2))
                    {
                        intermediateCode += "(S,0" + to_string(symtab[findSymbolIndex(operand2)].index) + ")";
                    }
                    else
                    {
                        symtab[symbolCount].index = symbolCount + 1;
                        symtab[symbolCount].name = operand2;
                        symbolCount++;
                        intermediateCode += "(S,0" + to_string(symtab[findSymbolIndex(operand2)].index) + ")";
                    }
                }
                lc = to_string(locationCounter);
                locationCounter++;
            }
        }

        cout << "  " << label << "\t" << opcode << "\t" << operand1 << "\t\t" << operand2 << "\t\t" << lc << "\t\t\t" << intermediateCode << endl;
        intermediateCodeFile << lc << "\t" << intermediateCode << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- SYMBOL TABLE --" << endl;
    cout << "\n <INDEX\tNAME\tADDRESS>" << endl;
    for (int i = 0; i < symbolCount; ++i)
    {
        cout << "  " << symtab[i].index << "\t " << symtab[i].name << "\t  " << symtab[i].address << endl;
        symbolTableFile << symtab[i].index << "\t " << symtab[i].name << "\t  " << symtab[i].address << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- LITERAL TABLE --" << endl;
    cout << "\n <INDEX\tNAME\tADDRESS>" << endl;
    for (int i = 0; i < literalCount; ++i)
    {
        cout << "  " << littab[i].index << "\t " << littab[i].name << "\t  " << littab[i].address << endl;
        literalTableFile << littab[i].index << "\t " << littab[i].name << "\t  " << littab[i].address << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- POOL TABLE --" << endl;
    cout << "\n <INDEX\tLITERAL_NUMBER>" << endl;
    for (int i = 0; i < poolCount; ++i)
    {
        cout << "  " << pooltab[i].index << "\t   " << pooltab[i].literal_number << endl;
    }

    return 0;
}
