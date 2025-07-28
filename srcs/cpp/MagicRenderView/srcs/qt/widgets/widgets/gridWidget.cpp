#include "./gridWidget.h"

GridWidget::GridWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {

}
bool GridWidget::addNode( const IFunctionDeclaration &function_declaration ) {
	if( function_declaration.isIsValid( ) == false )
		return false;
	std::shared_ptr nodeGeneraterItem( std::make_shared< INodeGeneraterItem >( function_declaration ) );
	nodeGeneraterItems.emplace_back( nodeGeneraterItem );
	return true;
}
void GridWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void GridWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void GridWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
void GridWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
