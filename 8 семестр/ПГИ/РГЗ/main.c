#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma pack(1)
typedef struct {
    uint16_t signature;
    uint32_t filesize;
    uint32_t reserved;
    uint32_t offset;
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bpp;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_m;
    uint32_t y_pixels_per_m;
    uint32_t colors_used;
    uint32_t colors_important;
} Head;

typedef struct {
    Head head;
    uint8_t* rastr;
    uint8_t* palette;
} Image;

void read_head(Head* head, FILE* file) { fread(head, sizeof(Head), 1, file); }

Image read_image(FILE* file)
{
    Image image = { 0 };

    read_head(&image.head, file);

    fseek(file, sizeof(image.head), SEEK_SET);

    if (image.head.bpp <= 8) {
        int colors_number = 1 << image.head.bpp;
        image.palette = (uint8_t*)malloc(colors_number * 4 * sizeof(uint8_t));
        fread(image.palette, sizeof(uint8_t), (colors_number * 4), file);
    }

    image.rastr = (uint8_t*)malloc(image.head.filesize);
    int bytes_per_pixel = image.head.bpp / 8;
    if (bytes_per_pixel == 0) {
        bytes_per_pixel = bytes_per_pixel;
    }
    int row_size = image.head.width * bytes_per_pixel;

    uint32_t padding = (4 - image.head.width * bytes_per_pixel % 4) % 4;
    for (int i = 0; i < image.head.height; i++) {
        fread(&image.rastr[i * row_size], sizeof(uint8_t), row_size, file);
        fseek(file, padding, SEEK_CUR);
    }

    fread(image.rastr, sizeof(uint8_t), image.head.filesize, file);

    return image;
}

void print_head(Head head)
{
    printf("signature: %s\n", (char*)&head.signature);
    printf("filesize: %d\n", head.filesize);
    printf("reserved: %d\n", head.reserved);
    printf("offset: %d\n", head.offset);
    printf("header_size: %d\n", head.header_size);
    printf("width: %d\n", head.width);
    printf("height: %d\n", head.height);
    printf("planes: %d\n", head.planes);
    printf("bpp: %d\n", head.bpp);
    printf("compression: %d\n", head.compression);
    printf("image_size: %d\n", head.image_size);
    printf("x_pixels_per_m: %d\n", head.x_pixels_per_m);
    printf("y_pixels_per_m: %d\n", head.y_pixels_per_m);
    printf("colors_used: %d\n", head.colors_used);
    printf("colors_important: %d\n", head.colors_important);
}

double calculate_dissimilarity(const uint8_t* palette, uint8_t color1_index, uint8_t color2_index)
{
    // Calculate the RGB values of color1
    uint8_t color1_r = palette[color1_index * 4 + 2];
    uint8_t color1_g = palette[color1_index * 4 + 1];
    uint8_t color1_b = palette[color1_index * 4];

    // Calculate the RGB values of color2
    uint8_t color2_r = palette[color2_index * 4 + 2];
    uint8_t color2_g = palette[color2_index * 4 + 1];
    uint8_t color2_b = palette[color2_index * 4];

    // Calculate the Euclidean distance between the two colors
    double diff_r = color1_r - color2_r;
    double diff_g = color1_g - color2_g;
    double diff_b = color1_b - color2_b;
    return sqrt(diff_r * diff_r + diff_g * diff_g + diff_b * diff_b);
}


typedef struct {
    uint8_t index;
    uint64_t counts;
} PalletteCount;


Image convert_8_bit_bmp_to_4_bit_bmp(Image image)
{
    PalletteCount pallette_counts[256];
    for (int i = 0; i < 256; i++) {
        pallette_counts[i].index = i;
        pallette_counts[i].counts = 0;
    }

    for (int y = 0; y < image.head.height; y++) {
        for (int x = 0; x < image.head.width; x++) {
            pallette_counts[image.rastr[y * image.head.width + x]].counts++;
        }
    }

    uint8_t selected_colors[16];    // Choose the most frequent and dissimilar colors
    for (int i = 0; i < 16; i++) {
        uint8_t most_frequent_color = pallette_counts[i].index;
        selected_colors[i] = most_frequent_color;
        // is_selected[most_frequent_color] = true;

        // Calculate dissimilarity with already selected colors
        double max_dissimilarity = -1.0;
        uint8_t selected_color_index = 0;

        for (int j = 0; j < i; j++) {
            uint8_t selected_color = selected_colors[j];

            // Calculate dissimilarity (e.g., Euclidean distance in RGB space)
            double dissimilarity = calculate_dissimilarity(image.palette, most_frequent_color, selected_color);

            if (dissimilarity > max_dissimilarity) {
                max_dissimilarity = dissimilarity;
                selected_color_index = j;
            }
        }

        // Choose the color with the maximum dissimilarity
        if (max_dissimilarity >= 0.0) {
            selected_colors[i] = most_frequent_color;
        }
    }

    // Create the new palette
    uint8_t* new_palette = (uint8_t*)malloc(4 * 16);
    for (int i = 0; i < 16; i++) {
        uint8_t palette_offset = i * 4;
        uint8_t color_index = selected_colors[i];
        new_palette[palette_offset + 2] = image.palette[color_index * 4 + 2]; // R
        new_palette[palette_offset + 1] = image.palette[color_index * 4 + 1]; // G
        new_palette[palette_offset] = image.palette[color_index * 4]; // B
    }

    // Update image header and palette
    image.head.bpp = 4;
    image.head.planes = 1;
    image.head.colors_used = 16;
    image.head.colors_important = 16;
    image.head.offset = sizeof(Head) + (1 << image.head.bpp) * 4;
    image.head.filesize = image.head.height * (image.head.width + 1) / 2 + image.head.offset;

    // Convert pixel values to 4-bit indices
    uint8_t* new_rastr = (uint8_t*)malloc((image.head.width + 1) / 2 * image.head.height);
    for (int y = 0; y < image.head.height; y++) {
        for (int x = 0; x < image.head.width; x++) {
            uint8_t color_index_from_original_pallette = image.rastr[y * image.head.width + x];
            float min_delta = __FLT_MAX__;
            uint8_t index = 0;
            uint64_t color_offset = color_index_from_original_pallette * 4;
            for (int i = 0; i < 16; i++) {
                uint8_t color_index_from_new_pallette = selected_colors[i];
                float delta = sqrt(
                    (image.palette[color_offset] - new_palette[color_index_from_new_pallette * 4])
                    * (image.palette[color_offset] - new_palette[color_index_from_new_pallette * 4])
                    + (image.palette[color_offset + 1] - new_palette[color_index_from_new_pallette * 4 + 1])
                    * (image.palette[color_offset + 1] - new_palette[color_index_from_new_pallette * 4 + 1])
                    + (image.palette[color_offset + 2] - new_palette[color_index_from_new_pallette * 4 + 2])
                    * (image.palette[color_offset + 2] - new_palette[color_index_from_new_pallette * 4 + 2])
                );

                if (delta < min_delta) {
                    min_delta = delta;
                    index = i;
                }
            }

            if (index >= 16) {
                printf("Error: index >= 16\n");
                exit(1);
            }

            uint64_t rastr_index = y * ((image.head.width + 1) / 2) + x / 2;

            if (x % 2 == 0) {
                new_rastr[rastr_index] &= 0x0F;
                new_rastr[rastr_index] |= (index << 4);
            } else {
                new_rastr[rastr_index] &= 0xF0;
                new_rastr[rastr_index] |= (index & 0x0F);
            }
        }
    }

    // Update image raster
    free(image.rastr);
    free(image.palette);

    image.rastr = new_rastr;
    image.palette = new_palette;

    return image;
}

void write_image(FILE* file, Image image)
{
    fwrite(&image.head, sizeof(Head), 1, file);

    if (NULL != image.palette) {
        fwrite(image.palette, sizeof(uint8_t), (1 << image.head.bpp) * 4, file); // Always write 64 bytes for palette in a 4-bit BMP
    }

    uint32_t row_size = (image.head.width + 1) / 2; // Correct row size calculation

    // Calculate padding based on the compressed width
    uint32_t padding = (4 - (row_size) % 4) % 4;

    for (int i = 0; i < image.head.height; i++) {
        fwrite(&image.rastr[i * row_size], sizeof(uint8_t), row_size, file);
        fwrite(&padding, sizeof(uint8_t), padding, file);
    }
}

int main(int argc, char* argv[])
{
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return -1;
    }

    char* filename = argv[1];

    FILE* file = fopen(filename, "rb");
    if (NULL == file) {
        perror(filename);
        return -1;
    }

    Image image = read_image(file);
    print_head(image.head);

    if (image.head.bpp != 8) {
        fprintf(stderr, "Unsupported format");
        return -1;
    }

    fclose(file);

    write_image(fopen(argv[2], "wb"), convert_8_bit_bmp_to_4_bit_bmp(image));

    return 0;
}
