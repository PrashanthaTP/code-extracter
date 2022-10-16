# Automatic Variables : https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# Text functions      : https://www.gnu.org/software/make/manual/html_node/Text-Functions.html

CC:=gcc
CFLAGS:=-Wall
INC:=-Iinclude

SRC_DIR:=src
BIN_DIR:=bin

SRC_EXT:=c
SRC_FILES:=$(shell find ${SRC_DIR} -type f -name "*.${SRC_EXT}")
SRC_MAIN:=main.${SRC_EXT}
# notdir when used in substitution part didn't work
# https://stackoverflow.com/questions/35039505/using-notdir-within-substitution-reference-as-opposed-to-patsubst
#OBJ_FILES:=$(patsubst %,${BIN_DIR}/%,$(notdir ${SRC_FILES:.${SRC_EXT}:=.o}))
OBJ_FILES:=$(patsubst %.c,${BIN_DIR}/%.o,$(notdir ${SRC_FILES}))

TARGET:=bin/main.exe
LOG_PREFIX:=[Make]

SCRIPT_DIR=scripts
all:${TARGET}


define cmd-compile-v1
${CC} ${CFLAGS} $^ -o $@ 
endef

define cmd-link-v1
${CC} ${CFLAGS} ${INC} -c $^ -o $@
endef


COLORED_PREFIX =$(shell echo -e "\e[33m")
COLOR_RESET=$(shell echo -e "\e[0m")

COLOR_RED :=$(shell echo -e "\e[31m")
COLOR_ORANGE :=$(shell echo -e "\e[33m")
COLOR_GREEN :=$(shell echo -e "\e[32m")
COLOR_BOLD_GREEN :=$(shell echo -e "\e[1;32m")
COLOR_BOLD_BLUE :=$(shell echo -e "\e[1;34m")
COLOR_RESET:=$(shell echo -e "\e[0;;m")


define format-color-string
printf "${1}$2${COLOR_RESET}\n"
endef

define echo-info
$(call format-color-string,${COLOR_GREEN},"$1")
endef

define echo-warning
$(call format-color-string,${COLOR_ORANGE},"$1")
endef

define echo-error
$(call format-color-string,${COLOR_RED},"$1")
endef

define echo-cmd
$(call format-color-string,${COLOR_BOLD_BLUE},"$1")
endef

define cmd-compile-v2
@$(call echo-info,"-------- Compiling ---------");\
$(call echo-cmd,"${CC} ${CFLAGS} ${INC} $1 -o $2");\
${CC} ${CFLAGS} ${INC} -c $1 -o $2
endef

define cmd-link-v2
@$(call echo-info,"-------- Linking ---------");\
$(call echo-cmd,"${CC} ${CFLAGS} ${INC} $1 -o $2");\
${CC} ${CFLAGS} ${INC} $1 -o $2
endef

#${CC} ${CFLAGS} ${INC} $1 -I lib/libsystre/mingw32/include -L lib/libsystre/mingw32/bin -L lib/libsystre/mingw32/lib -lregex -o $2
define make-goal
${1}: ${2}
	$(call cmd-compile-v2,$2,$1)
endef

define get-build-obj-path
$(patsubst %.c,${BIN_DIR}/%.o,$(notdir $1))
endef

define make-goal-wrapper
$(eval $(call make-goal,$(call get-build-obj-path,${1}),$1))
endef


#rules for obj files
$(foreach src,${SRC_FILES},$(call make-goal-wrapper,${src}))

.PHONY: clean run test

#executables
${TARGET}: ${OBJ_FILES}
	$(call cmd-link-v2,$^,$@)
	
run: ${TARGET}
	./${TARGET}

clean: ${BIN_DIR}
	@[ ! -z "$(shell ls ${BIN_DIR}/*.exe 2>/dev/null)" ] && { echo "Cleaning ${BIN_DIR}/*.exe ";rm bin/*.exe ; } || echo "No *.exe in ${BIN_DIR} directory to clean";\
	[ ! -z "$(shell ls ${BIN_DIR}/*.o 2>/dev/null)" ] && { echo "Cleaning ${BIN_DIR}/*.o ";rm bin/*.o ; } || echo "No *.o in ${BIN_DIR} directory to clean"

test: ${TARGET}
	 #hack to eval ansi escape codes in wt git bash
	./${SCRIPT_DIR}/test.sh 2>&1 | cat
