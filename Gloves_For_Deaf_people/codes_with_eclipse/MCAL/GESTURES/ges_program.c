#ifndef F_CPU
#define F_CPU 8000000UL // Configured for 8 MHz Clock Frequency
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// --- MPU6050 REGISTERS ---
#define MPU6050_WRITE_ADDR   0xD0 // AD0 connected to GND
#define MPU6050_READ_ADDR    0xD1
#define PWR_MGMT_1           0x6B
#define ACCEL_XOUT_H         0x3B

// --- HARDWARE TWI (I2C) DRIVER ---
void TWI_Init(void) {
    TWSR = 0x00; // Prescaler = 1
    TWBR = 0x20; // TWBR = 32 sets SCL frequency to 100 kHz @ 8 MHz F_CPU
    TWCR = (1 << TWEN);
}

void TWI_Start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void TWI_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

uint8_t TWI_Read_ACK(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

uint8_t TWI_Read_NACK(void) {
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

// --- MPU6050 SENSOR FUNCTIONS ---
void MPU6050_Write_Register(uint8_t reg, uint8_t value) {
    TWI_Start();
    TWI_Write(MPU6050_WRITE_ADDR);
    TWI_Write(reg);
    TWI_Write(value);
    TWI_Stop();
}

void MPU6050_Init(void) {
    _delay_ms(150);
    // Wake up MPU6050 (Clears Sleep mode bit)
    MPU6050_Write_Register(PWR_MGMT_1, 0x00);
}

void MPU6050_Read_Raw(int16_t *acc_y, int16_t *gyro_z) {
    TWI_Start();
    TWI_Write(MPU6050_WRITE_ADDR);
    TWI_Write(ACCEL_XOUT_H); // Point to starting register address

    TWI_Start();
    TWI_Write(MPU6050_READ_ADDR);

    // Read 14 sequential data bytes (Accel X, Y, Z | Temp | Gyro X, Y, Z)
    int16_t ax     = (TWI_Read_ACK() << 8) | TWI_Read_ACK();
    *acc_y         = (TWI_Read_ACK() << 8) | TWI_Read_ACK();
    int16_t az     = (TWI_Read_ACK() << 8) | TWI_Read_ACK();
    int16_t temp   = (TWI_Read_ACK() << 8) | TWI_Read_ACK();
    int16_t gx     = (TWI_Read_ACK() << 8) | TWI_Read_ACK();
    int16_t gy     = (TWI_Read_ACK() << 8) | TWI_Read_ACK();
    *gyro_z        = (TWI_Read_ACK() << 8) | TWI_Read_NACK();

    TWI_Stop();
}

// --- HARDWARE UART DRIVER ---
void UART_Init(unsigned long baud) {
    // UBRR calculation = 51 for 9600 baud rate at 8 MHz
    unsigned int ubrr = (F_CPU / (16 * baud)) - 1;
    UBRRH = (unsigned char)(ubrr >> 8);
    UBRRL = (unsigned char)ubrr;
    UCSRB = (1 << TXEN);                 // Enable UART Transmitter
    UCSRC = (1 << URSEL) | (3 << UCSZ0); // 8-bit data format, 1 stop bit
}

void UART_SendString(const char* str) {
    while (*str) {
        while (!(UCSRA & (1 << UDRE))); // Wait for empty transmit buffer
        UDR = *str++;                   // Load char into transmit register
    }
}

// --- MAIN PROGRAM ---
int main(void) {
    // Initialize UART at 9600 baud, I2C at 100 kHz, and MPU6050
    UART_Init(9600);
    TWI_Init();
    MPU6050_Init();

    int16_t acc_y = 0;
    int16_t gyro_z = 0;

    while (1) {
        // Fetch raw motion sensor values
        MPU6050_Read_Raw(&acc_y, &gyro_z);

        // Gesture Condition: Wrist extension (Acc Y) + Upward Flick (Gyro Z)
        if (acc_y > 12000 && gyro_z > 15000) {
            UART_SendString("SHOOT\r\n"); // Send trigger payload to USB-TTL
            _delay_ms(1000);              // Debounce delay to avoid double firing
        }

        _delay_ms(20); // 50 Hz loop execution frequency
    }

    return 0;
}
