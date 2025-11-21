#include "drawLinkWidget.h"

#include "../../app/applicationInstance/application.h"
DrawLinkWidget::DrawLinkWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	appInstancePtr = Application::getInstancePtr( );
	nodeDirector = appInstancePtr->getNodeDirector( );
}
