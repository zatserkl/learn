#!/usr/bin/env python

# Andriy Zatserklyaniy <zatserkl@gmail.com> Jan 18, 2018

from __future__ import print_function   # to work with both Python 3 and 2
import os
import sys      # for the command line arguments


def size_string(size):
    units = [' ', 'K', 'M', 'G', 'T', 'P']
    iunit = 0
    size_curr = size
    while size_curr // 1024 > 0:
        size_curr /= 1024
        iunit += 1

    if iunit > 0:   # use float format
        size_str = "{0:8.1f}{1:s}".format(size_curr, units[iunit])
    else:           # use int format
        size_str = "{0:8d}{1:s}".format(size_curr, units[iunit])
    return size_str


def dir_size(path="."):
    """
    Compute size of the directory. Call itself recursively for enclosed dirs.

    As usual in the recursive subroutine you should provide
    1) termination of the recursion at some condition
    2) recursive call
    """

    if not os.path.isdir(path):
        return 0

    info_list = next(os.walk(path))

    # info_list consists of two lists: ordinary files and directories
    dirs = info_list[1]
    files = info_list[2]

    # print("dirs:", dirs)
    # print("files:", files)

    # size_tot = os.path.getsize(path) # self-size of OS entry for the directory
    size_tot = 0
    for file in files:
        path_file = os.path.join(path, file)

        if os.path.islink(path_file):
            # stat = os.stat(path_file)
            # print("os.stat:", stat)
            continue

        size_file = 0
        try:
            size_file = os.path.getsize(path_file) # bytes
        except FileNotFoundError as e:
            print("FileNotFoundError:", e)
            continue
        except OSError as e:
            print("OSError:", e)
            continue

        size_tot += size_file
        # print("{0:8d} {1}".format(size_file, path_file))

    # recursion termination

    if len(dirs) == 0:
        return size_tot

    # recursive call

    for dir in dirs:
        dir_child = path_file = os.path.join(path, dir)
        if os.path.islink(dir_child):
            continue
        size_tot += dir_size(dir_child)

    return size_tot


if __name__ == "__main__":

    if len(sys.argv) > 1 and sys.argv[1] in ["-h", "--help"]:
        print("Computes the directory size")
        print("Usage:", __file__, "dir")
        exit()

    path = "."
    if len(sys.argv) > 1:
        path = sys.argv[1]

    size_tot = dir_size(path)
    print("The total size is", size_string(size_tot))
