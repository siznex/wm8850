/*++
Copyright (c) 2011-2013  WonderMedia Technologies, Inc. All Rights Reserved.

This PROPRIETARY SOFTWARE is the property of WonderMedia
Technologies, Inc. and may contain trade secrets and/or other confidential
information of WonderMedia Technologies, Inc. This file shall not be
disclosed to any third party, in whole or in part, without prior written consent of
WonderMedia.  

THIS PROPRIETARY SOFTWARE AND ANY RELATED
DOCUMENTATION ARE PROVIDED AS IS, WITH ALL FAULTS, AND
WITHOUT WARRANTY OF ANY KIND EITHER EXPRESS OR IMPLIED,
AND WonderMedia TECHNOLOGIES, INC. DISCLAIMS ALL EXPRESS
OR IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, QUIET ENJOYMENT OR
NON-INFRINGEMENT.  
--*/

#include <linux/i2c.h>
#include "gsensor.h"


struct i2c_board_info gsensor_i2c_board_info = {
	.type          = GSENSOR_I2C_NAME,
	.flags         = 0x00,
	.addr          = GSENSOR_I2C_ADDR,
	.platform_data = NULL,
	.archdata      = NULL,
	.irq           = -1,
};

static struct i2c_client *gsensor_client=NULL;
int gsensor_i2c_register_device (void)
{
	struct i2c_board_info *gsensor_i2c_bi;
	struct i2c_adapter *adapter = NULL;
	//struct i2c_client *client   = NULL;
	gsensor_i2c_bi = &gsensor_i2c_board_info;
	adapter = i2c_get_adapter(0);/*in bus 0*/

	if (NULL == adapter) {
		printk("can not get i2c adapter, client address error\n");
		return -1;
	}
	gsensor_client = i2c_new_device(adapter, gsensor_i2c_bi);
	if (gsensor_client == NULL) {
		printk("allocate i2c client failed\n");
		return -1;
	}
	i2c_put_adapter(adapter);
	return 0;
}

void gsensor_i2c_unregister_device(void)
{
	if (gsensor_client != NULL)
	{
		i2c_unregister_device(gsensor_client);
	}
}
struct i2c_client* gsensor_get_i2c_client(void)
{
	return gsensor_client;
}
//EXPORT_SYMBOL_GPL(gsensor_i2c_register_device);