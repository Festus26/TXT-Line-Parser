# TXTLineParser

A C utility that extracts and formats numbered lines from text files. This tool processes text files by identifying lines that start with numbers and extracting their content while handling special formatting.

This script can be used for extracting only the necessary lines from your story script to copy paste to any table or file.

TXTLineParser is used in development of Chick'n Mushroom Soup

## Features

- Extracts lines starting with numbers
- Removes number prefixes and processes special formatting (handles `[<...>]` patterns)
- Preserves scene/day markers (lines starting with "S", "Sc", "St", "D", or "G")
- Supports command-line flags for custom input/output paths
- Falls back to default paths when no flags are provided

## Compilation

```bash
gcc TXTLineParser.c -o TXTLineParser
```

## Usage

### Default Behavior
By default, the program uses `input.txt` as input and `output.txt` as output:
```bash
./TXTLineParser
```

### Command-Line Options
```bash
./TXTLineParser [-i input_file] [-o output_file]
```

**Options:**
- `-i <input_file>` : Specify custom input file path (default: `input.txt`)
- `-o <output_file>` : Specify custom output file path (default: `output.txt`)
- `-h, --help` : Display help message

### Examples

```bash
# Use custom input file
./TXTLineParser -i Source.txt

# Use custom output file
./TXTLineParser -o output/Day7.txt

# Specify both input and output
./TXTLineParser -i Source.txt -o output/Result.txt

# Show help
./TXTLineParser -h
```

## How It Works

The program processes each line in the input file:
1. **Numbered lines**: Lines starting with a number (after trimming whitespace) are processed:
   - The number prefix and dot are removed
   - If the line contains `[<...>]` format, content after `>` is extracted
   - Otherwise, content after the dot is extracted
2. **Scene markers**: Lines starting with "S" (Scene/Sat/St), "D" (Day), or "G" (Gün) are preserved with blank lines before and after
3. **Other lines**: Ignored

## Default Configuration

You can modify the default input/output paths by changing the macros in the source code:
```c
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
```

## License

This project is open source and available for use.
