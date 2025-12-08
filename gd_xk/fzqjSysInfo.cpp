#include "fzqjSysInfo.h"
#include <QtCore/qprocess.h>

using namespace std;
fzqjSysInfo::fzqjSysInfo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    
}

fzqjSysInfo::~fzqjSysInfo(void)
{}



void fzqjSysInfo::on_btn_open_pic_save_path_2_clicked(void)
{
    QString filepath = ui.txt_pic_save_path_2->text();
    filepath.replace("/","\\");
    QProcess process;
    process.startDetached("explorer",QStringList()<<QString("/root,") << QString("%1").arg(filepath));
}

void fzqjSysInfo::on_btn_open_video_save_path_2_clicked(void)
{
    QString filepath = ui.txt_video_save_path_2->text();
    filepath.replace("/", "\\");
    QProcess process;
    process.startDetached("explorer", QStringList() << QString("/root,") << QString("%1").arg(filepath));
}

void fzqjSysInfo::on_btn_open_log_save_path_2_clicked(void)
{
    QString filepath = ui.txt_log_save_path_2->text();
    filepath.replace("/", "\\");
    QProcess process;
    process.startDetached("explorer", QStringList() << QString("/root,") << QString("%1").arg(filepath));
}

void fzqjSysInfo::on_btn_adaptive_view_clicked(void)
{
   /* m_configManager->set("IS_ADAPT_VIEW", ui.cbx_guidance_adaptive->isChecked() ? "1" : "0");
    m_configManager->print("Config.ini");
    emit sigUpdatepixnums();*/
}

void fzqjSysInfo::on_btn_adaptive_view_piex_vi_clicked(void)
{
    //string ui_str = ui.txt_adaptive_view_piex_vi->text().toStdString();
    //string config_str = m_configManager->read("ADPAT_VIEW_PIXE_VI", "");
    //if (ui_str == config_str)
    //{
    //    return;
    //}
    //int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
    //    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    //switch (ret)
    //{
    //case QMessageBox::Yes:
    //    //此处填入操作，例如msgBox.setText("you choose Save button!");
    //    m_configManager->set("ADPAT_VIEW_PIXE_VI", ui.txt_adaptive_view_piex_vi->text().toStdString());
    //    m_configManager->print("Config.ini");
    //    emit sigUpdatepixnums();
    //    break;
    //case QMessageBox::No:
    //    //此处填入操作
    //    break;
    //default:
    //    break;
    //}
}

void fzqjSysInfo::on_btn_adaptive_view_piex_ir_clicked(void)
{
    //string ui_str = ui.txt_adaptive_view_piex_ir->text().toStdString();
    //string config_str = m_configManager->read("ADPAT_VIEW_PIXE_IR", "");
    //if (ui_str == config_str)
    //{
    //    return;
    //}
    //int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
    //    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    //switch (ret)
    //{
    //case QMessageBox::Yes:
    //    //此处填入操作，例如msgBox.setText("you choose Save button!");
    //    m_configManager->set("ADPAT_VIEW_PIXE_IR", ui.txt_adaptive_view_piex_ir->text().toStdString());
    //    m_configManager->print("Config.ini");
    //    emit sigUpdatepixnums();
    //    break;
    //case QMessageBox::No:
    //    //此处填入操作
    //    break;
    //default:
    //    break;
    //}
}

void fzqjSysInfo::on_btn_guidance_adaptive_size_clicked(void)
{
    txtToConfig(ui.txt_guidance_adaptive_size, "GUIDE_ADPAT_VIEW_SIZE");
    emit sigUpdatepixnums();
}

void fzqjSysInfo::on_btn_guidance_adaptive_pixe_vi_clicked(void)
{
    txtToConfig(ui.txt_guidance_adaptive_pixe_vi, "GUIDE_ADPAT_VIEW_PIXE_VI");
    emit sigUpdatepixnums();
}

void fzqjSysInfo::on_btn_guidance_adaptive_pixe_ir_clicked(void)
{
    txtToConfig(ui.txt_guidance_adaptive_pixe_ir, "GUIDE_ADPAT_VIEW_PIXE_IR");
    emit sigUpdatepixnums();
}

void fzqjSysInfo::on_btn_guidance_adaptive_clicked(void)
{
   /* m_configManager->set("IS_GUIDE_ADAPT_VIEW", ui.cbx_guidance_adaptive->isChecked() ? "1" : "0");
    m_configManager->print("Config.ini");
    emit sigUpdatepixnums();*/
}

void fzqjSysInfo::on_btn_GD_Reboot_clicked(void)
{
    emit sigReboot();
}

void fzqjSysInfo::on_btn_getXKInfo_2_clicked(void)
{
    init_XKConfigInfo(m_configManager, &m_xk_configinfo);
    emit sig_InitConfigInfo(m_xk_configinfo);
    ui.txt_recv_GD_Port_2->setText(QString::number(m_xk_configinfo.XK_Recv_GD_INFO_Port));
    ui.txt_send_GD_Port_2->setText(QString::number(m_xk_configinfo.XK_Send_GD_INFO_Port));
    ui.txt_recv_ZK_Port_2->setText(QString::number(m_xk_configinfo.FK_Send_XK_INFO_Port));
    ui.txt_send_ZK_Port_2->setText(QString::number(m_xk_configinfo.XK_Send_FK_INFO_Port));

    ui.txt_GD_IP_2->setText(m_xk_configinfo.GD_IP);
    ui.txt_ZK_IP_2->setText(m_xk_configinfo.FK_IP);
    ui.txt_XK_IP_2->setText(m_xk_configinfo.XK_IP);

    ui.txt_VI_video_addr_2->setText(m_xk_configinfo.VI_RTSP_Addr);
    ui.txt_IR_video_addr_2->setText(m_xk_configinfo.IR_RTSP_Addr);

    ui.txt_pic_save_path_2->setText(m_xk_configinfo.PIC_SAVE_Addr);
    ui.txt_video_save_path_2->setText(m_xk_configinfo.VIDEO_SAVE_Addr);
    ui.txt_log_save_path_2->setText(m_xk_configinfo.LOG_SAVE_Addr);

    ui.cbx_sound_warning_2->setChecked(m_xk_configinfo.IS_WARNING_TARGET);
    //ui.cbx_guidance_adaptive->setChecked(m_xk_configinfo.IS_GUIDE_ADAPT_VIEW);
    ui.txt_guidance_adaptive_pixe_vi->setText(QString::number(m_xk_configinfo.GUIDE_ADPAT_VIEW_PIXE_VI));
    ui.txt_guidance_adaptive_pixe_ir->setText(QString::number(m_xk_configinfo.GUIDE_ADPAT_VIEW_PIXE_IR));
    ui.txt_guidance_adaptive_size->setText(QString::number(m_xk_configinfo.GUIDE_ADPAT_VIEW_SIZE));
    ui.txt_DEV_ID_2->setText(QString::fromStdString(m_configManager->read("DEV_ID", "")));
    ui.txt_SOURCE_ID_2->setText(QString::fromStdString(m_configManager->read("SOURCE_ID", "")));
    
}

void fzqjSysInfo::on_btn_recv_GD_Port_2_clicked(void)
{
    string ui_str= ui.txt_recv_GD_Port_2->text().toStdString();
    string config_str=m_configManager->read("XK_Recv_GD_INFO_Port","");
    if (ui_str== config_str)
    {
        return;
    }
    int ret=QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        m_configManager->set("XK_Recv_GD_INFO_Port", ui.txt_recv_GD_Port_2->text().toStdString());
        m_configManager->print("Config.ini");
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }   
}


void fzqjSysInfo::on_btn_send_GD_Port_2_clicked(void)
{
    string ui_str = ui.txt_send_GD_Port_2->text().toStdString();
    string config_str = m_configManager->read("XK_Send_GD_INFO_Port", "");
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        m_configManager->set("XK_Send_GD_INFO_Port", ui.txt_send_GD_Port_2->text().toStdString());
        m_configManager->print("Config.ini");
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
gg:;

}

void fzqjSysInfo::on_btn_recv_ZK_Port_2_clicked(void)
{
    string ui_str = ui.txt_recv_ZK_Port_2->text().toStdString();
    string config_str = m_configManager->read("FK_Send_XK_INFO_Port", "");
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        m_configManager->set("FK_Send_XK_INFO_Port", ui.txt_recv_ZK_Port_2->text().toStdString());
        m_configManager->print("Config.ini");
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
}

void fzqjSysInfo::on_btn_send_ZK_Port_2_clicked(void)
{
    string ui_str = ui.txt_send_ZK_Port_2->text().toStdString();
    string config_str = m_configManager->read("XK_Send_FK_INFO_Port", "");
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        m_configManager->set("XK_Send_FK_INFO_Port", ui.txt_send_ZK_Port_2->text().toStdString());
        m_configManager->print("Config.ini");
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
gg:;
}

void fzqjSysInfo::on_btn_GD_IP_2_clicked(void)
{
    bool Is_Ip = is_ip_ture(ui.txt_GD_IP_2->text());
    if (!Is_Ip)
    {
        QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("ip地址错误"));
        return;
    }
    string ui_str = ui.txt_GD_IP_2->text().toStdString();
    string config_str = m_configManager->read("GD_IP", "");
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
    {
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        QString vi_url_ = "rtsp://" + ui.txt_GD_IP_2->text() + ":554/vl";
        QString ir_url_ = "rtsp://" + ui.txt_GD_IP_2->text() + ":555/ir";
        m_configManager->set("GD_IP", ui.txt_GD_IP_2->text().toStdString());
        m_configManager->set("VI_RTSP_Addr", vi_url_.toStdString());
        m_configManager->set("IR_RTSP_Addr", ir_url_.toStdString());
        m_configManager->print("Config.ini");
        break;
    }
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
    on_btn_getXKInfo_2_clicked();
}

void fzqjSysInfo::on_btn_ZK_IP_2_clicked()
{
    bool Is_Ip = is_ip_ture(ui.txt_ZK_IP_2->text());
    if (!Is_Ip)
    {
        QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("ip地址错误"));
        return;
    }
    string ui_str = ui.txt_ZK_IP_2->text().toStdString();
    string config_str = m_configManager->read("FK_IP", "");
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        m_configManager->set("FK_IP", ui.txt_ZK_IP_2->text().toStdString());
        m_configManager->print("Config.ini");
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
}

void fzqjSysInfo::on_btn_XK_IP_2_clicked(void)
{
    bool Is_Ip = is_ip_ture(ui.txt_XK_IP_2->text());
    if (!Is_Ip)
    {
        QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("ip地址错误"));
        return;
    }
    string ui_str = ui.txt_XK_IP_2->text().toStdString();
    string config_str = m_configManager->read("XK_IP", "");
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        m_configManager->set("XK_IP", ui.txt_XK_IP_2->text().toStdString());
        m_configManager->print("Config.ini");
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
}

void fzqjSysInfo::on_btn_VI_video_addr_2_clicked(void)
{
    m_configManager->set("VI_RTSP_Addr", ui.txt_VI_video_addr_2->text().toStdString());
    m_configManager->print("Config.ini");
}

void fzqjSysInfo::on_btn_IR_video_addr_2_clicked(void)
{
    m_configManager->set("IR_RTSP_Addr", ui.txt_IR_video_addr_2->text().toStdString());
    m_configManager->print("Config.ini");
}

void fzqjSysInfo::on_btn_pic_save_path_2_clicked(void)
{
    QString filepath = QString::fromStdString( m_configManager->read("PIC_SAVE_Addr", ""));
    QString dir = QFileDialog::getExistingDirectory(this, QStringLiteral("保存图片地址"), filepath, QFileDialog::ShowDirsOnly);
    if (dir.isEmpty())
    {
        return;
    }
    else
    {
        filepath = dir;
        ui.txt_pic_save_path_2->setText(filepath);
    }
    m_configManager->set("PIC_SAVE_Addr", ui.txt_pic_save_path_2->text().toStdString());
    m_configManager->print("Config.ini");
    on_btn_getXKInfo_2_clicked();
}

void fzqjSysInfo::on_btn_video_save_path_2_clicked(void)
{
    QString filepath = QString::fromStdString(m_configManager->read("VIDEO_SAVE_Addr", ""));
    QString dir = QFileDialog::getExistingDirectory(this, QStringLiteral("保存视频地址"), filepath, QFileDialog::ShowDirsOnly);
    if (dir.isEmpty())
    {
        return;
    }
    else
    {
        filepath = dir;
        ui.txt_video_save_path_2->setText(filepath);
    }
    m_configManager->set("VIDEO_SAVE_Addr", ui.txt_video_save_path_2->text().toStdString());
    m_configManager->print("Config.ini");
    on_btn_getXKInfo_2_clicked();
}

void fzqjSysInfo::on_btn_log_save_path_2_clicked(void)
{
    QString filepath = QString::fromStdString(m_configManager->read("LOG_SAVE_Addr", ""));
    QString dir = QFileDialog::getExistingDirectory(this, QStringLiteral("保存日志地址"), filepath, QFileDialog::ShowDirsOnly);
    if (dir.isEmpty())
    {
        return;
    }
    else
    {
        filepath = dir;
        ui.txt_log_save_path_2->setText(filepath);
    }
    m_configManager->set("LOG_SAVE_Addr", ui.txt_log_save_path_2->text().toStdString());
    m_configManager->print("Config.ini");
    on_btn_getXKInfo_2_clicked();
}

void fzqjSysInfo::on_btn_sound_warning_2_clicked(void)
{
    m_configManager->set("IS_WARNING_TARGET", ui.cbx_sound_warning_2->isChecked()?"1":"0");
    m_configManager->print("Config.ini");
}

void fzqjSysInfo::on_btn_DEV_ID_2_clicked(void)
{
    m_configManager->set("DEV_ID", ui.txt_DEV_ID_2->text().toStdString());
    m_configManager->print("Config.ini");
}

void fzqjSysInfo::on_btn_SOURCE_ID_2_clicked(void)
{
    m_configManager->set("SOURCE_ID", ui.txt_SOURCE_ID_2->text().toStdString());
    m_configManager->print("Config.ini");
}

void fzqjSysInfo::on_btn_getGDInfo_2_clicked(void)
{
    m_xk_down_msg.msg_type = E_FK_SYS_CONFIG_INFO;
    emit sig_sendMsg2Pic(m_xk_down_msg);
    m_xk_down_msg.msg_type = E_FK_BUTT;
}


void fzqjSysInfo::RefreshGDConfig(GDConfigInfo m_gd_configinfo)
{
    ui.txt_GD_recv_XK_Port_2->setText(QString::number(m_gd_configinfo.GD_Recv_XK_INFO_Port));
    ui.txt_GD_send_XK_Port_2->setText(QString::number(m_gd_configinfo.GD_Send_XK_INFO_Port));
    ui.txt_GD_GD_IP_2->setText(m_gd_configinfo.GD_IP);
    ui.txt_GD_XK_IP_2->setText(m_gd_configinfo.XK_IP);
    ui.txt_GD_VI_OSD_2->setText(m_gd_configinfo.VI_OSD_NAME);
    ui.txt_GD_IR_OSD_2->setText(m_gd_configinfo.IR_OSD_NAME);
    ui.txt_GD_VI_threshold_2->setText(QString::number(m_gd_configinfo.AI_VI_ThreShold));
    ui.txt_GD_IR_threshold_2->setText(QString::number(m_gd_configinfo.AI_IR_ThreShold));
}

void fzqjSysInfo::on_btn_watch_dog_reboot_clicked(void)
{
    emit sigWatchDogMsg(0);
}

void fzqjSysInfo::on_btn_watch_dog_auto_reboot_start_clicked(void)
{
    emit sigWatchDogMsg(1);
}

void fzqjSysInfo::on_btn_watch_dog_auto_reboot_stop_clicked(void)
{
    emit sigWatchDogMsg(2);
}

void fzqjSysInfo::on_btn_watch_dog_stop_clicked(void)
{
    emit sigWatchDogMsg(3);
}

void fzqjSysInfo::on_btn_GD_recv_XK_Port_2_clicked(void)
{
    string ui_str = ui.txt_GD_recv_XK_Port_2->text().toStdString();
    string config_str = m_configManager->read("GD_Recv_XK_INFO_Port", "");
    std::string str = "GD_Recv_XK_INFO_Port";
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        strcpy(m_xk_down_config.key, str.c_str());
        strcpy(m_xk_down_config.value, ui.txt_GD_recv_XK_Port_2->text().toStdString().c_str());
        m_xk_down_config.key_len = str.length();
        m_xk_down_config.value_len = ui.txt_GD_recv_XK_Port_2->text().length();
        emit sig_sendConfig2Pic(m_xk_down_config);
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
}

void fzqjSysInfo::on_btn_GD_send_XK_Port_2_clicked(void)
{
    string ui_str = ui.txt_GD_send_XK_Port_2->text().toStdString();
    string config_str = m_configManager->read("GD_Send_XK_INFO_Port", "");
    std::string str = "GD_Send_XK_INFO_Port";
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        strcpy(m_xk_down_config.key, str.c_str());
        strcpy(m_xk_down_config.value, ui.txt_GD_send_XK_Port_2->text().toStdString().c_str());
        m_xk_down_config.key_len = str.length();
        m_xk_down_config.value_len = ui.txt_GD_send_XK_Port_2->text().length();
        emit sig_sendConfig2Pic(m_xk_down_config);
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
gg:;
}

void fzqjSysInfo::on_btn_GD_GD_IP_2_clicked(void)
{
    bool Is_Ip = is_ip_ture(ui.txt_GD_GD_IP_2->text());
    if (!Is_Ip)
    {
        QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("ip地址错误"));
        return;
    }
    string ui_str = ui.txt_GD_GD_IP_2->text().toStdString();
    string config_str = m_configManager->read("GD_IP", "");
    std::string str = "GD_IP";
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        strcpy(m_xk_down_config.key, str.c_str());
        strcpy(m_xk_down_config.value, ui.txt_GD_GD_IP_2->text().toStdString().c_str());
        m_xk_down_config.key_len = str.length();
        m_xk_down_config.value_len = ui.txt_GD_GD_IP_2->text().length();
        emit sig_sendConfig2Pic(m_xk_down_config);
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
}

bool fzqjSysInfo::is_ip_ture(QString in_ip)
{
    QString text255 = "(25[0-5])|(2[0-4][0-9])|(1[0-9][0-9])|([1-9][0-9])|([0-9])";//0-255
    QString rxpStr = QString("^(%1)\\.(%1)\\.(%1)\\.(%1)$").arg(text255);//判断ip
    QRegExp regexp1(rxpStr);

        if (regexp1.exactMatch(in_ip)==false)
        {
            return false;
        }
    return true;
}

void fzqjSysInfo::txtToConfig(QLineEdit* in_line, QString in_url)
{
    string ui_str = in_line->text().toStdString();
    string config_str = m_configManager->read(in_url.toStdString(), "");
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        m_configManager->set(in_url.toStdString(), in_line->text().toStdString());
        m_configManager->print("Config.ini");
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
}



void fzqjSysInfo::on_btn_GD_XK_IP_2_clicked(void)
{
    bool Is_Ip = is_ip_ture(ui.txt_GD_XK_IP_2->text());
    if (!Is_Ip)
    {
        QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("ip地址错误"));
        return;
    }
    string ui_str = ui.txt_GD_XK_IP_2->text().toStdString();
    string config_str = m_configManager->read("XK_IP", "");
    std::string str = "XK_IP";
    if (ui_str == config_str)
    {
        return;
    }
    int ret = QMessageBox::critical(this, QStringLiteral("确认弹窗"), QStringLiteral("是否进行修改"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Yes:
        //此处填入操作，例如msgBox.setText("you choose Save button!");
        strcpy(m_xk_down_config.key, str.c_str());
        strcpy(m_xk_down_config.value, ui.txt_GD_XK_IP_2->text().toStdString().c_str());
        m_xk_down_config.key_len = str.length();
        m_xk_down_config.value_len = ui.txt_GD_XK_IP_2->text().length();
        emit sig_sendConfig2Pic(m_xk_down_config);
        break;
    case QMessageBox::No:
        //此处填入操作
        break;
    default:
        break;
    }
}

//wchar_t test_buffer[256];
//大发噶但是
void fzqjSysInfo::on_btn_GD_VI_OSD_2_clicked(void)
{
    std::string str = "VI_OSD_NAME_WSTR";
    memset(m_xk_down_config.key, 0, sizeof(m_xk_down_config.key));
    memset(m_xk_down_config.value, 0, sizeof(m_xk_down_config.value));
    strcpy(m_xk_down_config.key, str.c_str());
    wcscpy((wchar_t*)m_xk_down_config.value, ui.txt_GD_VI_OSD_2->text().toStdWString().c_str());
    //wcscpy(test_buffer, ui.txt_GD_VI_OSD->text().toStdWString().c_str());
    m_xk_down_config.key_len = str.length();
    m_xk_down_config.value_len = ui.txt_GD_VI_OSD_2->text().length() * 2;
    emit sig_sendConfig2Pic(m_xk_down_config);
    str = "VI_OSD_NAME";
    memset(m_xk_down_config.key, 0, sizeof(m_xk_down_config.key));
    memset(m_xk_down_config.value, 0, sizeof(m_xk_down_config.value));
    strcpy(m_xk_down_config.key, str.c_str());
    strcpy(m_xk_down_config.value, ui.txt_GD_VI_OSD_2->text().toStdString().c_str());
    m_xk_down_config.key_len = str.length();
    m_xk_down_config.value_len = ui.txt_GD_VI_OSD_2->text().length();
    emit sig_sendConfig2Pic(m_xk_down_config);
}

void fzqjSysInfo::on_btn_GD_IR_OSD_2_clicked(void)
{
    string str = "IR_OSD_NAME_WSTR";
    memset(m_xk_down_config.key, 0, sizeof(m_xk_down_config.key));
    memset(m_xk_down_config.value, 0, sizeof(m_xk_down_config.value));
    strcpy(m_xk_down_config.key, str.c_str());
    //strcpy(m_xk_down_config.value, ui.txt_GD_IR_OSD->text().toStdString().c_str());
    wcscpy((wchar_t*)m_xk_down_config.value, ui.txt_GD_IR_OSD_2->text().toStdWString().c_str());
    m_xk_down_config.key_len = str.length();
    m_xk_down_config.value_len = ui.txt_GD_IR_OSD_2->text().length() * 2;
    emit sig_sendConfig2Pic(m_xk_down_config);
    str = "IR_OSD_NAME";
    memset(m_xk_down_config.key, 0, sizeof(m_xk_down_config.key));
    memset(m_xk_down_config.value, 0, sizeof(m_xk_down_config.value));
    strcpy(m_xk_down_config.key, str.c_str());
    strcpy(m_xk_down_config.value, ui.txt_GD_IR_OSD_2->text().toStdString().c_str());
    m_xk_down_config.key_len = str.length();
    m_xk_down_config.value_len = ui.txt_GD_IR_OSD_2->text().length();
    emit sig_sendConfig2Pic(m_xk_down_config);
}

void fzqjSysInfo::on_btn_GD_VI_threshold_2_clicked(void)
{
    string str = "AI_VI_ThreShold";
    strcpy(m_xk_down_config.key, str.c_str());
    strcpy(m_xk_down_config.value, ui.txt_GD_VI_threshold_2->text().toStdString().c_str());
    m_xk_down_config.key_len = str.length();
    m_xk_down_config.value_len = ui.txt_GD_VI_threshold_2->text().length();
    emit sig_sendConfig2Pic(m_xk_down_config);
}

void fzqjSysInfo::on_btn_GD_IR_threshold_2_clicked(void)
{
    string str = "AI_IR_ThreShold";
    strcpy(m_xk_down_config.key, str.c_str());
    strcpy(m_xk_down_config.value, ui.txt_GD_IR_threshold_2->text().toStdString().c_str());
    m_xk_down_config.key_len = str.length();
    m_xk_down_config.value_len = ui.txt_GD_IR_threshold_2->text().length();
    emit sig_sendConfig2Pic(m_xk_down_config);
}