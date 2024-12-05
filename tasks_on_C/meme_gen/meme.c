#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 100
#define MAX_LINES 10

typedef struct {
    unsigned char *data;
    int width;
    int height;
    int depth;
} Image;

Image *load_tga(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        return NULL;
    }

    unsigned char header[18];
    fread(header, sizeof(unsigned char), 18, file);

    int width = header[12] + (header[13] << 8);
    int height = header[14] + (header[15] << 8);
    int depth = header[16] / 8; 

    if (depth != 3 && depth != 4) {
        fclose(file);
        return NULL;
    }

    int imageSize = width * height * depth;
    unsigned char *data = malloc(imageSize);
    fread(data, sizeof(unsigned char), imageSize, file);
    fclose(file);

    Image *image = malloc(sizeof(Image));
    image->data = data;
    image->width = width;
    image->height = height;
    image->depth = depth;

    return image;
}

int save_tga(const char *filepath, Image *image) {
    FILE *file = fopen(filepath, "wb");
    if (!file) {
        return 0;
    }

    unsigned char header[18] = {0};
    header[2] = 2; 
    header[12] = image->width & 0xFF;
    header[13] = (image->width >> 8) & 0xFF;
    header[14] = image->height & 0xFF;
    header[15] = (image->height >> 8) & 0xFF;
    header[16] = image->depth * 8; 

    fwrite(header, sizeof(unsigned char), 18, file);
    fwrite(image->data, sizeof(unsigned char), image->width * image->height * image->depth, file);
    fclose(file);

    return 1;
}

void free_image(Image *image) {
    if (image) {
        free(image->data);
        free(image);
    }
}

void draw_text(Image *image, const char *text, int x, int y) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        int px = x + i * 8;
        int py = y;

        if (px >= image->width || py >= image->height) {
            break;
        }

        int offset = (py * image->width + px) * image->depth;
        image->data[offset] = 255;
        image->data[offset + 1] = 255;
        image->data[offset + 2] = 255;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Wrong parameters\n");
        return 1;
    }

    const char *input_path = argv[1];
    const char *output_path = argv[2];
    const char *font_path = argv[3]; 

    Image *image = load_tga(input_path);
    if (!image) {
        printf("Could not load image\n");
        return 1;
    }

    int top_lines, bottom_lines;
    if (scanf("%d %d", &top_lines, &bottom_lines) != 2) {
        free_image(image);
        printf("Неправильный ввод\n");
        return 1;
    }

    char top_text[MAX_LINES][MAX_TEXT_LENGTH];
    char bottom_text[MAX_LINES][MAX_TEXT_LENGTH];

    for (int i = 0; i < top_lines; i++) {
        fgets(top_text[i], MAX_TEXT_LENGTH, stdin);
        top_text[i][strcspn(top_text[i], "\n")] = '\0'; 
    }

    for (int i = 0; i < bottom_lines; i++) {
        fgets(bottom_text[i], MAX_TEXT_LENGTH, stdin);
        bottom_text[i][strcspn(bottom_text[i], "\n")] = '\0'; 
    }

    for (int i = 0; i < top_lines; i++) {
        draw_text(image, top_text[i], 10, 10 + i * 20); 
    }
    for (int i = 0; i < bottom_lines; i++) {
        draw_text(image, bottom_text[i], 10, image->height - (bottom_lines - i) * 20); 
    }

    if (!save_tga(output_path, image)) {
        free_image(image);
        printf("Ошибка при записи выходного файла.\n");
        return 1;
    }

    free_image(image);
    return 0;
}
