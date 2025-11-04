#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"


int starts_with_number(const char *line) {
    if (line == NULL) return 0;
    while (*line && isspace((unsigned char)*line)) {
        line++; // Skip leading whitespace
    }
    return isdigit((unsigned char)*line);
}

void copy_numbered_lines(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");

    if (in == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    if (out == NULL) {
        perror("Error opening output file");
        fclose(in);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (starts_with_number(buffer)) {
            //Write the line after the number to the output file
            for(int i = 0; i < (int)strlen(buffer); i++) {
                //printf("%c", buffer[i]);
                if(buffer[i] == '.') {
                    if(buffer[i + 2] == '[') {
                        for(int j = i + 3; j < (int)strlen(buffer); j++) {
                            if(buffer[j] == '>') {
                                fputs(buffer + j + 2, out);
                                break;
                            }
                        }
                        break;
                    }
                    fputs(buffer + i + 2, out);
                    break;   
                }   
            }
            //fputs(buffer, out);   
        }
        //if the line starts with "Scene" or "Day"
        else if((buffer[0] == 'S' && (buffer[1] == 'a' || buffer[1] == 'c' || buffer[1] == 't')) || buffer[0] == 'D' || buffer[0] == 'G') {
            fprintf(out, "\n");
            fputs(buffer, out);
            fprintf(out, "\n");
        }
    }

    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[]) {
    const char *input_file = INPUT_FILE;
    const char *output_file = OUTPUT_FILE;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s [-i input_file] [-o output_file]\n", argv[0]);
            printf("  -i input_file   Specify input file (default: %s)\n", INPUT_FILE);
            printf("  -o output_file  Specify output file (default: %s)\n", OUTPUT_FILE);
            printf("  -h, --help      Show this help message\n");
            return EXIT_SUCCESS;
        }
    }

    copy_numbered_lines(input_file, output_file);

    return EXIT_SUCCESS;
}
