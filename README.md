# Tinker-Firmware
The Firmware of Tinker is based on ARM mbed

## 构建
使用[yotta](http://yottadocs.mbed.com/)构建

```
yotta target frdm-k64f-gcc
```

由于mbed pwm库bug，现在需要手动修正一处：
在`yotta_modules/mbed-hal-ksdk-mcu/source/pwmout_api.c`中，修改`pwmout_write`函数为以下内容:

```
static volatile uint16_t count_buf;
void pwmout_write(pwmout_t* obj, float value) {
    uint32_t instance = obj->pwm_name >> TPM_SHIFT;
    if (value < 0.0f) {
        value = 0.0f;
    } else if (value > 1.0f) {
        value = 1.0f;
    }
    uint32_t ftm_addrs[] = FTM_BASE_ADDRS;
    uint16_t mod = FTM_HAL_GetMod(ftm_addrs[instance]);
    uint16_t new_count = (uint16_t)((float)(mod) * value);
    count_buf = new_count;
    //debug("%u\n", mod, new_count);
    // stop ftm clock to ensure instant update of mod register
    FTM_HAL_SetClockSource(ftm_addrs[instance], kClock_source_FTM_None);
    FTM_HAL_SetChnCountVal(ftm_addrs[instance], obj->pwm_name & 0xf, count_buf);
    FTM_HAL_SetCounter(ftm_addrs[instance], 0);
    FTM_HAL_SetClockSource(ftm_addrs[instance], kClock_source_FTM_SystemClk);
}
```
完成修改后

```
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
### EN
**功能**：使能电机驱动器

**参数个数**：0

**参数说明**：无

### DIS
**功能**：关闭电机驱动器

**参数个数**：0

**参数说明**：无

### SS
**功能**：设置电机速度

**参数个数**：4

**参数说明**：
- 参数：各电机速度

### SP
**功能**：设置电机位移

**参数个数**：4

**参数说明**：
- 参数：各电机位移

### SG
**功能**：设置电子齿轮参数

**参数个数**：2

**参数说明**：
- 参数1：电子齿轮分子
- 参数2：电子齿轮分母

### Subscribe
**功能**：订阅机器人信息

**参数个数**：1

**参数说明**：
- 参数1：（整数）刷新周期(ms)
