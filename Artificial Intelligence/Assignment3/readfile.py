from collections import defaultdict
import logging

adjList = defaultdict(list)

def readfileinput(verbose=False)->defaultdict:
    if verbose:
        logging.getLogger().setLevel(logging.DEBUG)
    else:
        logging.getLogger().setLevel(logging.INFO)
    with open("./input.graph", "r") as file:
        lines = file.readlines()
        line_ctr : int = 0
        for line in lines:
            if line[0] == "#":
                logging.debug(f"skipping comments on line:{line_ctr}")
                line_ctr += 1
                continue
            line : str = line.strip()
            start : int = 0
            src_node : int = 0
            flag = False
            for i, x in enumerate(line):

                if i == 0 and x.isdigit(): 
                    src_node = int(x)
                if x == '(' and not flag:
                    start = i
                    flag = True

                if x == ')' and flag:
                    number_tuple = line[start:i+1].split(',')
                    num1, num2 = number_tuple[0][1:].strip(), number_tuple[-1][:-1].strip()
                    if not num1.isdigit() or not num2.isdigit():
                        logging.info("The numbers inside the tuple are not in the correct format. \n",f"This error occured on line:{line_ctr}\nposition:{i}\nword:{x}...")
                        logging.debug(f"This is what the program read num1:{num1}\tnum2:{num2}")
                        exit(1)
                    adjList[src_node].append((int(num1), int(num2))) 
                    flag = False
                    start = 0
            if flag:
                logging.debug(f"There is a bracket which has not been closed on line:{line_ctr}")
                exit(1)
            if start != 0:
                logging.debug(f"A bracket was left open on line:{line_ctr}")

            line_ctr += 1
    logging.info("Completed Reading File")
    return adjList

