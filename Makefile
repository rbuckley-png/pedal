# Project Name
TARGET = pass-thru

USE_DAISYSP_LGPL = 1

# Sources
CPP_SOURCES = pass-thru.cpp	hardware-init.cpp

# Library Locations
LIBDAISY_DIR = libDaisy
DAISYSP_DIR = DaisySP

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

