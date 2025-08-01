#include "./nodeGeneraterListWidget.h"
NodeGeneraterListWidget::NodeGeneraterListWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
	currentContentFunStack = nullptr;
}
bool NodeGeneraterListWidget::setCurrentFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	if( currentContentFunStack == fun_stack )
		return true;
	
	return false;
}
bool NodeGeneraterListWidget::setCurrentFunStackIndex( const size_t &fun_stack_index ) {
	return false;
}
std_shared_ptr< IFunStack > NodeGeneraterListWidget::getCurrentFunStack( ) {
	return currentContentFunStack;
}
std_shared_ptr< IFunStack > NodeGeneraterListWidget::getCurrentFunStackIndex( ) {
	return { };
}
bool NodeGeneraterListWidget::appendCurrentFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {
	return false;
}
void NodeGeneraterListWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
