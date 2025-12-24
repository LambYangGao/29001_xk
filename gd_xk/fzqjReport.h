#pragma once

#include <QMainWindow>
#include "ui_fzqjReport.h"
#include"protocol_fk.h"
#include <QString>

class fzqjReport : public QMainWindow
{
	Q_OBJECT

public:
	fzqjReport(QWidget *parent = nullptr);
	~fzqjReport(void);

	XKUpDevStateMsg manualTarget;
	void fzqjReport::init_windows(void);
signals:
	void sig_report_send(XKUpDevStateMsg in_msg);
public slots:
	void on_btn_report_send_clicked(void);
private:
	Ui::fzqjReportClass ui;
};
