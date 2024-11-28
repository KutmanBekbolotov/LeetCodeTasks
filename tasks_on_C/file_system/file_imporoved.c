#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void usage(const char *message) {
    if (message != NULL) {
        fprintf(stderr, "%s\n", message);
    }
    fprintf(stderr, "Usage: ./program input-path needle [-i] [-o output-path]\n");
    exit(1);
}

int match(const char *line, const char *needle, int ignore_case) {
    if (ignore_case) {
        size_t len_line = strlen(line);
        size_t len_needle = strlen(needle);

        char *lower_line = (char *)malloc(len_line + 1);
        char *lower_needle = (char *)malloc(len_needle + 1);
        if (!lower_line || !lower_needle) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        for (size_t i = 0; i < len_line; i++) {
            lower_line[i] = (char)tolower((unsigned char)line[i]);
        }
        lower_line[len_line] = '\0';

        for (size_t i = 0; i < len_needle; i++) {
            lower_needle[i] = (char)tolower((unsigned char)needle[i]);
        }
        lower_needle[len_needle] = '\0';

        int result = strstr(lower_line, lower_needle) != NULL;

        free(lower_line);
        free(lower_needle);

        return result;
    } else {
        return strstr(line, needle) != NULL;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        usage("Too few arguments");
    }

    const char *input_path = NULL;
    const char *needle = NULL;
    const char *output_path = NULL;
    int ignore_case = 0;
    int output_specified = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-i") == 0) {
                if (ignore_case) {
                    usage("Parameter -i provided multiple times");
                }
                ignore_case = 1;
            } else if (strcmp(argv[i], "-o") == 0) {
                if (output_specified) {
                    usage("Parameter -o provided multiple times");
                }
                output_specified = 1;
                if (i + 1 >= argc) {
                    usage("Parameter -o requires an output file path");
                }
                output_path = argv[++i];
            } else {
                usage("Unknown flag");
            }
        } else {
            if (input_path == NULL) {
                input_path = argv[i];
            } else if (needle == NULL) {
                needle = argv[i];
            } else {
                usage("Too many positional arguments");
            }
        }
    }

    if (input_path == NULL) {
        usage("Input path not provided");
    }
    if (needle == NULL) {
        usage("Needle not provided");
    }

    FILE *input_file = fopen(input_path, "r");
    if (!input_file) {
        perror("Error opening input file");
        exit(1);
    }

    FILE *output_file = NULL;
    if (output_path != NULL) {
        output_file = fopen(output_path, "w");
        if (!output_file) {
            perror("Error opening output file");
            fclose(input_file);
            exit(1);
        }
    }

    char line[1024];
    while (fgets(line, sizeof(line), input_file)) {
        if (match(line, needle, ignore_case)) {
            if (output_file) {
                fprintf(output_file, "%s", line);
            } else {
                printf("%s", line);
            }
        }
    }

    fclose(input_file);
    if (output_file) {
        fclose(output_file);
    }

    return 0;
}
