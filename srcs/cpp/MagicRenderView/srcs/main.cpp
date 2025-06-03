#include <QApplication>
#include <QMainWindow>
int main( int argc, char *argv[ ] ) {
	QApplication app( argc, argv );
	
	QMainWindow mainwidget;
	mainwidget.show(  );
	return app.exec( );
}
