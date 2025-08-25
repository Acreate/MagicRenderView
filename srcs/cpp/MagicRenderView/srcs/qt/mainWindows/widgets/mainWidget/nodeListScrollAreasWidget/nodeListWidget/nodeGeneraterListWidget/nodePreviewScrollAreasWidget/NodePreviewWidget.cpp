#include "./NodePreviewWidget.h"

#include <QPainter>
#include <qevent.h>
#include <qgridlayout.h>

#include <qt/functionDeclaration/IFunctionDeclaration.h>

#include <qt/stacks/funStack/IFunStack.h>

#include "NodePreviewWidget/nodeFuncPreviewImageWidget.h"

NodePreviewWidget::NodePreviewWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ), mainLayout( nullptr ) {

}
NodePreviewWidget::~NodePreviewWidget( ) {
	size_t count = imageVector.size( );
	if( count == 0 )
		return;
	auto labelPtr = imageVector.data( );
	for( size_t index = 0; index < count; ++index )
		delete labelPtr[ index ];
}
void NodePreviewWidget::shortFunctionNodeWidget( ) {
	size_t count = imageVector.size( );
	if( count == 0 )
		return;
	auto data = imageVector.data( );
	if( mainLayout != nullptr )
		delete mainLayout;
	mainLayout = new QGridLayout( this );
	
	size_t layout = 0; // 层
	size_t lineCount = 4; // 最大个数
	auto previewImageWidget = data[ 0 ];
	mainLayout->addWidget( previewImageWidget, 0, 0 );
	for( size_t index = 1; index < count; ++index ) {
		previewImageWidget = data[ index ];
		size_t column = index % lineCount;
		if( column == 0 )
			++layout;
		mainLayout->addWidget( previewImageWidget, layout, column );
	}
}
void NodePreviewWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
void NodePreviewWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	shortFunctionNodeWidget( );
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
			label->setFixedSize( 100, 200 );
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
