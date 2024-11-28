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

void init() {
    cout << "\033[2J\033[H";
}

void display_frame(const string& frame) {
    init();
    cout << frame << '\n';
}

string load_frame(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "파일을 열 수 없습니다: " << filename << '\n';
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

int main() {
    vector<string> frames;
    string base_directory = "/home/reimunyancat/Archive/badapple";
    string frame_directory = base_directory +  "/BA_frame/txt";
    int num_frames = 0;

    for (const auto& entry : filesystem::directory_iterator(frame_directory)) {
        if (entry.path().extension() == ".txt") {
            num_frames++;
        }
    }

    for (int i = 1; i < num_frames; ++i) {
        string filename = frame_directory + "/" + format_filename(i);
        frames.push_back(load_frame(filename));
    }

    SoundBuffer buffer;
    if (!buffer.loadFromFile(base_directory + "/bad_apple.mp3")) {
        cerr << "오디오 파일을 로드할 수 없습니다!" << '\n';
        return -1;
    }

    Sound sound;
    sound.setBuffer(buffer);

    auto frame_duration = chrono::milliseconds(16);

    sound.play();
    auto start_time = chrono::steady_clock::now();
    
    while (sound.getStatus() == Sound::Playing) {
        for (const auto& frame : frames) {
            display_frame(frame);
            auto elapsed = chrono::steady_clock::now() - start_time;
            if (elapsed < frame_duration) {
                this_thread::sleep_for(frame_duration - elapsed);
            }
            start_time = chrono::steady_clock::now();
        }
    }

    return 0;
}

