#include "./NodePreviewWidget.h"

#include <qevent.h>

#include "nodeFuncPreviewImageWidget.h"

#include "../../functionDeclaration/IFunctionDeclaration.h"

#include "../../stacks/funStack/IFunStack.h"

NodePreviewWidget::NodePreviewWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
}
NodePreviewWidget::~NodePreviewWidget( ) {
	size_t count = imageVector.size( );
	if( count == 0 )
		return;
	auto labelPtr = imageVector.data( );
	for( size_t index = 0; index < count; ++index )
		delete labelPtr[ index ];
}
void NodePreviewWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

}
void NodePreviewWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	auto size = event->size( );
	auto imageWidget = size.width( ) / 5;
	double imageHeight = imageWidget * 1.8;
	imageSize = QSize( imageWidget, imageHeight );
	size_t count = imageVector.size( );
	if( count == 0 )
		return;
	auto labelPtr = imageVector.data( );
	int y = 25;
	int x = 25;
	size_t index = 0;
	NodeFuncPreviewImageWidget *nodeFuncPreviewImageWidget = labelPtr[ index ];
	nodeFuncPreviewImageWidget->setFixedSize( imageSize );
	nodeFuncPreviewImageWidget->move( x, y );
	for( index = 1; index < count; ++index ) {
		x += 25;
		if( index % 5 == 0 )
			y = y + imageHeight + 25;
		nodeFuncPreviewImageWidget = labelPtr[ index ];
		nodeFuncPreviewImageWidget->setFixedSize( imageSize );
		nodeFuncPreviewImageWidget->move( x, y );
	}
}
bool NodePreviewWidget::setFunStack( const std_shared_ptr< IFunStack > &fun_stack ) {

	// 检查函数数量，填充函数功能到窗口
	IFunStack *element = fun_stack.get( );
	auto functionDeclarations = element->getGenerFunctions( );
	size_t count = functionDeclarations.size( );
	if( count == 0 )
		return false;
	auto declarationPtr = functionDeclarations.data( );
	IFunctionDeclaration *functionElement;
	size_t index = 0;
	std_vector< NodeFuncPreviewImageWidget * > buff;
	for( functionElement = declarationPtr[ index ].get( ); index < count; ++index, functionElement = declarationPtr[ index ].get( ) )
		if( functionElement->isIsValid( ) == true ) {

			auto image = functionElement->getImage( );
			if( image == nullptr )
				continue;
			NodeFuncPreviewImageWidget *label = new NodeFuncPreviewImageWidget( this );
			if( label->setFunctionDeclaration( declarationPtr[ index ] ) == false ) {
				delete label;
				continue;
			}
			label->setFixedSize( imageSize );
			buff.emplace_back( label );
		}
	if( buff.size( ) == 0 )
		return false;
	count = imageVector.size( );
	auto labelPtr = imageVector.data( );
	for( index = 0; index < count; ++index )
		delete labelPtr[ index ];
	funStack = fun_stack;
	imageVector = buff;
	repaint( );
	return true;
}
