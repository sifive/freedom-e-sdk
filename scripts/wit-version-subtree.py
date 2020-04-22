#!/usr/bin/env python3

import subprocess
import sys


def run_command(cmd):
    """Run a command and capture stdout"""
    return subprocess.run(cmd, stdout=subprocess.PIPE).stdout.decode("utf-8").strip()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.stderr.write("Please provide an output path as an argument\n")
        sys.exit(1)

    out_path = sys.argv[1]

    with open(out_path, "w") as out_file:
        wit_tree = run_command(["wit", "inspect", "--tree"])

        fesdk_subtree = []
        for line in wit_tree.split("\n"):
            if "├─freedom-e-sdk" in line:
                fesdk_subtree.append(line)
            elif line[0:1] == "├":
                break
            elif len(fesdk_subtree) != 0:
                fesdk_subtree.append(line)

        for line in fesdk_subtree:
            out_file.write(line[2:] + "\n")

