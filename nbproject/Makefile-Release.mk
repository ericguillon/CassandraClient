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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/BaseDAO.o \
	${OBJECTDIR}/src/CassandraSession.o \
	${OBJECTDIR}/src/Client.o \
	${OBJECTDIR}/src/ClientDAO.o \
	${OBJECTDIR}/src/CustomFields.o \
	${OBJECTDIR}/src/Decimal.o \
	${OBJECTDIR}/src/Event.o \
	${OBJECTDIR}/src/EventDAO.o \
	${OBJECTDIR}/src/GlobalConfig.o \
	${OBJECTDIR}/src/Logger.o \
	${OBJECTDIR}/src/Operation.o \
	${OBJECTDIR}/src/OperationDAO.o \
	${OBJECTDIR}/src/OperationFactory.o \
	${OBJECTDIR}/src/SCTHandler.o \
	${OBJECTDIR}/src/SepaHandler.o \
	${OBJECTDIR}/src/TimerManager.o \
	${OBJECTDIR}/src/Utils.o \
	${OBJECTDIR}/src/XMLParser.o \
	${OBJECTDIR}/src/constants.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/debian/cassandra-cpp-driver/usr/lib/x86_64-linux-gnu -L../boost_1_60_0/stage/lib -lcassandra -lpthread ../boost_1_60_0/stage/lib/libboost_log.a ../boost_1_60_0/stage/lib/libboost_log_setup.a ../boost_1_60_0/stage/lib/libboost_signals.a ../boost_1_60_0/stage/lib/libboost_system.a ../boost_1_60_0/stage/lib/libboost_filesystem.a ../boost_1_60_0/stage/lib/libboost_date_time.a ../boost_1_60_0/stage/lib/libboost_thread.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ../boost_1_60_0/stage/lib/libboost_log.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ../boost_1_60_0/stage/lib/libboost_log_setup.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ../boost_1_60_0/stage/lib/libboost_signals.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ../boost_1_60_0/stage/lib/libboost_system.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ../boost_1_60_0/stage/lib/libboost_filesystem.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ../boost_1_60_0/stage/lib/libboost_date_time.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ../boost_1_60_0/stage/lib/libboost_thread.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/BaseDAO.o: src/BaseDAO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/BaseDAO.o src/BaseDAO.cpp

${OBJECTDIR}/src/CassandraSession.o: src/CassandraSession.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CassandraSession.o src/CassandraSession.cpp

${OBJECTDIR}/src/Client.o: src/Client.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Client.o src/Client.cpp

${OBJECTDIR}/src/ClientDAO.o: src/ClientDAO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/ClientDAO.o src/ClientDAO.cpp

${OBJECTDIR}/src/CustomFields.o: src/CustomFields.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CustomFields.o src/CustomFields.cpp

${OBJECTDIR}/src/Decimal.o: src/Decimal.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Decimal.o src/Decimal.cpp

${OBJECTDIR}/src/Event.o: src/Event.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Event.o src/Event.cpp

${OBJECTDIR}/src/EventDAO.o: src/EventDAO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EventDAO.o src/EventDAO.cpp

${OBJECTDIR}/src/GlobalConfig.o: src/GlobalConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GlobalConfig.o src/GlobalConfig.cpp

${OBJECTDIR}/src/Logger.o: src/Logger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Logger.o src/Logger.cpp

${OBJECTDIR}/src/Operation.o: src/Operation.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Operation.o src/Operation.cpp

${OBJECTDIR}/src/OperationDAO.o: src/OperationDAO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OperationDAO.o src/OperationDAO.cpp

${OBJECTDIR}/src/OperationFactory.o: src/OperationFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OperationFactory.o src/OperationFactory.cpp

${OBJECTDIR}/src/SCTHandler.o: src/SCTHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SCTHandler.o src/SCTHandler.cpp

${OBJECTDIR}/src/SepaHandler.o: src/SepaHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SepaHandler.o src/SepaHandler.cpp

${OBJECTDIR}/src/TimerManager.o: src/TimerManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TimerManager.o src/TimerManager.cpp

${OBJECTDIR}/src/Utils.o: src/Utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Utils.o src/Utils.cpp

${OBJECTDIR}/src/XMLParser.o: src/XMLParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/XMLParser.o src/XMLParser.cpp

${OBJECTDIR}/src/constants.o: src/constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../../AndroidStudioProjects/cpp-driver-master/packaging/build/cassandra-cpp-driver-2.2.2/include -I../boost_1_60_0 -Iinclude -I../rapidxml-1.13 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/constants.o src/constants.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cassandraclient

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
