#include "protocol_fk.h"
#include <string.h>
#include <stdio.h>


static int32_t check_fk_msg(uint8_t* buffer, uint32_t leng)
{
	if ((!buffer) || (leng < 45) || (buffer[0] != 0xEB) || (buffer[1] != 0x90))
	{
		return 0;
	}
	return (int32_t)1;
}

void init_xk_up_heart_msg(XKUpHeartMsg* msg)
{
	msg->fkhead = 0xAAAAAAAABBBBBBBB;
	msg->version = 0x01;
	msg->flag = 0x0200;
	msg->MLen = 55;

}

void init_xk_up_devState_msg(XKUpDevStateMsg* msg)
{
	memset(msg, 0, sizeof(XKUpDevStateMsg));

	msg->fkhead = 0xAAAAAAAABBBBBBBB;
	msg->version = 0x01;
	msg->flag = 0x0201;
	msg->MLen = 96;
}

void init_xk_up_log_msg(XKUpLogMsg* msg)
{
	msg->fkhead = 0xAAAAAAAABBBBBBBB;
	msg->version = 0x01;
	msg->flag = 0x0202;
	msg->MLen = 583;
}

