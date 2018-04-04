#!/usr/bin/env python

# Andriy Zatserklyaniy <zatserkl@gmail.com> Dec 18, 2017

from __future__ import print_function   # to work with both Python 3 and 2
import os
import sys      # for the command line arguments


def nfiles(path=".", nfiles_min=0):
    """
    Walks through directory and prints the number of (ordinary) files
    in the current dir and in each of enclosed dir,
    if the number of files exceeds the threshold nfiles_min.
    Links to files are counted as files. Links to directories are ignored.

    As usual in the recursive subroutine you should provide
    1) termination of the recursion at some condition
    2) recursive call
    """

    if not os.path.isdir(path):
        return

    if os.path.islink(path):
        return

    # --Python2_only-- info_list = os.walk(path).next()
    info_list = next(os.walk(path))

    dirs = info_list[1]
    files = info_list[2]

    # the main task: report the number of files

    if len(files) > nfiles_min:
        print("{0}\t{1}".format(len(files), path))

    # recursion termination

    if len(dirs) == 0:
        return

    # recursive call

    for dir in dirs:
        dir_child = os.path.join(path, dir)
        nfiles(dir_child, nfiles_min)


if __name__ == "__main__":

    if len(sys.argv) > 1 and sys.argv[1] in ["-h", "--help"]:
        print("Prints the number of ordinary files in each directory")
        print("Usage:", __file__,
              "[path] [the minimum number of files to report]")
        exit()

    path = "."
    if len(sys.argv) > 1:
        path = sys.argv[1]

    nfiles_min = 0
    if len(sys.argv) > 2:
        nfiles_min = int(sys.argv[2])

    nfiles(path, nfiles_min)
