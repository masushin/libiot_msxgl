// SPDX - License - Identifier : MIT

#ifndef __LIBIOT_H__
#define __LIBIOT_H__

int iotgeti(const char *node);
int iotgets(const char *node, char *result);
void iotputi(const char *node, int value);
void iotputs(const char *node, char *value);

#endif