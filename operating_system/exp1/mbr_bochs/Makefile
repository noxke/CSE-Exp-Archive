all:	Image

Image: boot_.s
	nasm -o boot.o boot_.s
	dd if=boot.o of=Image bs=512 conv=sync

clean:
	rm boot.o Image
