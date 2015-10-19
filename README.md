# Tinker-Firmware
The Firmware of Tinker is based on ARM mbed

## 构建
使用[yotta](http://yottadocs.mbed.com/)构建

```
yotta target frdm-k64f-gcc
yotta build
```

## 简介
- 以命令的形式控制机器人底层硬件
- 采用UDP传输指令

## 硬件安装
Mecanum轮的安装参考 [Mecanum Wheel Robot](http://www.seeedstudio.com/wiki/4WD_Mecanum_Wheel_Robot_Kit_Series)

## 配置说明
配置信息保存在config.h文件中，包括：
- IP地址
- 端口
- 电机方向

## 命令说明
### EnableSystem / ES
**功能**：使能电机驱动器

**参数个数**：0

**参数说明**：无

### ShutdownSystem / SS
**功能**：关闭电机驱动器

**参数个数**：0

**参数说明**：无

### SetRobotSpeed /SR
**功能**：设置机器人速度

**参数个数**：3

**参数说明**：
- 参数1：（整数）X方向速度
- 参数2：（整数）Y方向速度
- 参数3：（整数）自转速度

### Subscribe / SI
**功能**：订阅机器人信息

**参数个数**：1

**参数说明**：
- 参数1：（整数）刷新周期(ms)
