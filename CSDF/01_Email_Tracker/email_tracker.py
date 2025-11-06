import re
from email import message_from_string
from email.utils import parsedate_to_datetime
import sys

def extract_email_header_details(header_raw):
    msg = message_from_string(header_raw)

    # Extract all 'Received' headers
    received_headers = msg.get_all('Received', [])
    print("Received Headers (routing path):")
    for i, received in enumerate(received_headers[::-1], 1):
        print(f"  Hop {i}: {received}")

    # Try to find originating IP address from the earliest Received header
    origin_ip = None
    if received_headers:
        first_hop = received_headers[-1]
        ip_match = re.search(r'\[?(\d{1,3}(?:\.\d{1,3}){3})\]?', first_hop)
        if ip_match:
            origin_ip = ip_match.group(1)
            print(f"\nPossible originating IP address: {origin_ip}")
        else:
            print("\nCould not determine originating IP address.")

    # Extract sender, recipient, subject, and date
    from_addr = msg.get('From', 'N/A')
    to_addr = msg.get('To', 'N/A')
    subject = msg.get('Subject', 'N/A')
    date = msg.get('Date', 'N/A')

    print(f"\nFrom: {from_addr}")
    print(f"To: {to_addr}")
    print(f"Subject: {subject}")
    print(f"Date: {date}")

    try:
        date_obj = parsedate_to_datetime(date)
        print(f"Parsed Date: {date_obj.isoformat()}")
    except Exception:
        print("Date parsing failed.")

    # Check for SPF/DKIM/DMARC authentication results
    for header in ['Authentication-Results', 'Received-SPF']:
        auth_result = msg.get(header)
        if auth_result:
            print(f"\n{header}: {auth_result}")

    print("\n--- Header analysis complete ---")

def main():
    if len(sys.argv) != 2:
        print("Usage: python email_header_analyzer.py <header_file.txt>")
        sys.exit(1)

    file_path = sys.argv[1]

    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            header_raw = f.read()
            extract_email_header_details(header_raw)
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    except Exception as e:
        print(f"Error reading file: {e}")

if __name__ == "__main__":
    main()

