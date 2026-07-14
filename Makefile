.SILENT:

.DEFAULT_GOAL := build

MAKEFLAGS += --no-print-directory

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

EFFECTIVE_GOALS := $(if $(MAKECMDGOALS),$(MAKECMDGOALS),build)

ifneq ($(filter-out flash layout layout-global,$(EFFECTIVE_GOALS)),)
QMK_FIRMWARE_ROOT := $(shell qmk config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    QMK_FIRMWARE_ROOT := $(realpath $(QMK_USERSPACE)/../qmk_firmware)
endif

ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `qmk config -ro user.qmk_home` is not set)
endif
endif

.PHONY: build flash flash-wait layout layout-global

build:
	cd $(QMK_FIRMWARE_ROOT) && qmk compile -kb cantor -km alexeypegov -e QMK_USERSPACE=$(QMK_USERSPACE)

flash:
	dfu-util -a 0 -s 0x08000000:leave -D cantor_alexeypegov.bin

flash-wait:
	i=10; while [ $$i -gt 0 ]; do printf '%s... ' "$$i"; sleep 1; i=$$((i - 1)); done; printf '\n'
	$(MAKE) flash
	i=10; while [ $$i -gt 0 ]; do printf '%s... ' "$$i"; sleep 1; i=$$((i - 1)); done; printf '\n'
	$(MAKE) flash

layout:
	mkdir -p "$$HOME/Library/Keyboard Layouts"
	cp layout/Russian-Cantor-42.keylayout "$$HOME/Library/Keyboard Layouts/"
	cp layout/Russian-Cantor-42.icns "$$HOME/Library/Keyboard Layouts/"
	printf '%s\n' 'Installed Russian Cantor 42. Log out and log back in before selecting it in System Settings.'

layout-global:
	sudo cp layout/Russian-Cantor-42.keylayout layout/Russian-Cantor-42.icns "/Library/Keyboard Layouts/"
	printf '%s\n' 'Installed Russian Cantor 42 system-wide. Log out and log back in before selecting it in System Settings.'

%:
	+$(MAKE) -C $(QMK_FIRMWARE_ROOT) $(MAKECMDGOALS) QMK_USERSPACE=$(QMK_USERSPACE)
