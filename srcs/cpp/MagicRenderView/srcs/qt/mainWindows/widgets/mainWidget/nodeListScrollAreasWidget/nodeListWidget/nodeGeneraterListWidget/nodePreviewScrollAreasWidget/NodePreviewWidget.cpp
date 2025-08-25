#include "./NodePreviewWidget.h"

#include <QPainter>
#include <qevent.h>

#include <qt/functionDeclaration/IFunctionDeclaration.h>

#include <qt/stacks/funStack/IFunStack.h>

#include "NodePreviewWidget/nodeFuncPreviewImageWidget.h"

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
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::black );
}
void NodePreviewWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
void NodePreviewWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
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
	return true;
}
