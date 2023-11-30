# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  ChessClasses_config = debug
endif
ifeq ($(config),release)
  ChessClasses_config = release
endif

PROJECTS := ChessClasses

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

ChessClasses:
ifneq (,$(ChessClasses_config))
	@echo "==== Building ChessClasses ($(ChessClasses_config)) ===="
	@${MAKE} --no-print-directory -C . -f ChessClasses.make config=$(ChessClasses_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f ChessClasses.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   ChessClasses"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"