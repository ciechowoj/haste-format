#!/usr/bin/python3
import subprocess
import os

os.makedirs('build', 0o755, exist_ok = True)
subprocess.check_call(['g++', '-c', 'format.cpp', '-o', 'build/format.o'])
subprocess.check_call(['ar', 'rcs', 'build/libformat.a', 'build/format.o'])

subprocess.check_call(['g++', 'unit_tests/main.cpp', '-Lbuild', '-lformat', '-Iinclude', '-o', 'build/test.bin'])

