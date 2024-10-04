import ipaddress
import math

# Function to calculate the number of subnets and IP ranges based on hosts


def calculate_subnets_based_on_hosts(ip_network, num_hosts):
    # Calculate the subnet size that can accommodate the number of hosts
    # Adding 2 for network and broadcast address
    subnet_size = 32 - math.ceil(math.log2(num_hosts + 2))
    subnets = ip_network.subnets(new_prefix=subnet_size)

    print(
        f"\nNumber of Subnets that can accommodate at least {num_hosts} hosts:")

    for idx, subnet in enumerate(subnets, 1):
        print(f"Subnet {idx}: {subnet}")
        first_ip = subnet.network_address + 1  # First usable IP
        last_ip = subnet.broadcast_address - 1  # Last usable IP
        print(f"IP Range: {first_ip} - {last_ip}")

    print()

# Function to calculate subnets based on network division


def calculate_subnets_based_on_networks(ip_network, num_subnets):
    # Calculate the number of bits needed to create the desired number of subnets
    bits_for_subnets = math.ceil(math.log2(num_subnets))
    new_prefix = ip_network.prefixlen + bits_for_subnets
    subnets = ip_network.subnets(new_prefix=new_prefix)

    print(f"\nDividing network into {num_subnets} subnets:")

    for idx, subnet in enumerate(subnets, 1):
        print(f"Subnet {idx}: {subnet}")
        first_ip = subnet.network_address + 1  # First usable IP
        last_ip = subnet.broadcast_address - 1  # Last usable IP
        print(f"IP Range: {first_ip} - {last_ip}")

    print()

# Main program


def subnet_calculator():
    # Taking network address input
    network_address = input(
        "Enter the network address (e.g., 192.168.1.0/24): ")

    try:
        # Create an IP network object
        ip_network_obj = ipaddress.ip_network(network_address)
    except ValueError:
        print("Invalid IP network address.")
        return

    print("\nChoose an option:")
    print("1. Divide based on number of hosts")
    print("2. Divide based on number of subnets")

    choice = input("Enter your choice (1 or 2): ")

    if choice == "1":
        num_hosts = int(input("Enter the number of hosts per subnet: "))
        calculate_subnets_based_on_hosts(ip_network_obj, num_hosts)

    elif choice == "2":
        num_subnets = int(input("Enter the number of subnets: "))
        calculate_subnets_based_on_networks(ip_network_obj, num_subnets)

    else:
        print("Invalid choice!")


# Run the subnet calculator
subnet_calculator()
