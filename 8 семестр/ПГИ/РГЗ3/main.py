from PIL import Image
import numpy as np
from sklearn.cluster import KMeans

# 4. Преобразовать True Color PCX файл в 256-цветный PCX файл.

def main() -> int:
    image = Image.open('./image24.pcx')

    img_array = np.array(image)

    reshaped_array = img_array.reshape(-1, 3)

    kmeans = KMeans(n_clusters=256, random_state=0).fit(reshaped_array)

    color_palette = np.array(kmeans.cluster_centers_, dtype=np.uint8)

    labels = kmeans.labels_

    quantized_img = np.zeros_like(reshaped_array)
    for i in range(len(reshaped_array)):
        quantized_img[i] = color_palette[labels[i]]

    quantized_img = quantized_img.reshape(img_array.shape)

    result_image = Image.fromarray(quantized_img)
    result_image.save('rgr-result.pcx')

    return 0

if __name__ == '__main__':
    exit(main())
