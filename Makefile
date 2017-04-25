arch ?= x86_64
kernel := build/kernel-$(arch).bin
img := build/os.img
cc := x86_64-elf-gcc-6.3.0 -g -Wall -mno-red-zone

linker_script := src/linker.ld
grub_cfg := src/grub.cfg
c_source_files := $(wildcard src/*.c)
c_object_files := $(patsubst src/%.c, \
	build/%.c.o, $(c_source_files))
assembly_source_files := $(wildcard src/*.asm)
assembly_object_files := $(patsubst src/%.asm, \
	build/%.asm.o, $(assembly_source_files))

.PHONY: all clean run img

all: $(kernel)

clean:
	@rm -r build

run: $(img)
	@qemu-system-x86_64 -drive format=raw,file=$(img)

test: $(img)
	@qemu-system-x86_64 -s -drive format=raw,file=$(img) -serial stdio
#-monitor stdio

img: $(img)

$(img): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@dd if=/dev/zero of=$(img) bs=512 count=32768
	@parted $(img) mklabel msdos
	@parted $(img) mkpart primary fat32 2048s 30720s
	@parted $(img) set 1 boot on
	@sudo losetup /dev/loop0 $(img)
	@sudo losetup /dev/loop1 $(img) -o 1048576
	@sudo mkdosfs -F32 -f2 /dev/loop1
	@sudo mount /dev/loop1 /mnt/fatgrub
	@sudo grub-install --root-directory=/mnt/fatgrub --no-floppy --modules="normal part_msdos ext2 multiboot" /dev/loop0
	@sudo cp -r build/isofiles/* /mnt/fatgrub
	@sudo umount /mnt/fatgrub
	@sudo losetup -d /dev/loop0
	@sudo losetup -d /dev/loop1
	@rm -r build/isofiles

$(kernel): $(assembly_object_files) $(linker_script) $(c_object_files)
	ld -n -T $(linker_script) -o $(kernel) $(assembly_object_files) $(c_object_files)

#compile c files
build/%.c.o: src/%.c
	$(cc) -c -g -o $@ $<

# compile assembly files
build/%.asm.o: src/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@
