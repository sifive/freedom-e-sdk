#!/usr/bin/env python3

"""Detects the presence of a compatible string in a Devicetree"""

import argparse
import sys

import pydevicetree

def parse_arguments(argv):
    arg_parser = argparse.ArgumentParser(
        description="Detect the presence of a compatible string in a Devictree")

    arg_parser.add_argument("-d", "--dts", required=True,
        help="The path to the Devicteree for the target")
    arg_parser.add_argument("-c", "--compatible", required=True,
        help="The compatible string to check for")

    return arg_parser.parse_args(argv)

def main(argv):
    parsed_args = parse_arguments(argv)

    tree = pydevicetree.Devicetree.parseFile(
            parsed_args.dts, followIncludes=True)

    matches = tree.match(parsed_args.compatible)
    if len(matches) != 0:
        sys.stderr.write("Found {} matches for compatible string '{}'\n".format(len(matches), parsed_args.compatible))
        sys.exit(0)

    sys.stderr.write("Found no matches for compatible string '{}'\n".format(parsed_args.compatible))
    sys.exit(1)

if __name__ == "__main__":
    main(sys.argv[1:])
