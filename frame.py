from PIL import Image
import numpy as np
import os

ASCII_CHARS = "@%#*+=- "

def to_ascii(image_path, new_width=100):
    image = Image.open(image_path)
    width, height = image.size
    aspect_ratio = height / width
    new_height = int(aspect_ratio * new_width * 0.5)
    image = image.resize((new_width, new_height))
    image = image.convert("L")
    pixels = np.array(image)
    ascii_str = ""
    for pixel_value in pixels.flatten():
        ascii_str += ASCII_CHARS[pixel_value // 32]
    ascii_str_len = len(ascii_str)
    ascii_str = [ascii_str[index: index + new_width] for index in range(0, ascii_str_len, new_width)]
    return "\n".join(ascii_str)

def save(image_path, frame_number, output_dir="./BA_frame/txt"):
    ascii_image = to_ascii(image_path)
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    ascii_filename = os.path.join(output_dir, f"BA{frame_number:05d}.txt")
    with open(ascii_filename, "w") as file:
        file.write(ascii_image)
    print(f"Processed frame {frame_number:05d}")

def convert(image_folder):
    files = sorted([f for f in os.listdir(image_folder) if f.endswith('.png')])
    if not files:
        print("No PNG files found in the folder!")
    else:
        print(f"Found {len(files)} PNG files.")
    
    for i, file in enumerate(files):
        image_path = os.path.join(image_folder, file)
        frame_number = int(file.split('BA_')[1].split('.')[0])
        save(image_path, frame_number)

image_folder = "./BA_frame/png"
convert(image_folder)

