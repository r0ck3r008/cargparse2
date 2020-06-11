COMPILER := gcc
COMPILE_PATH := -I${shell pwd}/include
COMPILER_FLAGS := '-g -Wall -Werror -fpic'
LINKER_FLAGS := -shared

ALL_OBJS := mem/*.o argparse/*.o

all: libcargparse2.so

libcargparse2.so: argparse_objs mem_objs
	${COMPILER} ${LINKER_FLAGS} ${ALL_OBJS} -o libcargparse2.so
	make clean_objs

argparse_objs:
	COMPILER=${COMPILER} COMPILE_PATH=${COMPILE_PATH} \
		 COMPILER_FLAGS=${COMPILER_FLAGS} make -C argparse/

mem_objs:
	COMPILER=${COMPILER} COMPILE_PATH=${COMPILE_PATH} \
		 COMPILER_FLAGS=${COMPILER_FLAGS} make -C mem/

clean_objs:
	make -C argparse/ clean
	make -C mem/ clean

clean: clean_objs
	rm -f libcargparse2.so
