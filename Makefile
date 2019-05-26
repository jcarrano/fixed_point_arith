# ############################################################################ #
# Global config
# ############################################################################ #

# #### Input, output and names ####

OUT_DIR ?= build
SRC ?= src
INCLUDE ?= include
LIBNAME ?= fixed_point
OUT_FILE = $(OUT_DIR)/$(LIBNAME)

# #### Frama-C configuration ####

# z3 seems to be smarter when solving arithmetic problems
WP_PROVER ?= Z3

FRAMA_C ?= frama-c
FRAMA_C_CONFIG ?= $(FRAMA_C)-config
FRAMA_C_FLAGS ?= -no-frama-c-stdlib -cpp-frama-c-compliant
FRAMA_SHARE ?= $(shell $(FRAMA_C_CONFIG) -print-share-path)
# TODO: add ARM machdep
FRAMA_CPPFLAGS ?= -I$(FRAMA_SHARE)/libc/ -DFRAMAC_SOURCE -D__FC_MACHDEP_X86_32 -E -C
# small hack so that we don't have to copy the whole FRAMA_WP_FLAGS to the
# command line when testing.
# One example usage of this is proving a single function, eg:
# FRAMA_WP_XFLAGS="-wp-fct f_neg -wp-print" make proofs
FRAMA_WP_XFLAGS ?=
FRAMA_WP_FLAGS ?= -wp -wp-prover $(WP_PROVER) -wp-rte $(FRAMA_WP_XFLAGS)
FRAMA_REPORT_FLAGS ?= -report-unclassified-unknown ERROR -report-classify -report-output

# #### Tool config ######

# archiver
ifeq (${THIN_ARCHIVE}, true)
ARFLAGS = rcTs
else
ARFLAGS = rcs
endif

# preprocessor
IPATH += -I$(INCLUDE)
CPPFLAGS += $(IPATH) -DFXP_C99_INLINE

# compiler
WFLAGS ?= -pedantic -Wall -Wextra

CFLAGS += -std=c99 -ffunction-sections -fdata-sections

# Important when creating a shared library only
# CFLAGS += -fPIC

# Other tools

NM ?= nm
ACSL_UNICODE ?= scripts/acsl-unicode.sed

# windows hacks
ifeq ($(strip $(OS)), Windows_NT)
MKDIR           ?= md
RM		?= del
RMDIR		?= rmdir /s /q
PATHSEP := \\
else
MKDIR           ?= mkdir -p
RM		?= rm -f
RMDIR		?= rm -rf
PATHSEP := /
endif

# rwildcard  dir,pattern
#	Use this function to recursively search for all files with a certain
#	extension.
#	Unix find is better for this, but it may not be available on windows.
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# rdwildcard  dir
# 	Find all directories
rdwildcard=$(foreach d,$(wildcard $1*/),$(call rdwildcard,$d/) $(filter %/,$d))

# transform infiles,in_extension,out_extension
#	Convert input filenames into output filenames by changing the extension
#	and the directory
transform=$(1:%$2=$(OUT_DIR)/%$3)


# ###################### Messages ######################### #

MSG_ARCHIVING ?= Creating static library archive

# ############################################################################ #
# Automatic dependency generation
# ############################################################################ #


# flags for the preprocessor
DEPFLAGS ?= -MM -MP -MQ $@ $(patsubst %,-MQ %,$(call transform,$*.o $*.proof))

# ######## Let's make a list of all files which exist currently ############ #
C_FILES=$(call rwildcard,$(SRC)/,*.c)
H_FILES=$(call rwildcard,$(SRC)/ $(INCLUDE)/,*.h)
SRC_DIRECTORIES=$(SRC)/ $(call rdwildcard,$(SRC)/)
OUT_DIRECTORIES=$(call rdwildcard,$(OUT_DIR)/)

# .d files are dependency listings for .c files
D_FILES=$(call rwildcard,$(OUT_DIR)/,*.d)

O_FILES=$(call rwildcard,$(OUT_DIR)/,*.o)
GCH_FILES=$(call rwildcard,$(OUT_DIR)/,*.gch)
PROOF_FILES=$(call rwildcard,$(OUT_DIR)/,*.proof)

# ###### Make a list of files that need to be produced ###############

# each .c produces a .o
NEEDED_OBJECTS = $(call transform,$(C_FILES),.c,.o)

# FIXME: right now only some files have proof, so we have to specify them
# manually
# NEEDED_PROOFS = $(C_FILES:.c=.proof)
PROVED_C_FILES = src/fixed_point.c
NEEDED_PROOFS = $(call transform,$(PROVED_C_FILES),.c,.proof)
NEEDED_REPORTS = $(call transform,$(PROVED_C_FILES),.c,.proof-report)

NEEDED_DEPS = $(call transform,$(C_FILES),.c,.d)

NEEDED_DIRS = $(OUT_DIR) $(call transform,$(SRC_DIRECTORIES),,)

# More on automatic dependencies later

# ############################################################################ #
# Rules for building the project
# ############################################################################ #

.PHONY: all library proofs

all: proofs library

library: $(OUT_FILE).a $(OUT_FILE).sym

proofs: $(NEEDED_PROOFS) $(NEEDED_REPORTS)

# ###################### Output directory creation ########################### #

$(OUT_DIR):
	$(MKDIR) $@

$(OUT_DIR)/%/:
	$(MKDIR) $@

.PHONY: directories
directories: | $(NEEDED_DIRS)

# ######################## Rules for cleaning ################################ #

.PHONY: depclean
depclean: $(foreach dfile,$(D_FILES),$(dfile)-clean)

.PHONY: clean
clean: $(foreach f,$(O_FILES) $(GCH_FILES) $(PROOF_FILES),$(f)-clean)

.PHONY: allclean
allclean: clean depclean

.PHONY: wipe
wipe: allclean $(OUT_DIR)-dirclean

# Rules to clean each type of file

%-clean:
	$(RM) $*

%-dirclean:
	$(RMDIR) $*

# ###################### Dependency handling ################################# #

# If we are only cleaning then ignore the dependencies
_REALGOAL = $(if $(MAKECMDGOALS),$(MAKECMDGOALS),all)
ifneq (,$(filter-out depclean clean wipe unicodize,$(_REALGOAL)))
include $(NEEDED_DEPS)
endif

$(OUT_DIR)/%.d: %.c | directories
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(DEPFLAGS) $< -o $@

# ##################### Output file generation ############################### #


$(OUT_FILE).a: $(NEEDED_OBJECTS) | directories

# create a static library file from object files
%.a:
	$(info $(MSG_ARCHIVING))
	$(AR) $(ARFLAGS) $@ $^

# if nm fails for some reason, the file will still be created (because of
# the redirect. Using an intermediate target causes make to delete it.
%.sym-tmp: %.a
	$(NM) -n $< > $@

%.sym: %.sym-tmp
	cp $< $@

$(OUT_DIR)/%.o: | directories
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# ################## Proving stuff ########################################## #

$(OUT_DIR)/%.proof-report $(OUT_DIR)/%.proof: export CPP := $(CPP) $(CPPFLAGS) $(FRAMA_CPPFLAGS)
$(OUT_DIR)/%.proof-report $(OUT_DIR)/%.proof: | directories
	$(info $(CPP))
	$(FRAMA_C) $(FRAMA_C_FLAGS) $(FRAMA_WP_FLAGS) $< \
		-then $(FRAMA_REPORT_FLAGS) $@-report
	touch $@

#                   ╭╴▼ ╖  ╭───────────╮  ╓ ▽╶╮
#                ⇜◫╞╡ ◉ ╠╬╪╡ Æsthetics ╞╪╬╣ ◎ ╞╡◫⟿
#                   ╰╴△ ╜  ╰───────────╯  ╙ ▲╶╯

NEED_PRETTYFYING = $(C_FILES) $(H_FILES)

.PHONY: unicodize

unicodize: $(NEED_PRETTYFYING:%=%-pretty)

%-pretty:
	sed -f $(ACSL_UNICODE) -i $*
