.POSIX:

PYTHON=python3

all: lint-documentation

# TODO validate links in sources and plain text files
lint-documentation: README.md LICENSE.md
	$(PYTHON) lint-commonmark-links.py $?