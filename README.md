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
- ARM 交叉编译工具链，默认前缀为 `arm-linux-gnueabihf-`
- i.MX6UL/i.MX6ULL 开发板及串口、终端