#include "normalNodeEditorPropertyMenu.h"

#include "../../app/application.h"
#include "../../director/nodeDirector.h"
#include "../../node/node/node.h"
#include "../../node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h"
#include "../../node/port/inputPort/inputPort.h"
#include "../../node/port/outputPort/outputPort.h"
#include "action/autoAction.h"
bool NormalNodeEditorPropertyMenu::extendQActionArchiveVectorCount( size_t extendCount ) {
	size_t newCount = qactionArchiveCount + extendCount;
	if( qactionArchiveCount > newCount ) // 数据被截断
		return false;
	qactionArchiveVector.resize( newCount, nullptr );
	actionArchiveArrayPtr = qactionArchiveVector.data( );
	for( ; qactionArchiveCount < newCount; ++qactionArchiveCount )
		actionArchiveArrayPtr[ qactionArchiveCount ] = new AutoAction;
	return true;
}
bool NormalNodeEditorPropertyMenu::appendRmoveOutputRefActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port ) {
	unLinkPortActionInputMap.emplace_back( ActionPair( auto_action, output_port, input_port ) );
	deleteInputAtOutputRef->addAction( auto_action );
	return true;
}
bool NormalNodeEditorPropertyMenu::appendRmoveInputRefActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port ) {
	unLinkPortActionOutputMap.emplace_back( ActionPair( auto_action, output_port, input_port ) );
	deleteOutputAtInputRef->addAction( auto_action );
	return true;
}
void NormalNodeEditorPropertyMenu::removeInoutPortRefLinkAction( QAction *tr_obj_ptr ) {
	if( unLinkPortActionInputMapCount == 0 )
		return;
	// 触发端口删除
	size_t index;
	for( index = 0; index < unLinkPortActionInputMapCount; ++index )
		if( unLinkPortActionInputMapArrayPtr[ index ].getTrigAction( ) == tr_obj_ptr ) {
			emit unLink_signal( this, unLinkPortActionInputMapArrayPtr[ index ].getOutputPort( ), unLinkPortActionInputMapArrayPtr[ index ].getInputPort( ) );
			return;
		}
}
void NormalNodeEditorPropertyMenu::removeOutoutPortRefLinkAction( QAction *tr_obj_ptr ) {
	if( unLinkPortActionOutputMapCount == 0 )
		return;
	// 触发端口删除
	size_t index;
	for( index = 0; index < unLinkPortActionOutputMapCount; ++index )
		if( unLinkPortActionOutputMapArrayPtr[ index ].getTrigAction( ) == tr_obj_ptr ) {
			emit unLink_signal( this, unLinkPortActionOutputMapArrayPtr[ index ].getOutputPort( ), unLinkPortActionOutputMapArrayPtr[ index ].getInputPort( ) );
			return;
		}
}
void NormalNodeEditorPropertyMenu::displayInfoWidget( QAction *tr_obj_ptr ) {
	if( tr_obj_ptr != displayInfoWidgetAction )
		return;
	nodeInfoWidget->show( );
	emit show_node_edit_info_widget_signal( this, currentNode, nodeInfoWidget );
}
void NormalNodeEditorPropertyMenu::displayAtNodEnsureToWidget( QAction *tr_obj_ptr ) {
}
NormalNodeEditorPropertyMenu::NormalNodeEditorPropertyMenu( ) : QMenu( ) {
	currentNode = nullptr;
	qactionArchiveCount = 0;
	actionArchiveArrayPtr = nullptr;
	displayInfoWidgetAction = new AutoAction( tr( "显示编辑菜单" ) );
	noteInfoWidgetAction = new AutoAction( tr( "不存在匹配窗口" ) );
	noteInfoWidgetAction->setEnabled( false );
	noteRemoveOutputLinkAction = new AutoAction( tr( "不存在匹配输出引用" ) );
	noteRemoveOutputLinkAction->setEnabled( false );
	noteRemoveInputputLinkAction = new AutoAction( tr( "不存在匹配输入引用" ) );
	noteRemoveInputputLinkAction->setEnabled( false );
}
NormalNodeEditorPropertyMenu::~NormalNodeEditorPropertyMenu( ) {
	size_t index;
	if( qactionArchiveCount )
		for( index = 0; index < qactionArchiveCount; ++index )
			delete actionArchiveArrayPtr[ index ];
	delete noteInfoWidgetAction;
	delete noteRemoveOutputLinkAction;
	delete noteRemoveInputputLinkAction;
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
	connect( deleteOutputAtInputRef, &QMenu::triggered, this, &NormalNodeEditorPropertyMenu::removeOutoutPortRefLinkAction );
	connect( deleteInputAtOutputRef, &QMenu::triggered, this, &NormalNodeEditorPropertyMenu::removeInoutPortRefLinkAction );
	connect( dislayMenu, &QMenu::triggered, this, &NormalNodeEditorPropertyMenu::displayInfoWidget );
	return true;
}
bool NormalNodeEditorPropertyMenu::setNode( Node *node ) {
	if( node == nullptr )
		return false;
	currentNode = node;
	nodeInfoWidget = nullptr;
	unLinkPortActionInputMap.clear( );
	unLinkPortActionOutputMap.clear( );
	dislayMenu->clear( );
	dislayInputRef->clear( );
	deleteInputAtOutputRef->clear( );
	dislayOutputRef->clear( );
	deleteOutputAtInputRef->clear( );

	if( qactionArchiveCount == 0 )
		extendQActionArchiveVectorCount( 1024 );
	// 添加显示菜单
	nodeInfoWidget = Application::getInstancePtr( )->getNodeDirector( )->getNodeWidgeInfo( node );
	if( nodeInfoWidget ) {
		displayInfoWidgetAction->setText( nodeInfoWidget->getTitleText( ) );
		dislayMenu->addAction( displayInfoWidgetAction );
	} else
		dislayMenu->addAction( noteInfoWidgetAction );

	size_t userCount = 0;
	size_t modCount = 0;
	size_t refOutputCount = 0;
	size_t refCount;
	size_t refIndex;
	size_t index;
	size_t count;
	InputPort *inputPort;
	OutputPort *outputPort;
	InputPort **inputPortArrayPtr;
	OutputPort **outputPortArrayPtr;

	count = node->inputPortVector.size( );
	inputPortArrayPtr = node->inputPortVector.data( );
	for( index = 0; index < count; ++index ) {
		refCount = inputPortArrayPtr[ index ]->refOutputPortVector.size( );
		if( refCount == 0 )
			continue;
		refOutputCount += refCount;
		modCount = qactionArchiveCount - userCount; // 剩余数量
		// 当前数量无法满足需求
		if( modCount < refOutputCount )
			// 扩展一次，失败
			if( extendQActionArchiveVectorCount( 1024 + refOutputCount + qactionArchiveCount ) == false )
				// 使用更加小的扩展量
				if( extendQActionArchiveVectorCount( refOutputCount + qactionArchiveCount ) == false )
					return false; // 无法满足扩展需求
		// 添加到 unLinkPortActionInputMap
		inputPort = inputPortArrayPtr[ index ];
		outputPortArrayPtr = inputPort->refOutputPortVector.data( );
		for( refIndex = 0; refIndex < refCount; ++refIndex )
			if( appendRmoveOutputRefActionInfo( actionArchiveArrayPtr[ userCount ], outputPortArrayPtr[ refIndex ], inputPort ) )
				userCount += 1;

	}

	count = node->outputPortVector.size( );
	outputPortArrayPtr = node->outputPortVector.data( );
	for( index = 0; index < count; ++index ) {
		refCount = outputPortArrayPtr[ index ]->refInputPortVector.size( );
		if( refCount == 0 )
			continue;
		refOutputCount += refCount;
		modCount = qactionArchiveCount - userCount; // 剩余数量
		// 当前数量无法满足需求
		if( modCount < refOutputCount )
			// 扩展一次，失败
			if( extendQActionArchiveVectorCount( 1024 + refOutputCount + qactionArchiveCount ) == false )
				// 使用更加小的扩展量
				if( extendQActionArchiveVectorCount( refOutputCount + qactionArchiveCount ) == false )
					return false; // 无法满足扩展需求
		// 添加到 unLinkPortActionInputMap
		outputPort = outputPortArrayPtr[ index ];
		inputPortArrayPtr = outputPort->refInputPortVector.data( );
		for( refIndex = 0; refIndex < refCount; ++refIndex )
			if( appendRmoveInputRefActionInfo( actionArchiveArrayPtr[ userCount ], outputPort, inputPortArrayPtr[ refIndex ] ) )
				userCount += 1;
	}

	unLinkPortActionInputMapCount = unLinkPortActionInputMap.size( );
	unLinkPortActionInputMapArrayPtr = unLinkPortActionInputMap.data( );

	unLinkPortActionOutputMapCount = unLinkPortActionOutputMap.size( );
	unLinkPortActionOutputMapArrayPtr = unLinkPortActionOutputMap.data( );

	return qactionArchiveCount != 0;
}
