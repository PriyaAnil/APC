TARGET := ../Library/libapc.so
CFLAG := -I ../Include
SRCS := $(wildcard *.c)
${TARGET} : ${SRCS}
	gcc -fPIC -shared ${CFLAG} $^ -o $@
clean :
	rm ${TARGET}
