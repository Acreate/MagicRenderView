#include "./nodePreviewScrollAreasWidget.h"

#include "../widgets/NodePreviewWidget.h"
NodePreviewScrollAreasWidget::NodePreviewScrollAreasWidget( QWidget *parent, Qt::WindowFlags flags ): QScrollArea( parent ) {
	nodePreviewWidget = new NodePreviewWidget( this, flags );
	setWidget( nodePreviewWidget );
	this->setWidgetResizable( true );
}
NodePreviewScrollAreasWidget::~NodePreviewScrollAreasWidget( ) {
}
const std_shared_ptr< IFunStack > & NodePreviewScrollAreasWidget::getFunStack( ) const {
	return nodePreviewWidget->getFunStack( );
}
bool NodePreviewScrollAreasWidget::setFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	return nodePreviewWidget->setFunStack( fun_stack );
}
