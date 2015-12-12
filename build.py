#!/usr/bin/python3
import subprocess
import os
import timeit

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
	'-std=c++11'
]

sources = [
	'format.cpp',
	'str.cpp'
]

objects = ['build/{}.o'.format(source.replace('.cpp', '')) for source in sources]

tests = [
	'unit_tests/main.cpp', 
	'unit_tests/misc.cpp', 
	'unit_tests/str.test.cpp',
]


include_flags = ['-I{}'.format(x) for x in include_dirs]
library_flags = ['-L{}'.format(x) for x in library_dirs]

os.makedirs('build', 0o755, exist_ok = True)

def compile_format():
	for source, object in zip(sources, objects):
		subprocess.check_call(['g++'] + cpp_flags + include_flags + ['-c'] + [source] + ['-o'] + [object])

try:
	time = timeit.timeit(compile_format, number=1)
	subprocess.check_call(['ar', 'rcs', 'build/libformat.a'] + objects)
	subprocess.check_call([
		'g++', '-std=c++11'] + tests + cpp_flags + include_flags + library_flags + 
		['-lformat', '-lgtest_main', '-lgtest', '-pthread', '-o', 'build/test.bin'])

	print("Compilation time: ", time)
except subprocess.CalledProcessError as error:
	print('Compilation failed.')
	exit(1)

try:
	subprocess.check_call(['build/test.bin'])
except subprocess.CalledProcessError as error:
	print('Running test failed.')
	exit(1)
