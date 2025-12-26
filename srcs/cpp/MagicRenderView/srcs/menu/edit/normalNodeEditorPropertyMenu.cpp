#include "normalNodeEditorPropertyMenu.h"
NormalNodeEditorPropertyMenu::NormalNodeEditorPropertyMenu( ) : QMenu( ) {
}
bool NormalNodeEditorPropertyMenu::initNormalNodeEditorPropertyMenu( ) {
	clear( );
	dislayMenu = addMenu( tr( "显示" ) );
	inputMneu = addMenu( tr( "输入" ) );
	dislayInputRef = inputMneu->addMenu( tr( "显示引用" ) );
	deleteInputAtOutputRef = inputMneu->addMenu( tr( "删除输出端口引用" ) );
	outputMenu = addMenu( tr( "输出" ) );
	dislayOutputRef = outputMenu->addMenu( tr( "显示引用" ) );
	deleteOutputAtInputRef = outputMenu->addMenu( tr( "删除输入端口引用" ) );
	return true;
}
bool NormalNodeEditorPropertyMenu::setNode( Node *node ) {
	if( node == nullptr )
		return false;
	actionMap.clear( );
	dislayMenu->clear( );
	dislayInputRef->clear( );
	deleteInputAtOutputRef->clear( );
	dislayOutputRef->clear( );
	deleteOutputAtInputRef->clear( );

	return true;
}
