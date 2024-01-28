

all:
	cd ./Q1 && $(MAKE)
	cd ./Q2 && $(MAKE)
	cd ./Q3 && $(MAKE)
	cd ./Q4 && $(MAKE)

clean:
	cd ./Q1 && $(MAKE) clean
	cd ./Q2 && $(MAKE) clean
	cd ./Q3 && $(MAKE) clean
	cd ./Q4 && $(MAKE) clean


.PHONY: all clean

