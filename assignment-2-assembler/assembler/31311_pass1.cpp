/**
 * @file assembler.cpp
 * @brief Two-Pass Assembler: Pass-1 Implementation
 * 
 * This file contains the implementation of the first pass of a two-pass assembler. It reads assembly code, processes it, and generates intermediate code, symbol table, literal table, and pool table.
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * @struct OPtab
 * @brief Structure to store opcode information.
 * 
 * This structure holds details about each opcode, including its mnemonic and class.
 */
struct OPtab
{
    string opcode; ///< The operation code (mnemonic) for the instruction.
    string mclass; ///< The class of the opcode (IS for Imperative Statements, AD for Assembly Directives, DL for Declarative Statements).
    string mnemonic; ///< The numeric representation of the opcode.
};

// Hard-coded opcode table
struct OPtab optab[18] = {
    {"STOP", "IS", "00"},
    {"ADD", "IS", "01"},
    {"SUB", "IS", "02"},
    {"MULT", "IS", "03"},
    {"MOVER", "IS", "04"},
    {"MOVEM", "IS", "05"},
    {"COMP", "IS", "06"},
    {"BC", "IS", "07"},
    {"DIV", "IS", "08"},
    {"READ", "IS", "09"},
    {"PRINT", "IS", "10"},
    {"START", "AD", "01"},
    {"END", "AD", "02"},
    {"ORIGIN", "AD", "03"},
    {"EQU", "AD", "04"},
    {"LTORG", "AD", "05"},
    {"DC", "DL", "01"},
    {"DS", "DL", "02"}};

/**
 * @brief Fetch the opcode entry from the opcode table.
 * @param s The mnemonic of the opcode.
 * @return The index of the opcode entry in the table, or -1 if not found.
 */
int getOP(string s)
{
    for (int i = 0; i < 18; ++i)
    {
        if (optab[i].opcode == s)
            return i;
    }
    return -1;
}

/**
 * @brief Fetch the register code based on the register name.
 * @param s The name of the register (AREG, BREG, CREG, DREG).
 * @return The code corresponding to the register, or -1 if not found.
 */
int getRegID(string s)
{
    if (s == "AREG")
        return 1;
    else if (s == "BREG")
        return 2;
    else if (s == "CREG")
        return 3;
    else if (s == "DREG")
        return 4;
    else
        return (-1);
}

/**
 * @brief Fetch the conditional code based on the condition.
 * @param s The condition code (LT, LE, EQ, GT, GE, ANY).
 * @return The numeric code for the condition, or -1 if not found.
 */
int getConditionCode(string s)
{
    if (s == "LT")
        return 1;
    else if (s == "LE")
        return 2;
    else if (s == "EQ")
        return 3;
    else if (s == "GT")
        return 4;
    else if (s == "GE")
        return 5;
    else if (s == "ANY")
        return 6;
    else
        return (-1);
}

/**
 * @struct symTable
 * @brief Structure to store symbol table entries.
 * 
 * This structure holds information about each symbol, including its number, name, and address.
 */
struct symTable
{
    int no; ///< The number assigned to the symbol.
    string sname; ///< The name of the symbol.
    string addr; ///< The address associated with the symbol.
};

struct symTable ST[10];

/**
 * @brief Check if a symbol is present in the symbol table.
 * @param s The name of the symbol to check.
 * @return True if the symbol is present, false otherwise.
 */
bool presentST(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (ST[i].sname == s)
            return true;
    }
    return false;
}

/**
 * @brief Fetch the symbol entry from the symbol table.
 * @param s The name of the symbol.
 * @return The index of the symbol entry in the table, or -1 if not found.
 */
int getSymID(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (ST[i].sname == s)
            return i;
    }
    return (-1);
}

/**
 * @struct litTable
 * @brief Structure to store literal table entries.
 * 
 * This structure holds information about each literal, including its number, name, and address.
 */
struct litTable
{
    int no; ///< The number assigned to the literal.
    string lname; ///< The name (or value) of the literal.
    string addr; ///< The address associated with the literal.
};

struct litTable LT[10];

/**
 * @brief Check if a literal is present in the literal table.
 * @param s The name (or value) of the literal to check.
 * @return True if the literal is present, false otherwise.
 */
bool presentLT(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (LT[i].lname == s)
            return true;
    }
    return false;
}

/**
 * @brief Fetch the literal entry from the literal table.
 * @param s The name (or value) of the literal.
 * @return The index of the literal entry in the table, or -1 if not found.
 */
int getLitID(string s)
{
    for (int i = 0; i < 10; ++i)
    {
        if (LT[i].lname == s)
            return i;
    }
    return (-1);
}

/**
 * @struct poolTable
 * @brief Structure to store pool table entries.
 * 
 * This structure holds information about each pool table entry, including its number and the literal number.
 */
struct poolTable
{
    int no; ///< The number assigned to the pool table entry.
    string lno; ///< The literal number associated with the pool table entry.
};

struct poolTable PT[10];

/**
 * @brief Main function to process the assembly code and generate intermediate code, symbol table, literal table, and pool table.
 * 
 * This function reads the assembly code from an input file, processes each line according to the opcode, directives, and operands, and generates the required tables and intermediate code.
 */
int main()
{
    ifstream fin;
    fin.open("input3.txt");

    ofstream ic, st, lt;
    const char *path1 = "ic.txt"; ///< Path for the intermediate code output file.
    const char *path2 = "symtable.txt"; ///< Path for the symbol table output file.
    const char *path3 = "littable.txt"; ///< Path for the literal table output file.
    ic.open(path1);
    st.open(path2);
    lt.open(path3);

    string label, opcode, op1, op2;
    int scnt = 0, lcnt = 0, nlcnt = 0, pcnt = 0, LC = 0;

    cout << "\n -- ASSEMBLER PASS-1 OUTPUT --" << endl;
    cout << "\n <LABEL\tOPCODE\t\tOP1\t\tOP2\t\tLC\t\t\tINTERMEDIATE CODE>" << endl;

    /**
     * @brief Main processing loop for reading and processing each line of assembly code.
     * 
     * This loop continues until the end of the input file is reached. It reads each line, processes the opcode,
     * updates the symbol table, literal table, and intermediate code based on the assembly instructions.
     */
    while (!fin.eof())
    {
        fin >> label >> opcode >> op1 >> op2; // Reading the assembly code line by line
        int id;
        string IC, lc; // lc - LC processing, IC - Intermediate code

        id = getOP(opcode); // Fetch the opcode entry
        IC = "(" + optab[id].mclass + "," + optab[id].mnemonic + ") ";

        // Processing for Assembly Directives (AD)
        if (opcode == "START")
        {
            lc = "---";
            if (op1 != "NAN")
            {
                LC = stoi(op1);
                IC += "(C," + op1 + ")  NAN";
            }
        }

        /**
         * @brief Handle EQU directive.
         * 
         * The EQU directive defines a constant value for a symbol. This section updates the symbol table with the 
         * address of the symbol being defined and sets its value to the address of the symbol referenced.
         */
        if (opcode == "EQU")
        {
            lc = "---";
            IC += " NAN     NAN";
            if (presentST(label))
            {
                ST[getSymID(label)].addr = ST[getSymID(op1)].addr;
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = ST[getSymID(op1)].addr;
                scnt++;
            }
        }
        else if (label != "NAN")
        {
            /**
             * @brief Update the symbol table with the address of a new label.
             * 
             * When a label is encountered, this section checks if the label is already in the symbol table. If not,
             * it adds the label with its address.
             */
            if (presentST(label))
            {
                ST[getSymID(label)].addr = to_string(LC);
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = to_string(LC);
                scnt++;
            }
        }

        // Handling ORIGIN directive
        if (opcode == "ORIGIN")
        {
            string token1, token2;
            char op;
            stringstream ss(op1);
            size_t found = op1.find('+');
            if (found != string::npos)
                op = '+';
            else
                op = '-';
            getline(ss, token1, op);
            getline(ss, token2, op);
            lc = "---";
            if (op == '+')
            {
                LC = stoi(ST[getSymID(token1)].addr) + stoi(token2);
                IC += "(S,0" + to_string(ST[getSymID(token1)].no) + ")+" + token2 + " NAN";
            }
            else
            {
                LC = stoi(ST[getSymID(token1)].addr) - stoi(token2);
                IC += "(S,0" + to_string(ST[getSymID(token1)].no) + ")-" + token2 + " NAN";
            }
        }

        /**
         * @brief Process LTORG directive.
         * 
         * The LTORG directive handles literal table entries. This loop processes all literals that have been collected
         * but not yet outputted, assigns them addresses, and writes them to the intermediate code. It also updates the 
         * pool table with the current literal pool.
         */
        if (opcode == "LTORG")
        {
            cout << "  " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t\t";
            for (int i = lcnt - nlcnt; i < lcnt; ++i)
            {
                lc = to_string(LC);
                IC = "(DL,01) (C,";
                string c(1, LT[i].lname[2]);
                IC += c + ")    NAN";
                LT[i].addr = to_string(LC);
                LC++;
                if (i < lcnt - 1)
                    cout << lc << "\t" << IC << "\n\t\t\t\t";
                else
                    cout << lc << "\t" << IC << endl;
                ic << lc << "\t" << IC << endl;
            }
            // Managing pool table in LTORG
            PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);
            PT[pcnt].no = pcnt + 1;
            pcnt++;
            nlcnt = 0;
            continue;
        }

        /**
         * @brief Process END directive.
         * 
         * The END directive finalizes the assembly process. This section outputs the remaining literals in the literal table
         * and updates the pool table if needed. The loop processes any remaining literals and updates their addresses.
         */
        if (opcode == "END")
        {
            lc = "---";
            IC += " NAN     NAN";
            cout << "  " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t\t" << lc << "\t\t\t" << IC << endl;
            ic << lc << "\t" << IC << endl;
            if (nlcnt)
            {
                for (int i = lcnt - nlcnt; i < lcnt; ++i)
                {
                    lc = to_string(LC);
                    IC = "(DL,01) (C,";
                    string c(1, LT[i].lname[2]);
                    IC += c + ")    NAN";
                    LT[i].addr = to_string(LC);
                    LC++;
                    cout << "\t\t" << lc << "\t\t" << IC << endl;
                    ic << lc << "\t" << IC << endl;
                }
                // Managing pool table after END (if any literals are left)
                PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no);
                PT[pcnt].no = pcnt + 1;
                pcnt++;
            }
            break;
        }

        // Declarative Statements (DL)
        if (opcode == "DC" || opcode == "DS")
        {
            lc = to_string(LC);
            if (opcode == "DS")
            {
                IC += "(C," + op1 + ")    NAN";
                LC += stoi(op1);
            }
            else
            {
                string c(1, op1[1]);
                IC += "(C," + c + ")";
                LC++;
            }
        }

        /**
         * @brief Process Imperative Statements (IS).
         * 
         * This section handles all imperative statements not previously handled by other conditions. It updates the
         * intermediate code based on the operands and whether they are symbols or literals. The addresses of symbols
         * and literals are updated accordingly.
         */
        if (opcode != "START" && opcode != "END" && opcode != "ORIGIN" && opcode != "EQU" && opcode != "LTORG" && opcode != "DC" && opcode != "DS")
        {
            if (op2 == "NAN")
            {
                if (op1 == "NAN")
                {
                    lc = to_string(LC);
                    LC++;
                    IC += " NAN     NAN";
                }
                else
                {
                    if (presentST(op1))
                    {
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no) + ")";
                        lc = to_string(LC);
                        LC++;
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op1;
                        scnt++;
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no) + ")";
                        lc = to_string(LC);
                        LC++;
                    }
                }
            }
            else
            {
                if (opcode == "BC")
                    IC += "(" + to_string(getConditionCode(op1)) + ")     ";
                else
                    IC += "(" + to_string(getRegID(op1)) + ")     ";

                if (op2[0] == '=') // operand2 is a literal
                {
                    LT[lcnt].no = lcnt + 1;
                    LT[lcnt].lname = op2;
                    lcnt++;
                    nlcnt++;
                    IC += "(L,0" + to_string(LT[getLitID(op2)].no) + ")";
                }
                else // operand2 is a symbol
                {
                    if (presentST(op2))
                    {
                        IC += "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op2;
                        scnt++;
                        IC += "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                    }
                }
                lc = to_string(LC);
                LC++;
            }
        }

        // Console output
        cout << "  " << label << "\t" << opcode << "\t\t" << op1 << "\t\t" << op2 << "\t" << lc << "\t\t" << IC << endl;
        ic << lc << "\t" << IC << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- SYMBOL TABLE --" << endl;
    cout << "\n <NO.\tSYMBOL\tADDRESS>" << endl;
    for (int i = 0; i < scnt; ++i)
    {
        cout << "  " << ST[i].no << "\t " << ST[i].sname << "\t  " << ST[i].addr << endl;
        st << ST[i].no << "\t " << ST[i].sname << "\t  " << ST[i].addr << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- LITERAL TABLE --" << endl;
    cout << "\n <NO.\tLITERAL\tADDRESS>" << endl;
    for (int i = 0; i < lcnt; ++i)
    {
        cout << "  " << LT[i].no << "\t " << LT[i].lname << "\t  " << LT[i].addr << endl;
        lt << LT[i].no << "\t " << LT[i].lname << "\t  " << LT[i].addr << endl;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- POOL TABLE --" << endl;
    cout << "\n <NO.\tLITERAL_NO.>" << endl;
    for (int i = 0; i < pcnt; ++i)
    {
        cout << "  " << PT[i].no << "\t   " << PT[i].lno << endl;
    }

    return 0;
}
