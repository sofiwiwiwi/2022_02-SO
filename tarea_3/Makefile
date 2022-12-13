JFLAGS = -g

JC = javac

JVM = java

MAIN = Multithread

JAVAS := $(wildcard *.java)

CLASSES := $(JAVAS:.java=.class)

FILE = informe-nautico.txt

.PHONY: clean run

%.class: %.java
	$(JC) $(JFLAGS) $^


run: $(CLASSES)
	$(JVM) $(MAIN) $(FILE)

clean:
	rm -rf *.class *.txt