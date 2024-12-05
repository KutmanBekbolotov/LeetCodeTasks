#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct{
    unsigned char *data;
    int width;
    int height;
} Image;


typedef struct{
    Image letters[26];
} Font;

int load_tga(const char *path, Image *image);
int save_tga(const char *path, const Image *image);
int load_font(const char *font_dir, Font *font);
void render_text(Image *image, const char *text,
                 const Font *font, int top, int bottom);

int main(int argc, char **argv) {
    if (argc != 4){
        fprintf(stderr, "Wrong parameters\n");
        return 1;
    }

    const char *input_path = argv[1];
    const char *output_path = argv[2];
    const char *font_dir = argv[3];

    Image input_image;
    if(!load_tga(input_path, &input_image)){
        fprintf(stderr, "Could not load image\n");
        return 1;
    }

    Font font;
    if (!load_font(font_dir, &font)){
        fprintf(stderr, "Could not load font\n");
        return 1;
    }

    char text[101];
    int top, bottom;
    if (scanf("%d %d\n", &top, &bottom) != 2){
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    fgets(text, sizeof(text), stdin);

    render_text(&input_image, text, &font, top, bottom);
    save_tga(output_path, &input_image);

    free(input_image.data);
    return 0;
}