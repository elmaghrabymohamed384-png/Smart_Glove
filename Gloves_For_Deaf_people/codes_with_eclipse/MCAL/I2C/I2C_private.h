/*
 * I2C_private.h
 *
 *  Created on: Sep 8, 2026
 *      Author: jana
 */

#ifndef MCAL_I2C_I2C_PRIVATE_H_
#define MCAL_I2C_I2C_PRIVATE_H_

#define TWAR	*((volatile u8 *)0x22)
#define TWBR	*((volatile u8 *)0x20)
#define TWCR	*((volatile u8 *)0x56)
#define TWINT             7
#define TWEA              6
#define TWSTA             5
#define TWSTO             4
#define TWWC              3
#define TWEN              2
#define TWIE              0

#define TWDR	*((volatile u8 *)0x23)
#define TWSR	*((volatile u8 *)0x21)
#define TWPS1             1
#define TWPS0             0


//--------ACK-----------

#define SC_ACK_TRANS   0x08
#define SLA_ACK_TRANS  0x18

      //MASTER transmitter
#define STAcond_ACK       0x08
#define Re_STAcond_ACK    0x10
#define SLA_W_ACK         0x18
#define TransData_ACK     0x28

      //MASTER receiver
#define SLA_R_ACK         0x40
#define ReceiveData_ACK   0x50
#define ReceiveData_NACK  0x58    /* Added NACK status code for last byte read */


#endif /* MCAL_I2C_I2C_PRIVATE_H_ */
