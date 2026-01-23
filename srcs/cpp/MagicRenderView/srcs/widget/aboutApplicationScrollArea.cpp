#include "aboutApplicationScrollArea.h"

#include "../win/aboutApplicationWindow.h"
#include "aboutApplicationWidget.h"
AboutApplicationScrollArea::AboutApplicationScrollArea( AboutApplicationWindow *about_application_window_ptr ) : QScrollArea( about_application_window_ptr ), aboutApplicationWindowPtr( about_application_window_ptr ) {
	aboutApplicationWidgetPtr = new AboutApplicationWidget( about_application_window_ptr );
	setWidget( aboutApplicationWidgetPtr );
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
}
