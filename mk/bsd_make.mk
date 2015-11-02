########################################################
#
# FILE: Makefile
#
# AUTHOR: Nathan Boeger
#
# NOTES:
#  This is a generic Makefile for *BSD make, you will
#  need to customize the listed variables below inside
#  the Makefile for your application.
#
# INSTALL_DIR = name of the directory that you want to install
#   this applicaion (Ex: /usr/local/bin/ )
#
# APP          = name of the application
#
# C_SRC      = C source files (Ex: pstat.c )
#
# CPP_SRC  = CPP source files (Ex: node.cpp)
#
#
# $Id: ch01.html,v 1.5 2004/08/10 14:41:39 nathan Exp $
#########################################################

# Make the OBJ's from our defined C & C++ files
.ifdef CPP_SRC
OBJS            =       ${CPP_SRC:.cpp=.o}
.endif

.ifdef C_SRC
OBJS            +=      ${C_SRC:.c=.o}
.endif

# define the  Compiler. The compiler flags will be appended to
# if defined, else they are just assigned the values below
CPP             =        cc
CFLAGS          +=       -Wall -Wmissing-prototypes -O
LINK            +=       -lc

# Add a debug flag.
.ifdef DEBUG
  CFLAGS += -g
.endif

# Targets
all: ${OBJS}
	$(CPP) $(CFLAGS) -o $(APP) ${OBJS} $(LINK)

depend:
	$(CPP) -E -MM ${C_SRC} ${CPP_SRC}  > .depend

#######################################################
#
#        INSTALL SECTION
#
# install will copy the defined application (APP) into the
# directory INSTALL_DIR and chmod it 0755
# for more information on install read MAN(1) install
########################################################
install: all
	install -b -s $(APP) $(INSTALL_DIR)
	
clean:
	rm -f $(APP) *.o *.core

# SUFFIX RULES
.SUFFIXES: .cpp .c .o

.c.o:
	$(CPP) $(CFLAGS) -c ${.IMPSRC}
.cpp.o:
	$(CPP) $(CFLAGS) -c ${.IMPSRC}