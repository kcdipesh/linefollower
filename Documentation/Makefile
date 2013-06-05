# Documentation für meine Komplexe Leistung
#
# Ich verwende `troff` dafür. Inspiration dafür gab es bei:
# marmaro.de: https://www.marmaro.de/docs/master/

# resulting filename
NAME = komplexe-leistung
# files containing all the chapters for the documentation.
CHAPS = style.roff aufbau_fahrzeug.roff aufbau_programm.roff fazit.roff glossar.roff sources.roff

# parameters for troff processing
TROFFFLAGS = -Tps -ms -mom
# parameters for pdf file generation
PDFFLAGS = -sPAPERSIZE=a4 -dPDFSETTINGS=/prepress -dEmbedAllFonts=true
# programm for viewing the PDF
PDFVIEWER = zathura

all: pdf

ps: $(NAME).ps
$(NAME).ps: roff
	cat $(NAME).roff | preconv | tbl | pic | groff $(TROFFFLAGS) >$@

pdf: $(NAME).pdf
$(NAME).pdf: roff
	pdfmom -Tps -mm $(NAME).roff >$@

roff: $(NAME).roff
$(NAME).roff: $(CHAPS)
	soelim $(CHAPS) | preconv | pic >$@

view: pdf
	$(PDFVIEWER) $(NAME).pdf

clean:
	rm -f $(NAME).ps $(NAME).pdf $(NAME).roff

# Heirloom troff
#
#$(NAME).ps: $(CHAPS)
#	cat $(CHAPS) | \
#		$(TROFFPREFIX)/tbl | \
#		$(TROFFPREFIX)/pic | \
#		TROFFONTS=/usr/share/fonts/TTF $(TROFFPREFIX)/troff $(TROFFFLAGS) | \
#		$(TROFFPREFIX)/dpost >$@
#
#	ps2pdf $(PDFFLAGS) $(NAME).ps
