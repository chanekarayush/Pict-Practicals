import random
import time

class SelectiveRepeat:
    def __init__(self, window_size, total_frames):
        self.window_size = window_size
        self.total_frames = total_frames
        self.frames = list(range(1, total_frames + 1))
        self.acknowledged = [False] * total_frames

    def send_frames(self):
        print("Starting Selective Repeat Transmission...")
        i = 0
        while i < self.total_frames:
            for j in range(i, min(i + self.window_size, self.total_frames)):
                if not self.acknowledged[j]:
                    print(f"Sending frame {self.frames[j]}")
                    if not self.simulate_error():
                        self.acknowledged[j] = True
                        print(f"Frame {self.frames[j]} successfully received and acknowledged.")
                    else:
                        print(f"Frame {self.frames[j]} lost or corrupted. Retransmitting later.")

            # Slide the window
            while i < self.total_frames and self.acknowledged[i]:
                i += 1

    def simulate_error(self):
        return random.random() < 0.2

window_size = 4
total_frames = 10
sr = SelectiveRepeat(window_size, total_frames)
sr.send_frames()
