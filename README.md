# Tinker-Firmware
Building status: [![Build Status](http://407a.furoc.net:8111/app/rest/builds/buildType:(id:TinkerFirmware_Build)/statusIcon)](http://407a.furoc.net:8111/viewType.html?buildTypeId=TinkerFirmware_Build&guest=1)

The Firmware of Tinker is based on ARM mbed

![ARM mbed](https://mbed.org/static/img/mbed_logo.png)

## 简介
- 以命令的形式控制机器人底层硬件
- 采用UDP传输指令

## 硬件安装
Mecanum轮的安装参考
[Mecanum Wheel Robot](http://www.seeedstudio.com/wiki/4WD_Mecanum_Wheel_Robot_Kit_Series)
 
## 配置说明
配置信息保存在config.h文件中，包括：
- IP地址 
- 端口
- 电机方向

## 命令说明
### EnableSystem / ES
__功能__：使能电机驱动器

__参数个数__：0

__参数说明__：无

### ShutdownSystem / SS
__功能__：关闭电机驱动器

__参数个数__：0

__参数说明__：无

### SetRobotSpeed /SR
__功能__：设置机器人速度

__参数个数__：3

__参数说明__：
  - 参数1：（整数）X方向速度
  - 参数2：（整数）Y方向速度
  - 参数3：（整数）自转速度

### GetEncoderChange / GE
__功能__：获取编码器变化量

__参数个数__：0

__参数说明__：无
  
__返回值说明__：
  - （整数）编码器变化量 （__每次读取后清零__）

### RobotArmSet
__功能__：设置机械臂舵机角度

__参数个数__：6

__参数说明__：
  - 参数1：（整数）舵机角度
  