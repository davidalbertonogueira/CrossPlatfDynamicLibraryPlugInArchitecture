#!/bin/bash
# Makefile for CrossPlatfDynamicLibraryPlugInArchitecture
TOPTARGETS := all clean cleanall

SUBDIRS := circle square triangle genericlib TargetApplication

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)