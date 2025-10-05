#include "varEditorItemWidget.h"

#include <qboxlayout.h>
#include <qevent.h>

#include "../varGenerateWidget.h"

#include "../../application/application.h"
Imp_StaticMetaInfo( VarEditorItemWidget, QObject::tr( "VarEditorItemWidget" ), QObject::tr( "item" ) );
VarEditorItemWidget::VarEditorItemWidget( QWidget *parent ) : QWidget( parent ), varGenerateWidget( qobject_cast< VarGenerateWidget * >( parent ) ) {
	application = Application::getApplicationInstancePtr( );
	varGenerate = application->getVarGenerate( );
}
void VarEditorItemWidget::init( VarGenerateWidget *var_generate_widget ) {
	varGenerateWidget = var_generate_widget;
	setParent( var_generate_widget );
	connect( this, &VarEditorItemWidget::delEditorEvent, var_generate_widget, &VarGenerateWidget::delVarEditorPanle );
	connect( this, &VarEditorItemWidget::resetEditorSizeEvent, var_generate_widget, &VarGenerateWidget::resetSizeVarEditorPanle );
}
const type_info & VarEditorItemWidget::getStaticVarTypeInfo( ) {
	return typeid( nullptr );
}
void VarEditorItemWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	emit resetEditorSizeEvent( this, event->oldSize( ), event->size( ) );
}
