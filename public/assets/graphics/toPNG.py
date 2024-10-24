import os
from PIL import Image

def convert_to_png(directory):
    # Walk through all files and subdirectories in the directory
    for root, _, files in os.walk(directory):
        for filename in files:
            # Construct full file path
            file_path = os.path.join(root, filename)
            
            # Check if it's a file (not a directory) and not already a PNG
            if os.path.isfile(file_path) and not filename.lower().endswith('.png'):
                try:
                    # Open the image file
                    with Image.open(file_path) as img:
                        # Convert the image to PNG format
                        png_filename = os.path.splitext(filename)[0] + '.png'
                        png_file_path = os.path.join(root, png_filename)
                        
                        # Save the image in PNG format
                        img.save(png_file_path, 'PNG')
                        print(f"Converted {filename} to {png_filename}")
                        
                        # Delete the original file
                        os.remove(file_path)
                        print(f"Deleted original file {filename}")
                except Exception as e:
                    print(f"Failed to convert {filename}: {e}")

# Specify the directory containing the images
directory = './imgs'

# Convert all files in the directory to PNG
print(f"starting")
convert_to_png(directory)
print(f"complete")
