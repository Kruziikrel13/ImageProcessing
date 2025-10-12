#compiler
CC = g++ 
#linker
LD = g++
#linker flags
LDFLAGS = -Wall -g
#compiler flags
CFLAGS = -Wall -c -g -std=c++98
#serial libraries
S_LIBS = -ltiff -ljpeg -lpng -lz 

#linker path
LD_PATH = 
#includes
INCLUDE = -I/home/centos/libraries/
#defines for serial program
DEFS = -DSERIAL 
#erase files
RM = rm -f
#object files
S_OBJS =  TIFFimage.o JPEGimage.o PNGimage.o image.o  imageRaster.o serialImageProcessing.o main.o timer.o MemCheck.o 
#program name
PROG = serial 







#first rule
all : $(PROG)

#serial executable
serial : $(S_OBJS)
	$(LD) $(LDFLAGS) $(LD_PATH) $(S_OBJS) $(S_LIBS) -o $@


#%.o : %.cpp
#	$(CC) $(CFLAGS) $(INCLUDE) $(DEFS) $<

main.o : serialMain.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DEFS) $< -o $@

image.o : image/image.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $(DEFS) $< -o $@

TIFFimage.o : image/format/TIFFimage.cpp 
	$(CC) $(CFLAGS) $(DEFS) $(INCLUDE) $< -o $@

JPEGimage.o : image/format/JPEGimage.cpp 
	$(CC) $(CFLAGS) $(DEFS) $(INCLUDE) $< -o $@

PNGimage.o : image/format/PNGimage.cpp
	$(CC) $(CFLAGS) $(DEFS) $(INCLUDE) $< -o $@


imageRaster.o : image/imageRaster.cpp
	$(CC) $(CFLAGS) $(DEFS) $< -o $@

serialImageProcessing.o : processing/serialImageProcessing.cpp
	$(CC) $(CFLAGS) $(DEFS) $< -o $@

timer.o : utils/timer.cpp
	$(CC) $(CFLAGS) $< -o $@

MemCheck.o : utils/MemCheck.cpp
	$(CC) $(CFLAGS) $(DEFS) $< -o $@





clean:
	$(RM) $(S_OBJS) *~
