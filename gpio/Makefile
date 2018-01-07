obj-m := gpio.o
$(obj-m:.o=)-y := test.o 

KERNEL_DIR := /lib/modules/`uname -r`/build

NFSROOT := ~/work/drivertest

ccflags-y += -Wno-declaraton-after-statement

all: build copy  clean


build:
	make -C $(KERNEL_DIR)  M=$(PWD) modules

copy:
	cp -af  $(obj-m:.o=.ko) $(NFSROOT)
clean:
	make -C $(KERNEL_DIR) M=$(PWD)  clean

.PHONY: all build copy clean
