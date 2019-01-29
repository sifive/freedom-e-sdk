# Copyright (c) 2019 SiFive Inc.
#
# Documentation Build

.PHONY: all
all: html

###########################
# Build HTML Documentation
###########################

.PHONY: html
html: html/index.html

# Use Sphinx to build HTML from Doxygen XML
html/index.html: sphinx/*
	sphinx-build -b html sphinx html

.PHONY: clean
clean:
	rm -rf html

