# 在驱动目录下生成.ko文件
KERNELDIR := /home/lincait/linux/linux_kernal/alientek_linux
ARCH ?= arm
CROSS_COMPILE ?= arm-linux-gnueabihf-
CURRENT_PATH := $(shell pwd)
obj-m := newchrled.o

build: kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
	$(RM) ledApp