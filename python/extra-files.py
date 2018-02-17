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

    size_tot = 0
    for file in files:
        path_file = os.path.join(path, file)

        if os.path.islink(path_file):
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


def extra_files(dir_search, dir_compare):
    """
    """

    if not os.path.isdir(dir_search):
        return 0
    if not os.path.isdir(dir_compare):
        return 0

    list_search = os.listdir(dir_search)
    list_compare = os.listdir(dir_compare)

    list_diff = [x for x in list_search if x not in list_compare]

    dirs = []
    files = []
    for fname in list_diff:
        if os.path.isdir(dir_search + fname):
            dirs.append(fname)
        else:
            files.append(fname)

    print("dirs:")
    for fname in dirs:
        path = os.path.join(dir_search, fname)

        if os.path.islink(path):
            continue

        size = dir_size(path)
        print("{0:10s} {1}".format(size_string(size), path))

    print("files:")
    for fname in files:
        path = os.path.join(dir_search, fname)

        if os.path.islink(path):
            continue

        size = 0
        try:
            size = os.path.getsize(path) # bytes
        except FileNotFoundError as e:
            print("FileNotFoundError:", e)
            continue
        except OSError as e:
            print("OSError:", e)
            continue

        print("{0:10s} {1}".format(size_string(size), path))


if __name__ == "__main__":

    if len(sys.argv) > 1 and sys.argv[1] in ["-h", "--help"]:
        print("Prints extra files in the first directory comparing with the second")
        print("Usage:", __file__, "dir_search dir_compare")
        exit()

    if len(sys.argv) < 3:
        print("Prints extra files in the first directory comparing with the second")
        print("Usage:", __file__, "dir_search dir_compare")
        exit()

    dir_search = sys.argv[1]
    dir_compare = sys.argv[2]

    extra_files(dir_search, dir_compare)

