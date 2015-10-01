#!/usr/bin/python3
import subprocess
import os

googletest_root = "googletest/googletest"

include_dirs = [
	'{}/include'.format(googletest_root),
	'include',
]

library_dirs = [
	'{}/build'.format(googletest_root),
	'build',
]

cpp_flags = [
	'-Wall',
]

include_flags = ['-I{}'.format(x) for x in include_dirs]
library_flags = ['-L{}'.format(x) for x in library_dirs]

os.makedirs('build', 0o755, exist_ok = True)

try:
	subprocess.check_call(['g++', '-std=c++11'] + cpp_flags + include_flags + ['-c', 'format.cpp', '-o', 'build/format.o'])
	subprocess.check_call(['ar', 'rcs', 'build/libformat.a', 'build/format.o'])
	subprocess.check_call(['g++', '-std=c++11', 'unit_tests/main.cpp'] + cpp_flags + include_flags + library_flags + ['-lformat', '-lgtest_main', '-lgtest', '-pthread', '-o', 'build/test.bin'])
except subprocess.CalledProcessError as error:
	print('Compilation failed.')
	exit(1)

try:
	subprocess.check_call(['build/test.bin'])
except subprocess.CalledProcessError as error:
	print('Running test failed.')
	exit(1)
