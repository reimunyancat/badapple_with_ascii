#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
namespace fs = std::filesystem;

void init() {
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[H";
    #endif
}

void display_frame(const string& frame) {
    init();
    cout << frame << '\n';
}

string load_frame(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Cannot open file: " << filename << '\n';
        return "";
    }
    string frame((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return frame;
}

string format_filename(int i) {
    ostringstream filename_stream;
    filename_stream << setw(5) << setfill('0') << i;
    return "BA" + filename_stream.str() + ".txt";
}

void print_usage(const string& program_name) {
    cout << "Usage: " << program_name << " [options]\n"
         << "Options:\n"
         << "  --frames-dir <path>   Directory containing ASCII frames (default: ./BA_frame/txt)\n"
         << "  --audio <path>        Path to audio file (default: ./bad_apple.mp3)\n"
         << "  --help                Display this help message\n";
}

int main(int argc, char* argv[]) {
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif

    fs::path frame_directory = "./BA_frame/txt";
    fs::path audio_file = "./bad_apple.mp3";
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        
        if (arg == "--help") {
            print_usage(argv[0]);
            return 0;
        } else if (arg == "--frames-dir" && i + 1 < argc) {
            frame_directory = argv[++i];
        } else if (arg == "--audio" && i + 1 < argc) {
            audio_file = argv[++i];
        } else {
            cerr << "Unknown argument: " << arg << "\n";
            print_usage(argv[0]);
            return 1;
        }
    }
    
    cout << "Using frames directory: " << frame_directory.string() << "\n";
    cout << "Using audio file: " << audio_file.string() << "\n";
    
    if (!fs::exists(frame_directory)) {
        cerr << "Error: Frames directory does not exist: " << frame_directory.string() << "\n";
        return 1;
    }
    
    if (!fs::exists(audio_file)) {
        cerr << "Error: Audio file does not exist: " << audio_file.string() << "\n";
        return 1;
    }
    
    vector<string> frames;
    int num_frames = 0;

    for (const auto& entry : fs::directory_iterator(frame_directory)) {
        if (entry.path().extension() == ".txt") {
            num_frames++;
        }
    }
    
    if (num_frames == 0) {
        cerr << "Error: No ASCII frames found in directory: " << frame_directory.string() << "\n";
        return 1;
    }
    
    cout << "Found " << num_frames << " ASCII frames\n";

    for (int i = 1; i <= num_frames; ++i) {
        fs::path filename = frame_directory / format_filename(i);
        string frame_content = load_frame(filename.string());
        
        if (frame_content.empty()) {
            cerr << "Warning: Failed to load frame " << i << "\n";
            continue;
        }
        
        frames.push_back(frame_content);
    }
    
    if (frames.empty()) {
        cerr << "Error: Failed to load any frames\n";
        return 1;
    }

    SoundBuffer buffer;
    if (!buffer.loadFromFile(audio_file.string())) {
        cerr << "Error: Could not load audio file: " << audio_file.string() << "\n";
        return 1;
    }

    Sound sound(buffer);
    auto frame_duration = chrono::milliseconds(1000 / 60);

    cout << "Starting playback...\n";
    sound.play();
    
    auto playback_start = chrono::steady_clock::now();
    int frame_index = 0;
    
    while (sound.getStatus() == Sound::Status::Playing && frame_index < frames.size()) {
        auto current_time = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(current_time - playback_start).count();
        int target_frame = static_cast<int>(elapsed * 60 / 1000);
  
        while (frame_index <= target_frame && frame_index < frames.size()) {
            display_frame(frames[frame_index]);
            frame_index++;
        }
        
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    return 0;
}