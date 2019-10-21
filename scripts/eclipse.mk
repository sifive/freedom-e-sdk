# ----------------------------------------------------------------------
# Transform names from Assembly file so the eclipse indexer works.
# ----------------------------------------------------------------------
_ASFLAGS1 =$(ASFLAGS)  $(CPPFLAGS) $(_COMMON_CFLAGS)
_ASFLAGS4=$(_ASFLAGS1)
ifeq ($(UNAME_MSYS_NT),y)
_ASFLAGS2=$(_ASFLAGS1:-I/c/%=-Ic:/%)
_ASFLAGS3=$(_ASFLAGS2:-I/d/%=-Id:/%)
_ASFLAGS4=$(_ASFLAGS3:-I/e/%=-Ie:/%)
endif

# ----------------------------------------------------------------------
# Transform names from C file so the eclipse indexer works.
# ----------------------------------------------------------------------
_CFLAGS1=$(CFLAGS)   $(CPPFLAGS) $(CFLAGS_COMMON) $(_COMMON_CFLAGS)
_CFLAGS4=${_CFLAGS1}
_ASFLAGS4=$(_ASFLAGS1)
ifeq ($(UNAME_MSYS_NT),y)
_CFLAGS2=$(_CFLAGS1:-I/c/%=-Ic:/%)
_CFLAGS3=$(_CFLAGS2:-I/d/%=-Id:/%)
_CFLAGS4=$(_CFLAGS3:-I/e/%=-Ie:/%)
endif

# ----------------------------------------------------------------------
# Transform names from CPP file so the eclipse indexer works.
# ----------------------------------------------------------------------
_CXXFLAGS1=$(CXXFLAGS) $(CPPFLAGS) $(CFLAGS_COMMON) $(_COMMON_CFLAGS)
_CXXFLAGS4=$(_CXXFLAGS1)
ifeq ($(UNAME_MSYS_NT),y)
_CXXFLAGS2=$(_CXXFLAGS1:-I/c/%=-Ic:/%)
_CXXFLAGS3=$(_CXXFLAGS2:-I/d/%=-Id:/%)
_CXXFLAGS4=$(_CXXFLAGS3:-I/e/%=-Ie:/%)
endif

