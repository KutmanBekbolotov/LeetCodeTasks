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
        while (*line && *needle) {
            if (tolower((unsigned char)*line) != tolower((unsigned char)*needle)) {
                return 0; 
            }
            line++;
            needle++;
        }
        return (*needle == '\0'); 
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
    
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-i") == 0) {
                if (ignore_case) {
                    usage("-i flag specified more than once");
                }
                ignore_case = 1;
            } else if (strcmp(argv[i], "-o") == 0) {
                if (i + 1 >= argc) {
                    usage("-o flag requires an output file path");
                }
                output_path = argv[i + 1];
                i++;
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
        usage("Input file path is required");
    }
    if (needle == NULL) {
        usage("Search text is required");
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

    char line[101]; 
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
