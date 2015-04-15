# Tinker-Firmware
Building status: [![Build Status](http://104.236.146.235:8111/app/rest/builds/buildType:(id:TinkerFirmware_Make)/statusIcon)](http://104.236.146.235:8111/viewType.html?buildTypeId=TinkerFirmware_Make&guest=1)
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
### EnableSystem
__功能__：使能电机驱动器

__参数个数__：0

__参数说明__：无

### ShutdownSystem
__功能__：关闭电机驱动器

__参数个数__：0

__参数说明__：无

### SetRobotSpeed
__功能__：设置机器人速度

__参数个数__：2

__参数说明__：
  - 参数1：（枚举）
    - Vx X方向速度
    - Vy Y方向速度
    - Omega 自转速度
  - 参数2：（整数）表示速度值

### GetEncoderChange
__功能__：获取编码器变化量

__参数个数__：1

__参数说明__：
  - 参数1：（整数）编码器编号
  
__返回值说明__：
  - （整数）编码器变化量 （__每次读取后清零__）