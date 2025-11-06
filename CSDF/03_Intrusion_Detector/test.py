# Add this at the bottom to simulate a packet
from scapy.all import Dot11, Dot11Auth, RadioTap
import time
from collections import defaultdict
import random

attempt_timestamps = defaultdict(list)
ATTEMPT_THRESHOLD = 4
TIME_WINDOW = 10


blacklist = set()


def process_packet(pkt):
    if pkt.haslayer(Dot11Auth):  # Check if it's an authentication frame
        mac = pkt.addr2  # Source MAC address

        if mac in blacklist:
            print(f"[BLOCKED] Blacklisted MAC {mac} attempted connection.")
            return

        now = time.time()
        attempt_timestamps[mac].append(now)

        # Remove timestamps older than TIME_WINDOW
        attempt_timestamps[mac] = [t for t in attempt_timestamps[mac] if now - t < TIME_WINDOW]
        attempt_count = len(attempt_timestamps[mac])

        print(f"[INFO] Auth attempt from {mac}. Count: {attempt_count}")

        if attempt_count > ATTEMPT_THRESHOLD:
            blacklist.add(mac)
            print(f"[ALERT] MAC {mac} blacklisted due to excessive attempts!")


def simulate_packet(mac):
    pkt = RadioTap() / Dot11(type=0, subtype=11, addr2=mac) / Dot11Auth()
    process_packet(pkt)



def generate_random_mac():
    return ":".join(f"{random.randint(0x00, 0xFF):02x}" for _ in range(6))

if __name__ == "__main__":
    print("=" * 50)
    print("Simulating Wi-Fi Authentication Attempts")
    print("=" * 50)

    total_devices = 3 

    for device_num in range(1, total_devices + 1):
        mac = generate_random_mac()
        num_attempts = random.randint(3, 6)

        print(f"\nDevice {device_num}: MAC {mac}")
        print(f"↪️Simulating {num_attempts} authentication attempts...\n")

        for attempt in range(1, num_attempts + 1):
            print(f"    Attempt {attempt}/{num_attempts} from {mac}")
            simulate_packet(mac)
            time.sleep(0.5)  # Reduced sleep for faster simulation

        print("-" * 50)

    print("\nSimulation complete.")
    print("=" * 50)
