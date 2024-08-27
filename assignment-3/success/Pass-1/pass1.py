import re as regex
import json
import os
import ic_split as icFile
# Clear the terminal before starting the program
os.system('cls' if os.name == 'nt' else 'clear')

file_path = 'assignment-3/try2/Pass-1/input/program2.asm'  
output_path1 = 'assignment-3/try2/Pass-1/input/intermediateip.asm'       
output_path2 = 'assignment-3/try2/Pass-2/input/intermediate_code2.asm'       

icFile.split_file_after_start(file_path, output_path1, output_path2)

def get_key(val: str, dict: dict) -> any:
    """
    Function to get key from a dictionary based on value
    """
    for key, value in dict.items():
        if val == value:
            return key
    return None

# Create the MDT file
with open("assignment-3/try2/Pass-1/output/mdt.asm", 'w') as file:
    pass

# Input File(s)
try:
    with open(output_path1, 'r') as inputFile:
        # Output File(s)
        with open('assignment-3/try2/Pass-1/output/mdt.asm', 'a') as mdtFile:
            # Regex pattern to split on occurrence of one or more spaces
            pattern = r'\s+'

            # Flags
            mSign = False
            mDef = False

            # Tables
            mnt = {}
            pntab = {}
            kpdtab = {}

            # Storage variables
            macroName = ""
            kpdtabIndex = 1
            kpdtabLoc = 1
            mntIndex = 1
            mdtLoc = 1

            # Loop through lines in file
            for line in inputFile:
                # Skip blank lines and remove beginning and trailing whitespace(s)
                if line.strip() == '':
                    continue

                line = line.strip()
                # Split the line into words
                cmd = regex.split(pattern, line.rstrip())

                # When 'MACRO' is encountered, set the macro signature flag
                if len(cmd) == 1 and cmd[0] == 'MACRO':
                    mSign = True
                    continue

                # If macro definition has been encountered, process its right next line
                if mSign:
                    macroName = cmd.pop(0)
                    pntab[macroName] = {}
                    paramCnt = 0
                    pp = 0
                    kp = 0

                    # Now, cmd contains the list of all the parameters
                    for parameter in cmd:
                        if ',' in parameter:
                            parameter = parameter.replace(',', '')

                        if '&' in parameter and '=' not in parameter:
                            paramCnt += 1
                            pp += 1
                            paramName = parameter[1:]
                            pntab[macroName][paramCnt] = paramName

                        elif '&' in parameter and '=' in parameter:
                            paramCnt += 1

                            if kp == 0:
                                kpdtabLoc = kpdtabIndex

                            kp += 1

                            # Get the index of the '=' sign and
                            eqIndex = parameter.index('=')

                            paramName = parameter[1:eqIndex]
                            paramDefValue = parameter[eqIndex + 1:] or '---'

                            pntab[macroName][paramCnt] = paramName

                            kpdtab[kpdtabIndex] = {
                                'macro': macroName,
                                'index': kpdtabIndex,
                                'name': paramName,
                                'value': paramDefValue,
                            }

                            kpdtabIndex += 1

                        else:
                            pass

                    mSign = False
                    mDef = True
                    mnt[mntIndex] = {
                        'index': mntIndex,
                        'name': macroName,
                        'pp': pp,
                        'kp': kp,
                        'mdtp': mdtLoc,
                        'kpdtp': kpdtabLoc if kp else '---',
                    }
                    mntIndex += 1
                    continue

                if mDef:
                    mdtLoc += 1
                    callLine = ""

                    for command in cmd:
                        if ',' in command:
                            command = command.replace(',', '')
                        if '&' in command:
                            replParamValue = f'(P,{get_key(command[1:], pntab[macroName])})'
                            callLine += replParamValue + " "
                        else:
                            callLine += command + " "

                    mdtFile.write(callLine.strip() + '\n')
                    continue

                if len(cmd) == 1 and cmd[0] == 'MEND':
                    mdtLoc += 1
                    mDef = False
                    mdtFile.write('MEND\n')
                    continue

            # Write tables to JSON files
            with open('assignment-3/try2/Pass-1/output/mnt.json', 'w') as json_file:
                json.dump(mnt, json_file, indent=4)

            with open('assignment-3/try2/Pass-1/output/pntab.json', 'w') as json_file:
                json.dump(pntab, json_file, indent=4)

            with open('assignment-3/try2/Pass-1/output/kpdtab.json', 'w') as json_file:
                json.dump(kpdtab, json_file, indent=4)

except FileNotFoundError as e:
    print(f"File error: {e}")
except json.JSONDecodeError as e:
    print(f"JSON decode error: {e}")
except Exception as e:
    print(f"An error occurred: {e}")

if os.path.exists(output_path1):
    os.remove(output_path1)