#pragma once

#include <QWidget>
#include "ui_serialportForm.h"
#include <myserial.h>
#include <QMessageBox>

class serialportForm : public QWidget
{
	Q_OBJECT

public:
	serialportForm(MySerial* serialport,QWidget *parent = Q_NULLPTR);
	~serialportForm();

private:
	Ui::serialportForm ui;
	MySerial* m_serialport = nullptr;

protected slots:
	void Onbtn_open();
};
