import os
domain_name = input("Enter domain name or ip address:")

x = domain_name.split('.')
x = x[1:]
for val in x:
    if not val.isalpha:
        break
    print(f'Searching for domain .{val}...')
query = f'nslookup {domain_name}'
os.system(query)
exit(0)
