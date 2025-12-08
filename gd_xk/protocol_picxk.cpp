#include "protocol_picxk.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static int32_t check_fk_msg(uint8_t* buffer, uint32_t leng)
{
	if (!buffer || leng < 45 || buffer[0] != 0xEB || buffer[1] != 0x90)
		return 0;

	return 1;
}
void init_pic_up_realtime_msg(PICUpRealTimeStateMsgStruct* msg)
{
	memset(msg, 0, sizeof(PICUpRealTimeStateMsgStruct));
	msg->sync_code = 0xAA55;
}

void init_XKConfigInfo(ConfigManager* config,XKConfigInfo* info)
{
	strcpy(info->XK_IP, config->read("XK_IP","").c_str());
	strcpy(info->GD_IP, config->read("GD_IP", "").c_str());
	strcpy(info->FK_IP, config->read("FK_IP", "").c_str());
	strcpy(info->VI_RTSP_Addr, config->read("VI_RTSP_Addr", "").c_str());
	strcpy(info->IR_RTSP_Addr, config->read("IR_RTSP_Addr", "").c_str());

	info->VI_H264_Port = config->read("VI_H264_Port", 0);
	info->IR_H264_Port = config->read("IR_H264_Port", 0);
	info->XK_Recv_GD_INFO_Port = config->read("XK_Recv_GD_INFO_Port", 0);
	info->XK_Send_GD_INFO_Port = config->read("XK_Send_GD_INFO_Port", 0);
	info->XK_Send_FK_INFO_Port = config->read("XK_Send_FK_INFO_Port", 0);
	info->FK_Send_XK_INFO_Port = config->read("FK_Send_XK_INFO_Port", 0);

	info->this_jingdu = config->read("this_jingdu", 0.0F);
	info->this_weidu = config->read("this_weidu", 0.0F);
	info->this_gaodu = config->read("this_gaodu", 0.0F);

	strcpy(info->PIC_SAVE_Addr, config->read("PIC_SAVE_Addr", "").c_str());
	strcpy(info->VIDEO_SAVE_Addr, config->read("VIDEO_SAVE_Addr", "").c_str());
	strcpy(info->LOG_SAVE_Addr, config->read("LOG_SAVE_Addr", "").c_str());

	info->IS_WARNING_TARGET = config->read("IS_WARNING_TARGET", 0);

	//int dev_id_int = config->read("DEV_ID", 0);
	//int source_id_int = config->read("SOURCE_ID", 0);
	//info->devID = config->read("DEV_ID", 0);
	sscanf(config->read("DEV_ID", "").c_str(), "%x", &info->devID);
	//info->sourceID = config->read("SOURCE_ID", 0);
	sscanf(config->read("SOURCE_ID", "").c_str(), "%x", &info->sourceID);
	info->IS_GUIDE_ADAPT_VIEW = config->read("IS_GUIDE_ADAPT_VIEW", 0);
	info->GUIDE_ADPAT_VIEW_PIXE_VI = config->read("GUIDE_ADPAT_VIEW_PIXE_VI", 0);
	info->GUIDE_ADPAT_VIEW_PIXE_IR = config->read("GUIDE_ADPAT_VIEW_PIXE_IR", 0);
	info->GUIDE_ADPAT_VIEW_SIZE = config->read("GUIDE_ADPAT_VIEW_SIZE", 0);

	info->laser_forbid_fw_start = config->read("LASER_FORBID_FW_START", 0.0F);
	info->laser_forbid_fw_stop = config->read("LASER_FORBID_FW_STOP", 0.0F);
	info->laser_forbid_fy_start = config->read("LASER_FORBID_FY_START", 0.0F);
	info->laser_forbid_fy_stop = config->read("LASER_FORBID_FY_STOP", 0.0F);
	int a = 1;
}


void init_GDConfigInfo(ConfigManager* config, GDConfigInfo* info)
{
	info->sync_code = 0xAA55;
	info->type = FKUP_CONFIG_INFO_E;
	strcpy(info->XK_IP, config->read("XK_IP", "").c_str());
	strcpy(info->GD_IP, config->read("GD_IP", "").c_str());
	strcpy(info->VI_RTSP_Addr, config->read("VI_RTSP_Addr", "").c_str());
	strcpy(info->IR_RTSP_Addr, config->read("IR_RTSP_Addr", "").c_str());

	info->VI_H264_Port = config->read("VI_H264_Port", 0);
	info->IR_H264_Port = config->read("IR_H264_Port", 0);
	info->GD_Send_XK_INFO_Port = config->read("GD_Send_XK_INFO_Port", 0);
	info->GD_Recv_XK_INFO_Port = config->read("GD_Recv_XK_INFO_Port", 0);

	info->AI_VI_ThreShold = config->read("AI_VI_ThreShold", 0.0F);
	info->AI_IR_ThreShold = config->read("AI_IR_ThreShold", 0.0F);

	strcpy(info->VI_OSD_NAME, config->read("VI_OSD_NAME", "").c_str());
	strcpy(info->IR_OSD_NAME, config->read("IR_OSD_NAME", "").c_str());
}

void init_pic_up_selfcheck_msg(PICUpSelfCheckStateStruct* msg)
{
	memset(msg, 0, sizeof(PICUpSelfCheckStateStruct));
	msg->sync_code = 0xEB90;
}

void init_xk_down_msg(XKDownMsg* msg)
{
	memset(msg, 0, sizeof(XKDownMsg));
	msg->sync_code1 = 0xEB;
	msg->sync_code2 = 0x90;
}

