//
// Created by 嘉佳 on 2025/10/12.
//

#ifndef IMU_IMU_H
#define IMU_IMU_H

#ifdef __cplusplus
extern "C" {
#endif
class bmi088{
public:
    void bmi088_write_byte(uint8_t tx_data);

    void bmi088_read_byte(uint8_t *rx_data, uint8_t length);

    void bmi088_write_reg(uint8_t reg, uint8_t data);

    void BMI088_ACCEL_NS_L();

    void BMI088_ACCEL_NS_H();

    void BMI088_GYRO_NS_L();

    void BMI088_GYRO_NS_H();

    // 参考: acc写入，相当于加上片选的 bmi088_write_reg 函数
    void bmi088_accel_write_single_reg(uint8_t reg, uint8_t data);

    // 尝试完成 ↓
    void bmi088_accel_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length); // 加速度计读取，注意需要忽略第一位数据dummy byte
    void bmi088_gyro_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length); // 陀螺仪读取
    void bmi088_gyro_write_single_reg(uint8_t reg, uint8_t tx_data); // gyro写入
    void bmi088_init();
};

#ifdef  __cplusplus
    }
#endif
#endif //IMU_IMU_H