/*
 * ModbusShare.h
 *
 *  Created on: May 25, 2022
 *      Author: ronso
 */

#ifndef INC_MODBUSSHARE_H_
#define INC_MODBUSSHARE_H_

#define FIRST_SCAN_ADDRESS 20
#define LAST_SCAN_ADDRESS 41

#define MODBUS_MAX_DATA_LENGTH        40
#define MODBUS_MAX_CHILD_ADDRESS      0x60
#define MODBUS_GET_RX_LEN_FROM_DEVICE 0xFF
#define MODBUS_UNITIALIZED_ADDRESS    0
#define MODBUS_BROADCAST_ADDRESS      0
#define MODBUS_MAX_NON_RANDOM_ADDRESS 20

#define MBUS_PKT_DATA_OFFSET 1
#define MBUS_PKT_LENGTH_OFFSET 0


typedef enum
{
    MBUS_FUNCT_READ = 4,
    MBUS_FUNCTION_WRITE = 5,
    MBUS_FUNCT_RESET = 8,
} mBusFuncCodes;




typedef enum
{
    MBUS_READ_ID = 1,
    MBUS_READ_TYPE,
    MBUS_READ_HELLO,
	MBUS_READ_TEMPERATURE,
	MBUS_READ_FUEL_STATUS,
    MBUS_READ_UPGRADE_STATUS,
} mBusReadCodes;


typedef enum
{
    MBUS_WRITE_ADD = 1,
	MBUS_WRITE_LED,
} mBusWriteCodes;


typedef enum
{
    MBUS_RESET_ADD_IF_NOT_INITIALIZED = 1,
    MBUS_RESET_ADD,
    MBUS_RESET_DEVICE,
    MBUS_RESET_UPGRADE,
    MBUS_RESET_ENABLE,
} mBusResetCodes;


#define MBUS_DEVICE_ENABLE_STRING     "\xAA\xAA\xAA\xAA\xAA\x55\x55\x55\x55\x55"
#define MBUS_DEVICE_ENABLE_STRING_LEN 10

typedef enum
{
    MBUS_DEV_TYPE_FREE = 0,
    MBUS_DEV_TYPE_SCALE,
    MBUS_DEV_TYPE_PROBE,
    MBUS_DEV_TYPE_UNKNOWN,
}mbDevType;

#endif /* INC_MODBUSSHARE_H_ */