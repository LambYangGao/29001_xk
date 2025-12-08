#pragma execution_character_set("utf-8")
#include <QtWidgets/QApplication>
#include <QFile>
#include "fzqjMain_user.h"
#include "SDL2/SDL.h"
#undef main

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	QApplication a(argc, argv);

	QFile file(QStringLiteral("%1/abc.qss").arg(QCoreApplication::applicationDirPath()));
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	qApp->setStyleSheet(styleSheet);
	file.close();

	//login logregdlg;
	//logregdlg.exec();
	fzqjMain_user w;
	//fzqjMain w;
	//fzqjMain_test w;
	//fzqjReplay w;
	//yltdMain w;
	w.show();
	return a.exec();
}
