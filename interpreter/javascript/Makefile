.POSIX:

# Workaround for include-line support on both `make` and `nmake`.
#\
!INCLUDE ../Makefile.config #\
!IF 0
include ../Makefile.config #\
!ENDIF

EXT_DEPS=../core/$(LIBPREFIX)karyon-core$(LIB) ../native/$(LIBPREFIX)karyon-native$(LIB)
EXE_DEPS=main$(OBJ) $(EXT_DEPS) $(LIBPREFIX)karyon-javascript$(LIB)
LIB_DEPS=Str$(OBJ) Input$(OBJ) Token$(OBJ)

all: karyon-javascript$(EXE)

karyon-javascript$(EXE): $(EXE_DEPS)
	$(CC) $(LDFLAGS) $(LDOUT)$@ $(EXE_DEPS)

$(LIBPREFIX)karyon-javascript$(LIB): $(LIB_DEPS)
	$(AR) $(ARFLAGS) $(AROUT)$@ $(LIB_DEPS)

Str$(OBJ): $(EXT_DEPS) Str.h
Input$(OBJ): $(EXT_DEPS) Input.h
Token$(OBJ): $(EXT_DEPS) Token.h Input.h Str.h
