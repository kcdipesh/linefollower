# Projekt für meine Komplexe Leistung
#
# Ich verwende `ino'für das Bauen und Senden an den Arduino.
# ino: https://github.com/amperka/ino

# Ino binary
INO = ino
# picocom binary
PICOCOM = ~/Devel/picocom/picocom
# Arduino serial port
SERIALPORT = /dev/ttyACM0

all: build

build:
	$(INO) build

upload: build
	$(INO) upload

serial:
#	$(INO) serial
	$(PICOCOM) --echo --nolock $(SERIALPORT)

clean:
	rm -rf ./.build
