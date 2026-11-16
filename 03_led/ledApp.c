/*
   led驱动测试
   使用说明：
  ./ledtest /dev/led 0 关闭 LED
  ./ledtest /dev/led 1 打开 LED
*/
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define LEDON  1
#define LEDOFF 0

int main(int argc, char *argv[])
{
    int fd, retvalue;
    char *filename;
    unsigned char databuf[1];

    if(argc != 3)
    {
        printf("Error Usage!\r\n");
        return -1;
    }

    filename = argv[1];         // 获取路径
    databuf[0] = atoi(argv[2]); // 获取要对led执行的操作

    // 打开设备文件
    fd = open(filename, O_RDWR);
    if(fd < 0)
    {
        printf("file %s open failed!\r\n", argv[1]);
        return -1;
    }

    // 向设备写入数据
    retvalue = write(fd, databuf, sizeof(databuf));
    if(retvalue < 0)
    {
        printf("LED Control Failed!\r\n");
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}