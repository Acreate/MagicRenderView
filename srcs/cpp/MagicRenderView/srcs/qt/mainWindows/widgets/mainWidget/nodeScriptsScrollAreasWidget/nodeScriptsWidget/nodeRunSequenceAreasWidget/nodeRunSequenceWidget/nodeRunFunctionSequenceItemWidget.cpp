#include "./nodeRunFunctionSequenceItemWidget.h"

#include <QLabel>
#include <QPainter>
#include <qboxlayout.h>

#include <qt/functionDeclaration/IFunctionDeclaration.h>

NodeRunFunctionSequenceItemWidget::NodeRunFunctionSequenceItemWidget( NodeRunSequenceWidget *node_run_sequence_widget, const std::shared_ptr< IFunctionDeclaration > &function_declaration ) : QWidget( node_run_sequence_widget ), itemParent( node_run_sequence_widget ) {
	IFunctionDeclaration *functionDeclaration = function_declaration.get( );
	if( functionDeclaration->isIsControlCode( ) == false )
		itemChild = nullptr;
	else
		itemChild = new NodeRunSequenceWidget( node_run_sequence_widget );

	auto oldLayout = layout( );
	if( oldLayout )
		delete oldLayout;
	auto mainLayout = new QVBoxLayout( this );
	auto title = new QLabel( this );
	mainLayout->addWidget( title );
	title->setAlignment( Qt::AlignCenter );
	title->setText( functionDeclaration->getDeclarationName( ) );
	itemActive = true;
}
NodeRunFunctionSequenceItemWidget::~NodeRunFunctionSequenceItemWidget( ) {
	itemParent->removeItem( this );
	disconnect( );
}
void NodeRunFunctionSequenceItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
