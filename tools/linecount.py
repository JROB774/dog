#!/usr/bin/env python3

# ==============================================================================
# Simple Python script for counting source code lines for C/C++ projects.
# Available Under Public Domain or MIT License
# Released 11-08-2020
# Version 1.0.6
# Authored by Joshua Robertson
# ==============================================================================

import os

from argparse import ArgumentParser

parser = ArgumentParser(description="Count the lines of code in C/C++ source files.")
parser.add_argument("paths", nargs="+", help="list of dirs/files to count code lines from")
parser.add_argument("--version", action="version", version="%(prog)s v1.0.6")
parser.add_argument("-r", action="store_true", help="recursively go through directories", dest="recursive", default=False)
parser.add_argument("-d", action="store_true", help="print line count info for each source file", dest="detail")
parser.add_argument("-e", action="append", metavar="dir/file", help="dir/file to exclude from the count", dest="exclude", default=[])
args = parser.parse_args()

in_block_comment = False

total_code_count = 0
total_comment_count = 0
total_blank_count = 0
total_line_count = 0

extensions = (".h", ".hh", ".hpp", ".hxx", ".h++", ".c", ".cc", ".cpp", ".cxx", ".c++", ".cp", ".inl", ".ipp", ".hint")

def print_formatted (file, code, comments, blank, total):
    print("| ", end="")
    print(file.ljust(filename_padding), end="")
    print(" | ", end="")
    print(code.rjust(10), end="")
    print(" | ", end="")
    print(comments.rjust(10), end="")
    print(" | ", end="")
    print(blank.rjust(10), end="")
    print(" | ", end="")
    print(total.rjust(10), end="")
    print(" |")

def line_is_code (line):
    global in_block_comment
    line_length = len(line)
    is_code = False
    i = 0
    while i < line_length:
        state_change = False
        if line[i] == "/" and line[i+1] == "*":
            if not in_block_comment:
                in_block_comment = True
                state_change = True
                i += 2
        elif line[i] == "*" and line[i+1] == "/":
            if in_block_comment:
                in_block_comment = False
                state_change = True
                i += 2
        if i >= line_length:
            break
        if not in_block_comment and not line[i].isspace():
            is_code = True
        if state_change:
            i -= 1
        i += 1
    return is_code

def process_file (infilename):
    global in_block_comment

    global total_code_count
    global total_comment_count
    global total_blank_count
    global total_line_count

    code_count = 0
    comment_count = 0
    blank_count = 0
    line_count = 0

    if infilename.lower().endswith(extensions):
        with open(infilename) as f:
            for line in f:
                line = line.lstrip()
                line_length = len(line)

                if in_block_comment:
                    block_comment_exit_pos = 0
                    for i in range(0, line_length-1):
                        if line[i] == "*" and line[i+1] == "/":
                            in_block_comment = False
                            block_comment_exit_pos = i+2
                            break
                    if in_block_comment:
                        comment_count += 1
                    else:
                        if block_comment_exit_pos < line_length:
                            if line_is_code(line[block_comment_exit_pos:]):
                                code_count += 1
                                continue
                        comment_count += 1
                else:
                    if not line:
                        blank_count += 1
                    elif line[0] == "/" and line[1] == "/":
                        comment_count += 1
                    else:
                        if line_is_code(line):
                            code_count += 1
                        else:
                            comment_count += 1

        line_count = code_count + comment_count + blank_count

        total_code_count += code_count
        total_comment_count += comment_count
        total_blank_count += blank_count
        total_line_count += line_count

        if args.detail:
            print_formatted(infilename,
                str(code_count),
                str(comment_count),
                str(blank_count),
                str(line_count))

def get_dir_files (indirectory):
    paths = os.listdir(indirectory)
    files = []
    for path in paths:
        path = os.path.normcase(os.path.normpath(os.path.join(indirectory, path)))
        if os.path.isdir(path):
            if args.recursive:
                if not path in args.exclude:
                    files.extend(get_dir_files(path))
        else:
            if path.lower().endswith(extensions):
                if not path in args.exclude:
                    files.append(path)
    return files

# Clean up the excludes input so they can be handledy properly by the script.
for i,exclude in enumerate(args.exclude):
    args.exclude[i] = os.path.normcase(os.path.normpath(exclude))

# Cache all of the files specified through directories, etc. that need to be counted.
files = []
for path in args.paths:
    path = os.path.normcase(os.path.normpath(path))
    if os.path.isdir(path):
        if not path in args.exclude:
            files.extend(get_dir_files(path))
    else:
        if path.lower().endswith(extensions):
            if not path in args.exclude:
                files.append(path)

# Determine the longest file name so we can pad the output with spaces.
filename_padding = len("TOTAL")
if args.detail:
    if files:
        filename_padding = len(max(files, key=len))

print_formatted("FILE", "CODE", "COMMENTS", "BLANK", "TOTAL")

# Process each source code file and count the lines.
for file in files:
    process_file(file)

print_formatted("TOTAL",
    str(total_code_count),
    str(total_comment_count),
    str(total_blank_count),
    str(total_line_count))
