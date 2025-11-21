#include "drawNodeWidget.h"

#include "../../app/applicationInstance/application.h"
DrawNodeWidget::DrawNodeWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
}
