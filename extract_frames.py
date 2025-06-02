import os
import subprocess
import sys

def check_ffmpeg():
    try:
        subprocess.run(['ffmpeg', '-version'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        return True
    except FileNotFoundError:
        return False

def create_directories(output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
        print(f"Created directory: {output_dir}")

def extract_frames(video_path, output_dir, fps):
    if not os.path.exists(video_path):
        print(f"Error: Video file not found at {video_path}")
        return False

    create_directories(output_dir)
    
    command = ['ffmpeg', '-i', video_path]
    command.extend(['-r', str(fps)])
    command.append(os.path.join(output_dir, 'BA_%05d.png'))
    
    print("Executing command:", ' '.join(command))
    
    try:
        subprocess.run(command, check=True)
        print(f"Successfully extracted frames to {output_dir}")
        return True
    except subprocess.CalledProcessError as e:
        print(f"Error extracting frames: {e}")
        return False

if __name__ == "__main__":
    video_path = 'bad_apple.mp4'
    output_dir = './BA_frame/png'
    fps = 30

    if not check_ffmpeg():
        print("Error: ffmpeg is not installed or not in PATH. Please install ffmpeg first.")
        print("Installation instructions:")
        print("  - Ubuntu/Debian: sudo apt-get install ffmpeg")
        print("  - Fedora: sudo dnf install ffmpeg")
        print("  - macOS: brew install ffmpeg")
        print("  - Windows: Download from https://ffmpeg.org/download.html")
        sys.exit(1)
    
    frame = extract_frames(video_path, output_dir, fps)
    
    if frame:
        print("Frame extraction completed successfully.")
        print("Next steps:")
        print("1. Run 'python frame.py' to convert frames to ASCII art")
        print("2. Compile and run main.cpp to play the animation")
    else:
        print("Frame extraction failed.")
