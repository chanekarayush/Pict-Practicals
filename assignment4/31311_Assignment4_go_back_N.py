import random

class GoBackN:
    def __init__(self, window_size, total_frames):
        self.window_size = window_size
        self.total_frames = total_frames
        self.frames = list(range(1, total_frames + 1))
        self.sent_frames = []
        self.acknowledged = []

    def send_frames(self):
        print("Starting Go-Back-N Transmission...")
        i = 0
        while i < len(self.frames):
            self.sent_frames = self.frames[i:i + self.window_size]
            print(f"Sending frames: {self.sent_frames}")

            for frame in self.sent_frames:
                if self.simulate_error():
                    print(f"Frame {frame} lost or corrupted. Resending from frame {frame}.")
                    break
                else:
                    self.acknowledged.append(frame)
                    print(f"Frame {frame} successfully received.")

            # Move the window to the next unacknowledged frame
            i = len(self.acknowledged)

    def simulate_error(self):
        return random.random() < 0.2

window_size = 4
total_frames = 10
gbn = GoBackN(window_size, total_frames)
gbn.send_frames()
