#include "varGenerateWidget.h"

#include <QPainter>

#include "mainWidget.h"

#include <qt/varType/I_Var.h>

#include <qt/application/application.h>
VarGenerateWidget::~VarGenerateWidget( ) {
	size_t count = mainWidgetGenerateVar.size( );
	auto dataPtr = mainWidgetGenerateVar.data( );
	size_t index = 0;

	for( ; index < count; ++index )
		delete dataPtr[ index ];
}
VarGenerateWidget::VarGenerateWidget( QWidget *parent_widget ) : QWidget( parent_widget ) {
	appInstance = Application::getApplicationInstancePtr( );
	varGenerate = appInstance->getVarGenerate( );
	keyFirst = "Application/MainWindow/MainWidget/VarGenerateWidget";
}

VarGenerateWidget::VarGenerateWidget( ) : VarGenerateWidget( nullptr ) {
}
void VarGenerateWidget::setMainWidget( MainWidget *const main_widget ) { mainWidget = main_widget; }
void VarGenerateWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkYellow );
}
