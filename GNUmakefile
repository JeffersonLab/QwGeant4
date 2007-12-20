# $Id: GNUmakefile,v 1.5 2006/05/02 01:02:20 grimm Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------


# target
name := QweakSimG4
G4TARGET := $(name)

# external libs
G4EXLIB := true

ifndef QWEAK_BASE
  export QWEAK_BASE := $(PWD)
endif

export G4WORKDIR := $(PWD)

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

# debugging symbols
#ifdef G4DEBUG
#  CPPFLAGS += -g -ggdb
#endif

# profiling
#ifdef G4PROFILE
#  CPPFLAGS += -pg
#endif


#-----------------------------------------
# Checking important environment settings
#-----------------------------------------
#

ifndef XERCESCROOT	
	@echo XERCESCROOT not defined!
endif

ifndef GDML_INC
	@echo GDML_INC not defined!
endif

ifndef GDML_LIB
	@echo GDML_LIB not defined!
endif

.PHONY: all
all: lib bin 


# G4 arch include
include $(G4INSTALL)/config/architecture.gmk
#include $(G4INSTALL)/config/binmake.gmk

# QWEAK make includes (gmk) dir
MAKEINCLUDES := $(QWEAK_BASE)/config/make

# GDML
#include $(MAKEINCLUDES)/gdml.gmk

# Xerces
#include $(MAKEINCLUDES)/xerces.gmk

# ROOT
include $(MAKEINCLUDES)/root.gmk

# LCDD
#include $(MAKEINCLUDES)/lcdd.gmk

# LCIO
#include $(MAKEINCLUDES)/lcio.gmk

# LCPhys
#include $(MAKEINCLUDES)/lcphys.gmk

# To be placed last: 
# Geant4 binmake and special settings
include $(MAKEINCLUDES)/geant4.gmk


#----------------------------
# Adding OpenCascade Package
#----------------------------
#
#INCFLAGS  += -I$(OPENCASCADE)/include 
#LDFLAGS   += -L$(OPENCASCADE)/lib -lTKSTEP -lTKOffset 
#CPPFLAGS  += -DUSE_NON_CONST -DCSFDB -DNO_CXX_EXCEPTION -DNo_Exception -DNDEBUG -DLIN -DLININTEL -DHAVE_CONFIG_H -DUSE_STL_STREAM -DHAVE_LIMITS

#-------------------------------------------------------------------------------------
# Before we compile, use rootcint to create the dictionary files for our ROOT classes.
#-------------------------------------------------------------------------------------
# 
$(G4TARGET).cc: src/QweakSimUserMainEvent_Dict.cc

src/QweakSimUserMainEvent_Dict.cc: 
	@echo "Generating dictionary QweakSimUserMainEvent_Dict.cc ..."
	@rootcint -f src/QweakSimUserMainEvent_Dict.cc -c $(ROOTCFLAGS) -I./include QweakSimUserMainEvent.hh QweakSimUserPrimaryEvent.hh QweakSimUserGEM_MainEvent.hh QweakSimUserGEM_SingleGEMEvent.hh QweakSimUserGEM_WirePlaneEvent.hh QweakSimUserHDC_MainEvent.hh QweakSimUserHDC_SingleHDCEvent.hh QweakSimUserHDC_WirePlaneEvent.hh QweakSimUserVDC_MainEvent.hh QweakSimUserVDC_Config.hh QweakSimUserVDC_DriftCellEvent.hh QweakSimUserVDC_SingleVDCEvent.hh QweakSimUserVDC_WirePlaneEvent.hh QweakSimUserTriggerScintillator_MainEvent.hh QweakSimUserTriggerScintillator_DetectorEvent.hh QweakSimUserTriggerScintillator_PMTEvent.hh QweakSimUserCerenkov_MainEvent.hh QweakSimUserCerenkov_OctantEvent.hh QweakSimUserCerenkov_DetectorEvent.hh QweakSimUserCerenkov_PMTEvent.hh EPEvent.hh QweakSimUserMainEvent_LinkDef.hh


#-----------------------------------------------------------------
# After G4 programs have compiled, create the ROOT shared library.
#-----------------------------------------------------------------
#
RootShared = ./QweakSim.so
RootObjs   = $(G4TMPDIR)/QweakSimUserMainEvent.o $(G4TMPDIR)/QweakSimUserMainEvent_Dict.o

bin: $(RootShared)
$(RootShared): $(RootObjs)
	@echo "Making ROOT shared library..."
	@$(CXX) -shared -O $(RootObjs) -o $@
	@echo "$@ done"

#-----------------------------------------------------------------------------
# For cleaning the ROOT files, add a command to the standard G4 "make clean":
#-----------------------------------------------------------------------------
#
clean::
	@echo "Deleting old dictionaries, shared libraries, output files, documentation and analysis classes..."
	@rm -f *.so src/*Dict* *MakeClass* 
	@rm -rf docs
	@rm -rf tmp 

