
#include "node/ui/windows/magicRenderViewWindow.h"
#include "setting/appInstance.h"

int main( int argc, char *argv[ ] ) {
	cyl::app::AppInstance app( argc, argv );
	
	cyl::ui::MagicRenderViewWindow mainwidget;
	mainwidget.show( );
	app.setWindowToIndexScreenCentre( 0 );
	return app.exec( );
}
