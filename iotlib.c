// SPDX - License - Identifier : MIT

#include "msxgl.h"

__sfr __at(0x58) iot_port;

u8 g_temp;

/*
    setup
    - description
        setup for communication with the IOT device.
    - arguments
        node: The name of the node.
    - return value
        none
*/
void setup(const char *node)
{
    int l, i;
    iot_port = 0xE0;
    iot_port = 0x01;
    iot_port = 0x53;
    iot_port = 0xC0;

    l = String_Length(node);
    iot_port = l;

    for (i = 0; i < l; i++)
    {
        iot_port = node[i];
    }

    iot_port = 0x00;
    g_temp = iot_port;
}

/*
    iotgeti
    - description
        Get an integer value from the IOT device.
    - arguments
        node: name of the node.
    - return value
        Value from the IOT device.
*/
int iotgeti(const char *node)
{
    unsigned char r[2];

    setup(node);

    iot_port = 0xE0;
    iot_port = 0x01;
    iot_port = 0x01;
    iot_port = 0x80;

    g_temp = iot_port;
    r[0] = iot_port;
    r[1] = iot_port;
    return (int)*((u16 *)r);
}

/*
    iotgets
    - description
        Get a string (byte data) value from the IOT device.
    - arguments
        node: node name.
        result: Pointer to the buffer to store the return value.
    - return value
        Length of the return value.
*/
int iotgets(const char *node, char *result)
{
    u8 l;
    int i;

    setup(node);

    iot_port = 0xE0;
    iot_port = 0x01;
    iot_port = 0x03;
    iot_port = 0x80;
    l = iot_port;

    for (i = 0; i < l; i++)
    {
        result[i] = iot_port;
    }
    result[l] = 0;
    return l;
}

/*
    iotputi
    - description
        Send an integer value to the IOT device.
    - arguments
        node: node name
        value: value to send.
    - return value
        none
*/
void iotputi(const char *node, int value)
{
    setup(node);

    iot_port = 0xE0;
    iot_port = 0x01;
    iot_port = 0x41;
    iot_port = 0xC0;

    iot_port = 0x02;
    iot_port = value & 0x00ff;
    iot_port = (value & 0xff00) >> 8;
}

/*
    iotputs
    - description
        Send a string (byte data) to the IOT device.
    - arguments
        node: node name
        value: value to send.
    - return value
        none
*/
void iotputs(const char *node, char *value)
{
    u8 l;
    int i;
    setup(node);

    iot_port = 0xE0;
    iot_port = 0x01;
    iot_port = 0x43;
    iot_port = 0xC0;

    l = String_Length(value);

    iot_port = l;
    for (i = 0; i < l; i++)
    {
        iot_port = value[i];
    }

    iot_port = 0x00;
    g_temp = iot_port;
}
