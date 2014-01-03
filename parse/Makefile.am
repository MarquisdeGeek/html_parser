####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = parse

## INCLUDES were found outside kdevelop specific part

parse_SOURCES = MyErrorList.cpp beautyCfg.cpp beautify.cpp 
parse_LDADD   = ./cmn/libcmn.a ./html/libhtml.a ./pc/libpc.a 

SUBDIRS = cmn html pc 

EXTRA_DIST = beautify.cpp beautify.h beautyCfg.cpp MyErrorList.cpp MyErrorList.h 

####### kdevelop will overwrite this part!!! (end)############
# set the include path found by configure
INCLUDES= $(all_includes)
 
# the library search path.
parse_LDFLAGS = $(all_libraries) 
                                                                                
