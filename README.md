# i.MX6ULL 驱动与裸机练习

## 关于本仓库

本仓库记录 i.MX6UL/i.MX6ULL 开发板上的裸机程序和 Linux 驱动练习。

## 目录结构

- `01_ledc/` - 裸机 C 语言 LED 闪烁程序
- `02_chrdevbase/` - 虚拟字符设备驱动
- `03_led/` - GPIO LED 字符设备驱动
- `04_newchrled/` - 使用 `cdev`、设备类和设备对象注册 LED 字符设备

## 环境与依赖

- Linux 主机环境
- ARM 硬浮点交叉编译工具链，默认前缀为 `arm-linux-gnueabihf-`
- 与目标开发板匹配、已配置可用于外部模块编译的 Linux 内核源码
- i.MX6UL/i.MX6ULL 开发板及可访问的串口或终端

三个驱动目录的 `Makefile` 默认将内核源码目录设为 `/home/lincait/linux/linux_kernal/alientek_linux`。编译时可传入实际路径覆盖默认值。

## 编译

### 裸机 LED 程序

```bash
cd 01_ledc
make
```

使用 Makefile 中配置的 ARM 工具链编译，生成 `ledc.bin`、`ledc.elf` 和 `ledc.dis`。

### Linux 驱动模块

在相应驱动目录中编译，并将 `KERNELDIR` 指向目标板使用的内核源码目录：

```bash
cd 02_chrdevbase
make KERNELDIR=/path/to/linux-kernel
```

同样的方式适用于 `03_led/` 和 `04_newchrled/`。成功后可在目录中找到对应的 `.ko` 模块。

用户态测试程序需使用目标板兼容的工具链单独编译，例如：

```bash
arm-linux-gnueabihf-gcc chrdevbaseApp.c -o chrdevbaseApp
arm-linux-gnueabihf-gcc ledApp.c -o ledApp
```

## 在开发板上测试

将编译好的模块和用户态程序复制到开发板。加载或卸载模块：

```bash
insmod chrdevbase.ko
rmmod chrdevbase
```

`02_chrdevbase` 和 `03_led` 使用固定主设备号 200，需按驱动对应的设备名创建设备节点，例如：

```bash
mknod /dev/chrdevbase c 200 0
mknod /dev/led c 200 0
```

`04_newchrled` 会注册字符设备并创建设备对象；在设备管理服务正常工作时，设备节点为 `/dev/newchrled`。LED 测试程序的调用格式为：

```bash
./ledApp /dev/led 1
./ledApp /dev/led 0
```

将路径换成 `/dev/newchrled` 可用于 `04_newchrled`。`02_chrdevbase` 的测试程序格式为：

```bash
./chrdevbaseApp /dev/chrdevbase 1  # 读
./chrdevbaseApp /dev/chrdevbase 2  # 写

```
