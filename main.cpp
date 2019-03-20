#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Produs.h"
#include "service.h"
#include "Repo.h"
#include "gui.h"

void testall() {
	testProdus();
	testservice();
	testRepo();
}
int main(int argc, char *argv[])
{
	testall();
	QApplication a(argc, argv);
	FileRepo rep{ "Produse1.txt "};
	validator val;
	service serv{ rep,val };
	ProdGUI gui{ serv };
	gui.show();
	a.exec();
	_CrtDumpMemoryLeaks();
	return 0;
}
