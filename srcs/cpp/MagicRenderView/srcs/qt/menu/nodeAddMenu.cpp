#include "nodeAddMenu.h"

#include "action/nodeAddAction.h"

#include <qt/tools/tools.h>

#include "qt/functionDeclaration/baseArithmetic/addFunctionDeclaration.h"
#include "qt/functionDeclaration/baseArithmetic/divFunctionDeclaration.h"
#include "qt/functionDeclaration/baseArithmetic/mulFunctionDeclaration.h"
#include "qt/functionDeclaration/baseArithmetic/subFunctionDeclaration.h"

NodeAddMenu::NodeAddMenu( QWidget *parent ) : QMenu( parent ) {
	connect( this, &QMenu::triggered, [this] ( QAction *action ) {
		auto nodeAddAction = qobject_cast< NodeAddAction * >( action );
		if( nodeAddAction )
			emit activeNodeAction( nodeAddAction );
		else
			emit activeQAction( action );
	} );
	/// 基本运算菜单
	QMenu *baseArithmetic = new QMenu( this );
	baseArithmetic->setTitle( "基础四则运算" );
	addMenu( baseArithmetic );

	std::shared_ptr< IFunctionDeclaration > pFunctionDeclaration; // 用作指向函数对象指针
	QAction *newNodeAction;// 用作新建菜单项

	/// * 加法
	pFunctionDeclaration = std::make_shared< AddFunctionDeclaration >( );
	newNodeAction = new NodeAddAction( baseArithmetic, pFunctionDeclaration );
	newNodeAction->setText( pFunctionDeclaration->getFunctionDeclarationName( ) );
	baseArithmetic->addAction( newNodeAction );
	/// * 减法
	pFunctionDeclaration = std::make_shared< SubFunctionDeclaration >( );
	newNodeAction = new NodeAddAction( baseArithmetic, pFunctionDeclaration );
	newNodeAction->setText( pFunctionDeclaration->getFunctionDeclarationName( ) );
	baseArithmetic->addAction( newNodeAction );
	/// * 乘法
	pFunctionDeclaration = std::make_shared< MulFunctionDeclaration >( );
	newNodeAction = new NodeAddAction( baseArithmetic, pFunctionDeclaration );
	newNodeAction->setText( pFunctionDeclaration->getFunctionDeclarationName( ) );
	baseArithmetic->addAction( newNodeAction );
	/// * 除法
	pFunctionDeclaration = std::make_shared< DivFunctionDeclaration >( );
	newNodeAction = new NodeAddAction( baseArithmetic, pFunctionDeclaration );
	newNodeAction->setText( pFunctionDeclaration->getFunctionDeclarationName( ) );
	baseArithmetic->addAction( newNodeAction );
}
NodeAddMenu::~NodeAddMenu( ) {
}
