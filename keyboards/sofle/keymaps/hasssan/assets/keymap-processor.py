#!/usr/bin/env -S uv run --script

# /// script
# requires-python = ">=3.12"
# ///

import argparse
import sys
import re

def replace_layer_names(content):
    """Replace layer names with their numeric representations."""
    replacements = {
        "BASE": "0",
        "SYM": "1",
        "NAV": "2",
        "NUM": "3",
        "WIN": "4",
        "FUN": "5",
        "EXT": "6",
        "NHRM": "7",
        "GAME": "8"
    }

    for name, number in replacements.items():
        content = re.sub(rf'\b{name}\b', number, content)

    return content

def main():
    parser = argparse.ArgumentParser(description='Process QMK keymap JSON files to replace layer names with numeric representations')
    parser.add_argument('file_path', help='Path to the JSON keymap file to process')
    parser.add_argument('-o', '--output', help='Output file path (default: overwrite input file)', default=None)
    args = parser.parse_args()

    try:
        # Read the input file as a string
        with open(args.file_path, 'r') as f:
            content = f.read()

        # Replace layer names with numeric representations
        modified_content = replace_layer_names(content)

        # Output the result
        if args.output:
            with open(args.output, 'w') as f:
                f.write(modified_content)
            print(f"Modified content written to {args.output}")
        else:
            with open(args.file_path, 'w') as f:
                f.write(modified_content)
            print(f"File {args.file_path} updated successfully")

    except FileNotFoundError:
        print(f"Error: File {args.file_path} not found", file=sys.stderr)
        sys.exit(1)
    except PermissionError:
        print(f"Error: Permission denied for file {args.file_path}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"Error: {str(e)}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()

