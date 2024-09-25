def get_block_input():
    n  = int(input("Enter number of memory block(s): "))
    block_size = list(map(int, input("Enter the size of memory blocks").split()))

    block_size = block_size*n if len(block_size) == 1 else block_size
    if len(block_size) < n:
        print("Please enter a valid input!")
        exit(1)
    return block_size

def get_process_input():
    n = int(input("Enter the number of processes: "))
    proc_size = list(map(int, input("Enter the size of processes").split()))
    proc_size = proc_size*n if len(proc_size) == 1 else proc_size
    if len(proc_size) < n:
        print("Please enter a valid input!")
        exit(1)
    return proc_size

def first_fit(block_size: list, proc_size: list) -> list:
    allotted_blocks = [-1]*len(block_size)
    fragementation = [0]* len(block_size)
    for i in range(len(proc_size)):
        for j in range(len(block_size)):
            if block_size[j] >= proc_size[i]:
                allotted_blocks[i] = j
                fragementation[i] = block_size[j] - proc_size[i]
                block_size[j] -= proc_size[i]
                break
    return [fragementation, allotted_blocks, block_size, proc_size]

def best_fit(block_size: list, proc_size: list):
    allotted_blocks = [0]*len(block_size)
    fragementation = [0]* len(block_size)
    for i in range(len(proc_size)):
        temp = -1
        for j in range(len(block_size)):
            if block_size[j] >= proc_size[i]:
                if temp == -1:
                    temp = j
                elif block_size[temp] > block_size[j]:
                    temp = j
        
        if temp != -1:
            allotted_blocks[i] = temp
            fragementation[i] = block_size[temp] - proc_size[i]
            block_size -= proc_size[i]
    
    return [fragementation, allotted_blocks, block_size, proc_size]

def worst_fit(block_size: list, proc_size: list) -> list:
    allotted_blocks = [0]*len(block_size)
    fragementation = [0]* len(block_size)
    for i in range(len(proc_size)):
        temp = -1
        for j in range(len(block_size)):
            if block_size[j] >= proc_size[i]:
                if temp == -1:
                    temp = j
                elif block_size[temp] < block_size[j]:
                    temp = j
        
        if temp != -1:
            allotted_blocks[i] = temp
            fragementation[i] = block_size[temp] - proc_size[i]
            block_size -= proc_size[i]
    
    return [fragementation, allotted_blocks, block_size, proc_size]
            
# Python3 program for next fit
# memory management algorithm

# Function to allocate memory to
# blocks as per Next fit algorithm
def next_fit(block_size, m, proc_size, n):
		
	# Stores block id of the block
	# allocated to a process

	# Initially no block is assigned
	# to any process
	allocation = [-1] * n
	j = 0
	t = m-1
	for i in range(n):

		# Do not start from beginning
		while j < m:
			if block_size[j] >= proc_size[i]:
				
				# allocate block j to p[i] process
				allocation[i] = j
				
				# Reduce available memory in this block.
				block_size[j] -= proc_size[i]
				
				# sets a new end point
				t = (j - 1) % m
				break
			if t == j:
				# sets a new end point
				t = (j - 1) % m
				# breaks the loop after going through all memory block
				break
			
			# mod m will help in traversing the
			# blocks from starting block after
			# we reach the end.
			j = (j + 1) % m
			


                
