###############################################################################
# Makefile for the FALCON utilities module
#
#     See ../../falcon_makefiles/Makefile.libs for usage
#
###############################################################################

PLATFORM_BUILD=1
export PLATFORM_BUILD

###############################################################################
# LIBRARY
###############################################################################

LIB = lib/libfalcon_utilities$(LIB_SUFFIX).a

###############################################################################
# SOURCES
###############################################################################

CC_SOURCES = \
    src/falcon_arg_parser.cc \
    
###############################################################################
# Include ../../falcon_makefiles/Makefile.libs for rules
###############################################################################

include ../falcon_makefiles/Makefile.libs

###############################################################################
# Adjust *FLAGS and paths as necessary
###############################################################################

CPPFLAGS += -DBOOST_LOG_DYN_LINK
CPPFLAGS += -Werror -Wall -Wextra -Wcast-align -Wno-type-limits
CPPFLAGS += -std=c++11 -O3
