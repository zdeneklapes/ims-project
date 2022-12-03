SHELL = /usr/bin/env bash
NAME = documentation

all: bibtex or biblatex

biblatex:
	pdflatex $(NAME).tex
	biber $(NAME).bcf
	pdflatex $(NAME).tex
	@$(MAKE) -s clean

bibtex:
	pdflatex $(NAME).tex
	bibtex $(NAME).aux
	pdflatex $(NAME).tex
	pdflatex $(NAME).tex
	@$(MAKE) -s clean

.PHONY: clean
clean:
	rm -f $(NAME).{aux,dvi,log,ps,out,bbl,blg,toc,fls,fdb_latexmk} texput.log
