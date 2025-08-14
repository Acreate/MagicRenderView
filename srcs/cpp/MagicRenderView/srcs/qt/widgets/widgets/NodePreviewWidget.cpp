#include "./NodePreviewWidget.h"

#include "../../functionDeclaration/IFunctionDeclaration.h"

#include "../../stacks/funStack/IFunStack.h"

NodePreviewWidget::NodePreviewWidget( QWidget *parent, Qt::WindowFlags flags ) : QWidget( parent, flags ) {
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
	for( functionElement = declarationPtr[ index ].get( ); index < count; ++index, functionElement = declarationPtr[ index ].get( ) )
		if( functionElement->isIsValid( ) == true ) {
			// todo : 生成窗口控件
		}

	
	funStack = fun_stack;
	return true;
}
