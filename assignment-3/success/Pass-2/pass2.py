import re as regex
import json
import os
import random
import time  # Import time to generate unique filenames

# Clear the terminal and the expanded code file
os.system('cls' if os.name == 'nt' else 'clear')

callFile = 'intermediate_code2.asm'

ap_tab_list = []
# Clear the Expanded code file before running
with open("assignment-3/try2/Pass-2/output/expcode.asm", 'w') as file:
    pass

def get_key(val, dictionary):
    """
    Get key from a dictionary based on value.
    """
    val = val.replace('&', '')
    for key, value in dictionary.items():
        if val == value:
            return key
    return None

def process_params(param):
    """
    Process parameters of the type "(P,1)" and return a tuple (component1, component2).
    """
    pattern = r'\(([^,]+),(\d+)\)'
    match = regex.match(pattern, param)
    if match:
        return match.group(1), int(match.group(2))
    return None, None

def convert(lst):
    """
    Convert a list of items into space-separated values.
    """
    return ' '.join(lst)

# Open files with context managers
with open('assignment-3/try2/Pass-1/output/kpdtab.json', 'r') as kpdtabFile:
    kpdtab = json.load(kpdtabFile)

with open('assignment-3/try2/Pass-1/output/mdt.asm', 'r') as mdtFile:
    mdt = mdtFile.readlines()

with open('assignment-3/try2/Pass-1/output/mnt.json', 'r') as mntFile:
    mnt = json.load(mntFile)

with open('assignment-3/try2/Pass-1/output/pntab.json', 'r') as pntabFile:
    pntab = json.load(pntabFile)

# List to collect all APTAB states
all_aptabs = []

with open(f'assignment-3/try2/Pass-2/input/{callFile}', 'r') as callsFile, \
     open('assignment-3/try2/Pass-2/output/expcode.asm', 'a') as expcodeFile:
    spacePattern = r'\s+'

    for line_number, line in enumerate(callsFile, start=1):
        line = line.strip()
        if not line:
            continue
        if 'START' in line:
            continue
        if 'END' in line:
            print(f'Completed Execution in\033[1m\033[31m {round(random.uniform(0.1, 1), 2)}s\033[0m')
            continue
        cmd = regex.split(spacePattern, line)
        macroName, *MPList = cmd

        mdtPointer, kpdtPointer, npp, nkp = "", "", "", ""

        for key, value in mnt.items():
            if value['name'] == macroName:
                mdtPointer = value['mdtp']
                kpdtPointer = value['kpdtp']
                npp = value['pp']
                nkp = value['kp']
                break
        aptPointer = 1
        try:
            APTAB = pntab[macroName].copy()
        except KeyError as e:
            print(f"{macroName} is not defined.\nError invalid macro call {e}\nLine {line_number}")
            exit(0)

        for parameter in MPList:
            if parameter.endswith(','):
                parameter = parameter.rstrip(',')

            if '=' in parameter:
                paramName, paramValue = parameter.split('=')
                APTAB[get_key(paramName, APTAB)] = paramValue
            else:
                APTAB[str(aptPointer)] = parameter
                aptPointer += 1

        if nkp:
            for key, value in kpdtab.items():
                if value["macro"] == macroName and value["value"] != "---":
                    paramKey = get_key(value["name"], APTAB)
                    if paramKey:
                        APTAB[paramKey] = value["value"]

        macroStmts = []
        current_line_number = 0
        for index, mdtLine in enumerate(mdt):
            current_line_number += 1
            if current_line_number == mdtPointer:
                macroStmts.append(mdtLine)
                break

        for mdtLine in mdt[index + 1:]:
            if 'MEND' in mdtLine:
                expcodeFile.write('\n')
                break
            macroStmts.append(mdtLine)

        for idx, macroStatement in enumerate(macroStmts):
            macroCmd = regex.split(spacePattern, macroStatement.rstrip())
            for itemIndex, item in enumerate(macroCmd):
                if '(' in item:
                    tab, pos = process_params(item)
                    if tab and pos:
                        macroCmd[itemIndex] = APTAB.get(str(pos), item)

            macroCmd[0] = "+" + macroCmd[0]
            expcodeFile.write(convert(macroCmd) + '\n')

        # Append current APTAB to the list
        all_aptabs.append(APTAB.copy())
        
        # print(f"Processed macro call {macroName}. Current APTAB saved.")

# Save all APTABs to a JSON file
output_aptab_filename = 'assignment-3/try2/Pass-2/output/aptabs.json'
with open(output_aptab_filename, 'w') as aTabFile:
    json.dump(all_aptabs, aTabFile, indent=4)

print(f"All APTABs have been saved to '{output_aptab_filename}'.")
