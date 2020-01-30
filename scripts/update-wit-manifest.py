#!/usr/bin/env python3

"""Updates the contents of wit-manifest.json to match .gitmodules"""

import json
import os
import subprocess
import sys


def run_command(cmd):
    """Run a command and capture stdout"""
    return subprocess.run(cmd, stdout=subprocess.PIPE).stdout.decode("utf-8").strip()


def change_to_root():
    """Change to the root directory of the git repository"""
    rootdir = run_command(["git", "rev-parse", "--show-toplevel"])
    os.chdir(rootdir)
    print("Found git repository in %s" % os.getcwd(), file=sys.stderr)


def check_directory():
    """Make sure we have submodules and a wit manifest"""
    check_files = ["wit-manifest.json", ".gitmodules"]

    for f in check_files:
        if not os.path.isfile(f):
            print("Could not find %s" % f)
            sys.exit(1)
        print("Found %s" % f)

    return all([os.path.isfile(f) for f in check_files])


def read_wit_manifest():
    print("Reading wit manifest")
    with open("wit-manifest.json", "r") as manifest:
        content = json.loads(manifest.read())
    return content


def write_wit_manifest(content):
    print("Writing wit manifest")
    with open("wit-manifest.json", "w") as manifest:
        manifest.write(json.dumps(content, indent=4) + "\n")

def get_submodules():
    print("Getting list of git submodules")
    raw_submodules = run_command(["git", "submodule"])
    submodules = []
    for line in raw_submodules.split("\n"):
        _, path, _ = line.split()
        commit = run_command(["git", "-C", path, "rev-parse", "HEAD"])
        remote = run_command(["git", "-C", path, "remote"]).split("\n")[0]
        url = run_command(["git", "-C", path, "remote", "get-url", remote])
        submodules.append({"commit": commit, "path": path, "remote": remote, "url": url})
    return submodules


def get_packages(manifest):
    submodules = get_submodules()
    packages = []
    for package in manifest:
        for submodule in submodules:
            if submodule['url'] == package['source']:
                packages.append({
                    "package_commit": package['commit'],
                    "submodule_commit": submodule['commit'],
                    "path": submodule['path'],
                    "name": package['name'],
                    "source": submodule['url'],
                })
                del submodules[submodules.index(submodule)]
    return packages


def main():
    change_to_root()
    if not check_directory():
        print("Failed to find submodules or a wit manifest", file = sys.stderr)
        sys.exit(1)

    manifest = read_wit_manifest()

    packages = get_packages(manifest)
    for package in packages:
        if package['package_commit'] != package['submodule_commit']:
            for m in manifest:
                if m['name'] == package['name']:
                    print("Updating package %s to commit %s" % (package['name'], package['submodule_commit']))
                    m['commit'] = package['submodule_commit']
                    break

    write_wit_manifest(manifest)


if __name__ == '__main__':
    main()
