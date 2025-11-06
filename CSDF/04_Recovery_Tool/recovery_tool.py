import ctypes
import sys
import os
import subprocess

def is_admin():
    try:
        return ctypes.windll.shell32.IsUserAnAdmin()
    except:
        return False

if not is_admin():
    print("Requesting admin privileges...")
    ctypes.windll.shell32.ShellExecuteW(
        None, "runas", sys.executable, " ".join(sys.argv), None, 1)
    sys.exit()

def recover_from_partition(drive_path, partition_number, output_folder):
    photorec_exe = r"C:\ProgramData\chocolatey\lib\testdisk-photorec\tools\testdisk-7.2\photorec_win.exe"

    if not os.path.exists(photorec_exe):
        raise FileNotFoundError(f"PhotoRec not found at: {photorec_exe}")

    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    cmd = [
        photorec_exe,
        "/log",
        "/d", output_folder,
        "/cmd",
        drive_path, partition_number, "search"  # ✅ FIXED this line
    ]

    print("Running PhotoRec recovery...")
    subprocess.run(cmd)
    print("Recovery done. Check:", output_folder)

if __name__ == "__main__":
    drive = r"\\.\PhysicalDrive1"  # Confirm using diskpart
    partition = "1"
    output = os.path.expanduser("~/Downloads")

    recover_from_partition(drive, partition, output)

