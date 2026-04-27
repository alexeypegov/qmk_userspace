.SILENT:

.DEFAULT_GOAL := build

MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

QMK_FIRMWARE_ROOT := $(shell qmk config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    QMK_FIRMWARE_ROOT := $(realpath $(QMK_USERSPACE)/../qmk_firmware)
endif

ifneq ($(MAKECMDGOALS),flash)
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `qmk config -ro user.qmk_home` is not set)
endif
endif

.PHONY: build flash

build:
	cd $(QMK_FIRMWARE_ROOT) && qmk compile -kb cantor -km alexeypegov -e QMK_USERSPACE=$(QMK_USERSPACE)

flash:
	dfu-util -a 0 -s 0x08000000:leave -D cantor_alexeypegov.bin

%:
	+$(MAKE) -C $(QMK_FIRMWARE_ROOT) $(MAKECMDGOALS) QMK_USERSPACE=$(QMK_USERSPACE)
