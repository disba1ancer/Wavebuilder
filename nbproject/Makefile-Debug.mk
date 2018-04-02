#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW32-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AbstractDataModel.o \
	${OBJECTDIR}/Graph.o \
	${OBJECTDIR}/HarmonicModel.o \
	${OBJECTDIR}/MainWindow.o \
	${OBJECTDIR}/SoundPlayer.o \
	${OBJECTDIR}/Wavebuilder.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/D/msys64/mingw32/bin -L/D/msys64/home/Anton/opt/wxWidgets/lib -lwx_baseu-3.0.dll -lwx_mswu_core-3.0.dll -lwx_mswu_adv-3.0.dll

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wavebuilder.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wavebuilder.exe: ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resources.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wavebuilder.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/wavebuilder ${OBJECTFILES} ${LDLIBSOPTIONS} ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resources.o

${OBJECTDIR}/AbstractDataModel.o: AbstractDataModel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/msys64/home/Anton/opt/wxWidgets/lib/wx/include/msw-unicode-3.0 -I/D/msys64/home/Anton/opt/wxWidgets/include/wx-3.0 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AbstractDataModel.o AbstractDataModel.cpp

${OBJECTDIR}/Graph.o: Graph.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/msys64/home/Anton/opt/wxWidgets/lib/wx/include/msw-unicode-3.0 -I/D/msys64/home/Anton/opt/wxWidgets/include/wx-3.0 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graph.o Graph.cpp

${OBJECTDIR}/HarmonicModel.o: HarmonicModel.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/msys64/home/Anton/opt/wxWidgets/lib/wx/include/msw-unicode-3.0 -I/D/msys64/home/Anton/opt/wxWidgets/include/wx-3.0 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HarmonicModel.o HarmonicModel.cpp

${OBJECTDIR}/MainWindow.o: MainWindow.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/msys64/home/Anton/opt/wxWidgets/lib/wx/include/msw-unicode-3.0 -I/D/msys64/home/Anton/opt/wxWidgets/include/wx-3.0 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MainWindow.o MainWindow.cpp

${OBJECTDIR}/SoundPlayer.o: SoundPlayer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/msys64/home/Anton/opt/wxWidgets/lib/wx/include/msw-unicode-3.0 -I/D/msys64/home/Anton/opt/wxWidgets/include/wx-3.0 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SoundPlayer.o SoundPlayer.cpp

${OBJECTDIR}/Wavebuilder.o: Wavebuilder.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/D/msys64/home/Anton/opt/wxWidgets/lib/wx/include/msw-unicode-3.0 -I/D/msys64/home/Anton/opt/wxWidgets/include/wx-3.0 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Wavebuilder.o Wavebuilder.cpp

${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resources.o: res.cfg.rc manifest.xml
	${MKDIR} -p ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}
	@echo Выполнение шага пользовательского сборки
	windres -I D:/msys64/home/Anton/opt/wxWidgets/lib/wx/include/msw-unicode-3.0 -I D:/msys64/home/Anton/opt/wxWidgets/include/wx-3.0 -o $@ $<

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/resources.o

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
