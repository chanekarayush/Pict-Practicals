def split_file_after_start(file_path, output_path1, output_path2, output_path3="assignment-3/try2/Pass-1/output/intermediate_code.asm"):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    # Find the index where `START` is located
    start_index = None
    for i, line in enumerate(lines):
        if 'START' in line:
            start_index = i
            break
    
    if start_index is None:
        raise ValueError("START not found in the file.")
    
    # Write the first part of the file (up to and including `START`)
    with open(output_path1, 'w') as file1:
        file1.writelines(lines[:start_index + 1])
    
    # Write the second part of the file (after `START`)
    with open(output_path2, 'w') as file2:
        file2.writelines(lines[start_index:])
    
    with open(output_path3, 'w') as file3:
        file3.writelines(lines[start_index:])
    
    # print(f"File split into {output_path1} and {output_path2}")


