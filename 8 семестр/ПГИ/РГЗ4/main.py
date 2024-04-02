from PIL import Image 
import numpy as np 
import random

def color_difference(color1, color2):
    r1, g1, b1 = color1
    r2, g2, b2 = color2
    delta = ((r1 - r2) )**2 + ((g1 - g2) )**2 + ((b1 - b2) )**2
    return delta

def k_means(points, k, max_iterations=100):
    centroids = random.sample(points, k)
    clusters = [[] for _ in range(k)]
    
    for _ in range(max_iterations):
        new_clusters = [[] for _ in range(k)]
        
        for point in points:
            closest_index = min([(i, color_difference(point, centroid)) for i, centroid in enumerate(centroids)], key=lambda x: x[1])[0]
            new_clusters[closest_index].append(point)
        
        if clusters == new_clusters:
            break
        
        clusters = new_clusters
        
        for i in range(k):
            if clusters[i]:
                centroids[i] = tuple(np.mean(clusters[i], axis=0))
    
    return centroids

def find_most_common_colors(image, num_colors):
    image = image.convert("RGB")
    pixels = np.array(image)
    points = [tuple(pixel) for row in pixels for pixel in row]
    
    centroids = k_means(points, num_colors)
    
    return centroids

def replace_colors(image, palette):
    image = image.convert("RGB")
    pixels = np.array(image)
    
    for i in range(len(pixels)):
        for j in range(len(pixels[i])):
            pixel_color = tuple(pixels[i][j])
            closest_color = min(palette, key=lambda x: color_difference(pixel_color, x))
            pixels[i][j] = closest_color
    
    new_image = Image.fromarray(pixels)
    return new_image

input_image_path = "CAT256.pcx"
try:
    input_image = Image.open(input_image_path)
except FileNotFoundError:
    print(f"Файл '{input_image_path}' не найден.")
except Exception as e:
    print(f"Ошибка загрузки изображения: {e}")

if input_image:
    palette_size = 16
    palette = find_most_common_colors(input_image, palette_size)
    
    output_image = replace_colors(input_image, palette)
    input_image.show()
    output_image.show()
    output_image_path = "cat16.pcx"
    output_image.save(output_image_path)
