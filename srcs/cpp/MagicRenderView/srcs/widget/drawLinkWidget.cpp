#include "drawLinkWidget.h"

#include "../app/application.h"

DrawLinkWidget::DrawLinkWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
}
