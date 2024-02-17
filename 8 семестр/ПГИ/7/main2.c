#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#pragma(pop)

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
        image.palette = malloc(colors_number * 4 * sizeof(uint8_t));
        fread(image.palette, sizeof(uint8_t), colors_number * 4, file);
    }

    image.rastr = malloc(image.head.filesize);
    int bytes_per_pixel = image.head.bpp / 8;
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

void write_image(FILE* file, Image image)
{
    fwrite(&image.head, sizeof(Head), 1, file);

    if (NULL != image.palette) {
        fwrite(image.palette, sizeof(uint8_t), (1 << image.head.bpp) * 4, file);
    }

    uint32_t bytes_per_pixel = image.head.bpp / 8;
    uint32_t row_size = image.head.width * bytes_per_pixel;
    uint32_t padding = (4 - (row_size) % 4) % 4;

    for (int i = 0; i < image.head.height; i++) {
        fwrite(&image.rastr[i * row_size], sizeof(uint8_t), row_size, file);
        fwrite(&padding, sizeof(uint8_t), padding, file);
    }
}


void write_text_to_image(Image *image, const char *text)
{
    uint64_t image_rastr_iterator = 0;
    for (int i = 0; i < strlen(text); i++) {
        for (int j = 0; j < 4; j++) {
            image->rastr[image_rastr_iterator] &= ~0x03;
            image->rastr[image_rastr_iterator] |= ((text[i] >> (j * 2)) & 0x03);
            image_rastr_iterator++;
        }
    }
}


char* extract_text_from_image(Image image)
{
    uint64_t image_rastr_iterator = 0;
    uint64_t rastr_size = image.head.height * image.head.width * (image.head.bpp / 8);
    char *text = malloc(rastr_size);
    if (text == NULL) {
        return NULL;
    }

    for (int i = 0; i < rastr_size && image_rastr_iterator < rastr_size; i++) {
        for (int j = 0; j < 4; j++) {
            text[i] |= ((image.rastr[image_rastr_iterator] & 0x03) << (j * 2));
            image_rastr_iterator++;
        }
    }
    return text;
}


char* read_text(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    uint64_t file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char *text = malloc(file_size + 1);
    fread(text, 1, file_size, file);
    text[file_size] = 0;
    return text;
}


int main(int argc, char* argv[])
{
    if (argc <= 3) {
        fprintf(stderr, "Usage: %s <image> <textfile> <output>\n", argv[0]);
        return -1;
    }

    char* filename = argv[1];

    FILE* file = fopen(filename, "rb");
    if (NULL == file) {
        perror(filename);
        return -1;
    }

    Image image = read_image(file);

    fclose(file);

    filename = argv[2];
    file = fopen(filename, "rb");
    if (NULL == file) {
        perror(filename);
        return -1;
    }

    char* text = read_text(file);
    fclose(file);

    print_head(image.head);

    write_text_to_image(&image, text);

    write_image(fopen(argv[3], "wb"), image);

    Image new_image = read_image(fopen(argv[3], "rb"));

    printf("\n\n\n");
    char* new_text = extract_text_from_image(new_image);
    printf("%s", new_text);
    return 0;
}
