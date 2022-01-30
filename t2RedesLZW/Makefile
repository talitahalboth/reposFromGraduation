all: encode decode

encode: encode.c lzwData.h
	gcc encode.c -o encode

decode: decode.c lzwData.h
	gcc decode.c -o decode

clean: 
	rm encode decode