c_files= idt.c kernel_main.c gdt.c page.c klibc.c time.c sched.c hd.c keyboard.c shell.c
asm_files= kernel.asm
c_objects = $(addsuffix .o,$(basename $(c_files)))
asm_objects = $(addsuffix .o,$(basename $(asm_files)))
objects:= $(asm_objects) $(c_objects)
kernel = kernel
CFLAGS = -I include/ -c -fno-stack-protector -fno-builtin -w -g 
CC = gcc
AS = nasm
LD = ld
LDFLAGS=-Ttext 0x100000
hardisk=hd.img
.PHONY:all clean dep 
#$(c_objects):%.o:%.c
#	$(CC) $(CFLAGS) $< -o $@
#$(asm_objects):%.o:%.asm
#	$(AS) -f elf $<
$(shell if [ ! -f deps ];then touch deps;fi;)
include deps
$(kernel):$(addsuffix .o,$(basename $(objects)))
#	echo $(addsuffix .o,$(basename $(objects)))
	$(LD) $(LDFLAGS)  -o $@ $^ 
	objdump -D $(kernel) > symbols
	grep '>:' symbols |sed 's/\(.*\) <\(.*\)>:/0x\1 \2/' 	>sym
	nm kernel >System.map
	sudo cp kernel ../hd/kernel
	sync
	sync
clean:
	-rm *.o $(kernel) deps
	touch deps
dep:$(c_files) $(asm_files)
	(if [ -f deps ]; then rm deps;fi;)
	(for file in $(c_files);do \
		$(CC) $(CFLAGS) -M $$file >>deps;echo "	$(CC) $(CFLAGS) $$file">>deps;done)
	(for file in $(asm_files);do \
		$(AS) -g -f elf -M $$file >>deps;echo "	$(AS) -f elf $$file">>deps;done)
all:$(kernel)
