# Author  : Prashantha T P
# License : MIT
# Date    : October 16, 2022 Sunday
#

CC:=gcc
CFLAGS:=-Wall

LIBS=$(shell find lib -mindepth 1 -maxdepth 1 -type d)
BIN_DIR=bin
TEMP_DIR=${BIN_DIR}/tmp

.PHONY: list clean

ifeq (no,$(shell [  -d ${TEMP_DIR} ] && echo yes || echo no ))
$(info  [INFO] Please create ./bin/tmp directory)
$(error [ERROR] ${TEMP_DIR} doesn't exist)
endif

list:
	@$(foreach lib,${LIBS},echo $(notdir ${lib}))

define compile
	${CC} ${CFLAGS} -I $(dir $1) -c ${1} -o ${TEMP_DIR}/$(notdir ${1:.c=.o})
endef

#echo  "${CC} ${CFLAGS} -I $(dir $1) -c ${1} -o ${TEMP_DIR}/$(notdir ${1:.c=.o})"
define get-src-files
$(shell find $1 -maxdepth 1 -mindepth 1 -type f -path "*.c")
endef

define get-obj-files
$(patsubst %,${TEMP_DIR}/%,$(notdir ${1:.c:.o}))
endef

define create-rule-for-lib
$1: $2
	@[ -f $1 ] && { echo "cleaning ${1}" && rm $1 ; } || echo -en ""
	${CC} ${CFLAGS} -I $(dir $2) -c ${2} -o $1
endef

define create-rule-for-archive
$1: $(call get-obj-files,$(call get-src-files,$2))
	$(foreach src,$(get-src-files,$2),echo ${src:.c:.o})
	$(call get-obj-files,$(call get-src-files,$2))
	@echo creating archive : $2.a aytala $1
endef

#@$(foreach src, $(call get-src-files,$2),$(call compile,${src}))
#@[ ! -z $(shell ls ${TEMP_DIR}) ] && { echo "cleaning ${TEMP_DIR}" && rm ${TEMP_DIR}/*.o ; } || echo -en ""
#ar -cr $2.a ${TEMP_DIR}/*.o 

define create-rule-for-test
$1: $2
	echo $1 and $2
endef

define create-rule-for-lib-wrapper
$(foreach src, $(call get-src-files,$1),$(eval $(call create-rule-for-lib,${TEMP_DIR}/$(notdir ${src:.c=.o}),${src})))
endef

#$(foreach src, $(call get-src-files,$1),$(eval $(call create-rule-for-lib,${TEMP_DIR}/${src:.c=.o},${src})))
define create-rule-for-archive-wrapper
$(eval $(call create-rule-for-archive, $(notdir ${1}), ${1}))
endef

$(foreach lib,${LIBS},$(call create-rule-for-lib-wrapper,${lib}))
$(foreach lib,${LIBS},$(call create-rule-for-archive-wrapper,${lib}))
