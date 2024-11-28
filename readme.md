ffmpeg -i bad_apple.mp4 -vf "fps=60" BA_frame/png/BA_%05d.png
g++ main.cpp -o main -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
