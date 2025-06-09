# Bad Apple ASCII Player

A terminal-based Bad Apple video ASCII art player. This project converts the famous Bad Apple!! music video into text art and plays it in the terminal with synchronized music.

![Bad Apple ASCII Example](https://via.placeholder.com/800x400)

## Overview

This project consists of three main components:

1. Video frame extraction (extract_frames.py)
2. Frame conversion to ASCII art (frame.py)
3. Terminal playback with music (main.cpp)

## Requirements

### Common Requirements

- ffmpeg (for frame extraction)

### Python Dependencies

- Python 3.8+
- NumPy 2.1.3+
- Pillow 11.0.0+

### C++ Dependencies

- C++17 compatible compiler
- SFML library (for audio playback)

## Installation

1. Clone the repository

   ```bash
   git clone https://github.com/reimunyancat/bad-apple-ascii.git
   cd bad-apple-ascii
   ```

2. Set up Python virtual environment (optional)

   ```bash
   python -m venv venv
   source venv/bin/activate  # Linux/Mac
   # or
   venv\Scripts\activate  # Windows
   ```

3. Install Python dependencies

   ```bash
   pip install -r requirements.txt
   ```

4. Install ffmpeg

   - Arch Linux: `sudo pacman -S ffmpeg`
   - Ubuntu: `sudo apt-get install ffmpeg`
   - macOS: `brew install ffmpeg`
   - Windows: Download from [ffmpeg download page](https://ffmpeg.org/download.html)

5. Install SFML

   - Arch Linux: `sudo pacman -S sfml`
   - Ubuntu: `sudo apt-get install libsfml-dev`
   - macOS: `brew install sfml`
   - Windows: Download from [SFML download page](https://www.sfml-dev.org/download.php)

## Usage

### 1. Extract Frames from Video

```bash
python extract_frames.py bad_apple.mp4
```

### 2. Convert Frames to ASCII Art

```bash
python frame.py
```

### 3. Run the Player

Compile and run the C++ program:

```bash
g++ -std=c++17 main.cpp -o main -lsfml-audio -lsfml-system -lsfml-graphics -lsfml-window
./main
```

## Project Structure

```
.
├── extract_frames.py     # Script to extract PNG frames from video
├── frame.py              # Script to convert PNG images to ASCII text
├── main.cpp              # C++ program to play ASCII art in terminal with music
├── requirements.txt      # Python dependencies list
├── BA_frame/             # Frame storage directory
│   ├── png/              # Original PNG frames (auto-generated)
│   └── txt/              # Converted ASCII frames (auto-generated)
└── bad_apple.mp3         # Audio file
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
