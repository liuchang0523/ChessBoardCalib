#include "stereo_calib.h"
#include "start_page.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	stereo_calib w;
	w.show();
	return a.exec();
}
