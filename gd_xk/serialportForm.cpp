#include "serialportForm.h"

serialportForm::serialportForm(MySerial* serialport,QWidget *parent)
	: QWidget(parent)
	,m_serialport(serialport)
{
	ui.setupUi(this);

	QStringList portnamelist = m_serialport->ScanSerialPorts();

	for each (QString portname in portnamelist)
	{
		ui.cbx_portname->addItem(portname);
	}

	connect(ui.btn_open, SIGNAL(clicked()), this, SLOT(Onbtn_open()));
}

serialportForm::~serialportForm()
{

}

void serialportForm::Onbtn_open()
{
	m_serialport->setInfo(ui.cbx_portname->currentText()
		, ui.cbx_baudrate->currentText().toInt()
		, ui.cbx_parity->currentText().toInt()
		, ui.cbx_databits->currentText().toInt()
		, ui.cbx_stopbits->currentText().toInt());
	this->close();
}
