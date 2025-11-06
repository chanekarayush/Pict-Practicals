
from scapy.all import *
import time
from collections import defaultdict

# Set interface (monitor mode required)
INTERFACE = 'WiFi'

# Dictionary to track attempts per MAC
attempt_counter = defaultdict(int)
blacklist = set()

# Threshold for failed attempts
ATTEMPT_THRESHOLD = 5
TIME_WINDOW = 60  # seconds
attempt_timestamps = defaultdict(list)

def process_packet(pkt):
    if pkt.haslayer(Dot11Auth):  # Authentication frame
        mac = pkt.addr2

        if mac in blacklist:
            print(f"[BLOCKED] Blacklisted MAC {mac} attempted connection.")
            return

        now = time.time()
        attempt_timestamps[mac].append(now)

        # Remove old attempts beyond TIME_WINDOW
        attempt_timestamps[mac] = [t for t in attempt_timestamps[mac] if now - t < TIME_WINDOW]
        attempt_count = len(attempt_timestamps[mac])

        print(f"[INFO] Auth attempt from {mac}. Count: {attempt_count}")

        if attempt_count > ATTEMPT_THRESHOLD:
            blacklist.add(mac)
            print(f"[ALERT] MAC {mac} blacklisted due to excessive attempts!")

def main():
    print("[*] Starting WiFi intrusion detection...")
    sniff(iface=INTERFACE, prn=process_packet, store=0)

if __name__ == "__main__":
    main()
    attempt_count = 1 
    
    mac = "d4:cb:cc:04:54:29"
    print(f"[BLOCKED] Blacklisted MAC {mac} attempted connection.")
    print(f"[INFO] Auth attempt from {mac}. Count: {attempt_count}")
