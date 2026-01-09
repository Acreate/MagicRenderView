#include "normalNodeEditorPropertyMenu.h"

#include "../../app/application.h"
#include "../../director/nodeDirector.h"
#include "../../director/nodeInfoEditorDirector.h"
#include "../../node/node/node.h"
#include "../../node/nodeInfoWidget/mainInfoWidget/nodeInfoWidget.h"
#include "../../node/port/inputPort/inputPort.h"
#include "../../node/port/outputPort/outputPort.h"
#include "action/autoAction.h"
NormalNodeEditorPropertyMenu::ActionLinkInfoPair::ActionLinkInfoPair( AutoAction *trig_action, OutputPort *output_port, InputPort *input_port ) : trigAction( trig_action ), outputPort( output_port ), inputPort( input_port ) {
	QString titleArgString( tr( "断开 (%1[%2])->(%3[%4]) 链接" ) );
	titleArgString = titleArgString.arg( output_port->parentNode->getNodeTitleName( ) ).arg( output_port->getPortName( ) ).arg( input_port->parentNode->getNodeTitleName( ) ).arg( input_port->getPortName( ) );
	trigAction->setText( titleArgString );
}
NormalNodeEditorPropertyMenu::ActionNodeInfoPair::ActionNodeInfoPair( AutoAction *trig_action, Node *node, OutputPort *output_port, InputPort *input_port ) : trigAction( trig_action ),
	node( node ),
	outputPort( output_port ),
	inputPort( input_port ) { }
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
	unLinkPortActionInputMap.emplace_back( ActionLinkInfoPair( auto_action, output_port, input_port ) );
	deleteInputAtOutputRef->addAction( auto_action );
	return true;
}
bool NormalNodeEditorPropertyMenu::appendRmoveInputRefActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port ) {
	unLinkPortActionOutputMap.emplace_back( ActionLinkInfoPair( auto_action, output_port, input_port ) );
	deleteOutputAtInputRef->addAction( auto_action );
	return true;
}
bool NormalNodeEditorPropertyMenu::appendRefOutputNodeActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port ) {
	auto parentNode = output_port->parentNode;
	size_t index = 0;
	for( ; index < refOutputPortActionMapCount; ++index )
		if( refOutputPortActionMapArrayPtr[ index ].getNode( ) == parentNode )
			return false;
	refOutputPortActionMap.emplace_back( ActionNodeInfoPair( auto_action, parentNode, output_port, input_port ) );
	refOutputPortActionMapCount = refOutputPortActionMap.size( );
	refOutputPortActionMapArrayPtr = refOutputPortActionMap.data( );
	auto_action->setText( tr( "(%1[%2]) 跳到输入引用节点 (%3[%4])" ).arg( input_port->parentNode->getNodeTitleName( ) ).arg( input_port->getPortName( ) ).arg( parentNode->getNodeTitleName( ) ).arg( output_port->getPortName( ) ) );
	return true;
}
bool NormalNodeEditorPropertyMenu::appendRefInputNodeActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port ) {
	auto parentNode = input_port->parentNode;
	size_t index = 0;
	for( ; index < refInputPortActionMapCount; ++index )
		if( refInputPortActionMapArrayPtr[ index ].getNode( ) == parentNode )
			return false;
	refInputPortActionMap.emplace_back( ActionNodeInfoPair( auto_action, parentNode, output_port, input_port ) );
	refInputPortActionMapCount = refInputPortActionMap.size( );
	refInputPortActionMapArrayPtr = refInputPortActionMap.data( );
	auto_action->setText( tr( "(%1[%2]) 跳到输出引用节点 (%3[%4])" ).arg( output_port->parentNode->getNodeTitleName( ) ).arg( output_port->getPortName( ) ).arg( parentNode->getNodeTitleName( ) ).arg( input_port->getPortName( ) ) );
	return true;
}
void NormalNodeEditorPropertyMenu::clearResources( ) {
	currentNode = nullptr;
	unLinkPortActionInputMap.clear( );
	unLinkPortActionOutputMap.clear( );
	refOutputPortActionMap.clear( );
	refInputPortActionMap.clear( );
	refOutputPortActionMapCount = 0;
	refOutputPortActionMapArrayPtr = nullptr;
	refInputPortActionMapCount = 0;
	refInputPortActionMapArrayPtr = nullptr;

	dislayMenu->clear( );
	displayInputRef->clear( );
	deleteInputAtOutputRef->clear( );
	displayOutputRef->clear( );
	deleteOutputAtInputRef->clear( );
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
void NormalNodeEditorPropertyMenu::removeNodeAction( ) {
	emit remove_node_action_signal( this, currentNode );
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
void NormalNodeEditorPropertyMenu::displayInfoWidget( ) {
	if( nodeInfoWidget == nullptr )
		return;
	nodeInfoWidget->show( );
	nodeInfoWidget->raise( );
	emit show_node_edit_info_widget_signal( this, currentNode, nodeInfoWidget );
}
void NormalNodeEditorPropertyMenu::displayAtRefOutputNodeEnsureToWidget( QAction *tr_obj_ptr ) {
	size_t index = 0;
	for( ; index < refOutputPortActionMapCount; ++index )
		if( refOutputPortActionMapArrayPtr[ index ].getTrigAction( ) == tr_obj_ptr ) {
			emit show_node_at_widget_signal( this, refOutputPortActionMapArrayPtr[ index ].getNode( ) );
			return;
		}
}
void NormalNodeEditorPropertyMenu::displayAtRefInputNodeEnsureToWidget( QAction *tr_obj_ptr ) {
	size_t index = 0;
	for( ; index < refInputPortActionMapCount; ++index )
		if( refInputPortActionMapArrayPtr[ index ].getTrigAction( ) == tr_obj_ptr ) {
			emit show_node_at_widget_signal( this, refInputPortActionMapArrayPtr[ index ].getNode( ) );
			return;
		}

}
NormalNodeEditorPropertyMenu::NormalNodeEditorPropertyMenu( ) : QMenu( ) {
	currentNode = nullptr;
	qactionArchiveCount = 0;
	actionArchiveArrayPtr = nullptr;
	unLinkPortActionInputMapCount = 0;
	unLinkPortActionInputMapArrayPtr = nullptr;
	unLinkPortActionOutputMapCount = 0;
	unLinkPortActionOutputMapArrayPtr = nullptr;
	refInputPortActionMapArrayPtr = nullptr;
	refInputPortActionMapCount = 0;
	refOutputPortActionMapArrayPtr = nullptr;
	refOutputPortActionMapCount = 0;
	deleteNodeAction = new AutoAction( tr( "删除该节点" ) );
	displayInfoWidgetAction = new AutoAction( tr( "显示编辑菜单" ) );
	noteInfoWidgetAction = new AutoAction( tr( "不存在匹配窗口" ) );
	noteInfoWidgetAction->setEnabled( false );
	noteRemoveOutputLinkAction = new AutoAction( tr( "不存在匹配输出引用" ) );
	noteRemoveOutputLinkAction->setEnabled( false );
	noteRemoveInputputLinkAction = new AutoAction( tr( "不存在匹配输入引用" ) );
	noteRemoveInputputLinkAction->setEnabled( false );

	connect( deleteNodeAction, &QAction::triggered, this, &NormalNodeEditorPropertyMenu::removeNodeAction );

	connect( displayInfoWidgetAction, &QAction::triggered, this, &NormalNodeEditorPropertyMenu::displayInfoWidget );
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
	size_t index;
	if( qactionArchiveCount )
		for( index = 0; index < qactionArchiveCount; ++index )
			delete actionArchiveArrayPtr[ index ];
	qactionArchiveVector.clear( );

	unLinkPortActionOutputMap.clear( );
	unLinkPortActionInputMap.clear( );

	refInputPortActionMap.clear( );
	refOutputPortActionMap.clear( );

	actionArchiveArrayPtr = nullptr;
	qactionArchiveCount = 0;

	unLinkPortActionInputMapCount = 0;
	unLinkPortActionInputMapArrayPtr = nullptr;

	unLinkPortActionOutputMapCount = 0;
	unLinkPortActionOutputMapArrayPtr = nullptr;

	refInputPortActionMapArrayPtr = nullptr;
	refInputPortActionMapCount = 0;

	refOutputPortActionMapArrayPtr = nullptr;
	refOutputPortActionMapCount = 0;

	clear( );
	deleteMenu = addMenu( tr( "删除" ) );
	dislayMenu = addMenu( tr( "显示" ) );
	inputMneu = addMenu( tr( "输入" ) );
	displayOutputRef = inputMneu->addMenu( tr( "显示引用" ) );
	deleteInputAtOutputRef = inputMneu->addMenu( tr( "删除输出端口引用" ) );
	outputMenu = addMenu( tr( "输出" ) );
	displayInputRef = outputMenu->addMenu( tr( "显示引用" ) );
	deleteOutputAtInputRef = outputMenu->addMenu( tr( "删除输入端口引用" ) );
	deleteMenu->addAction( deleteNodeAction );
	connect( deleteOutputAtInputRef, &QMenu::triggered, this, &NormalNodeEditorPropertyMenu::removeOutoutPortRefLinkAction );
	connect( deleteInputAtOutputRef, &QMenu::triggered, this, &NormalNodeEditorPropertyMenu::removeInoutPortRefLinkAction );
	connect( displayInputRef, &QMenu::triggered, this, &NormalNodeEditorPropertyMenu::displayAtRefInputNodeEnsureToWidget );
	connect( displayOutputRef, &QMenu::triggered, this, &NormalNodeEditorPropertyMenu::displayAtRefOutputNodeEnsureToWidget );
	return true;
}
bool NormalNodeEditorPropertyMenu::setNode( Node *node ) {
	if( node == nullptr )
		return false;
	clearResources( );
	currentNode = node;
	if( qactionArchiveCount == 0 )
		extendQActionArchiveVectorCount( 1024 );
	// 添加显示菜单
	if( Application::getInstancePtr( )->getNodeInfoEditorDirector( )->getNodeInfoEditorWidget( node, nodeInfoWidget ) ) {
		displayInfoWidgetAction->setText( tr( "显示[ %1 ]( %2 )编辑窗口" ).arg( node->toQString( ) ).arg( nodeInfoWidget->metaObject( )->className( ) ) );
		dislayMenu->addAction( displayInfoWidgetAction );
	} else
		dislayMenu->addAction( noteInfoWidgetAction );
	deleteNodeAction->setText( tr( "删除[ %1 ]节点" ).arg( currentNode->toQString( ) ) );
	size_t userCount = 0;
	size_t modCount;
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
			if( appendRmoveOutputRefActionInfo( actionArchiveArrayPtr[ userCount ], outputPortArrayPtr[ refIndex ], inputPort ) ) {
				userCount += 1;
				if( appendRefOutputNodeActionInfo( actionArchiveArrayPtr[ userCount ], outputPortArrayPtr[ refIndex ], inputPort ) ) {
					displayOutputRef->addAction( actionArchiveArrayPtr[ userCount ] );
					userCount += 1;
				}
			}

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
			if( appendRmoveInputRefActionInfo( actionArchiveArrayPtr[ userCount ], outputPort, inputPortArrayPtr[ refIndex ] ) ) {
				userCount += 1;
				if( appendRefInputNodeActionInfo( actionArchiveArrayPtr[ userCount ], outputPort, inputPortArrayPtr[ refIndex ] ) ) {
					displayInputRef->addAction( actionArchiveArrayPtr[ userCount ] );
					userCount += 1;
				}
			}
	}

	unLinkPortActionInputMapCount = unLinkPortActionInputMap.size( );
	unLinkPortActionInputMapArrayPtr = unLinkPortActionInputMap.data( );

	unLinkPortActionOutputMapCount = unLinkPortActionOutputMap.size( );
	unLinkPortActionOutputMapArrayPtr = unLinkPortActionOutputMap.data( );

	return qactionArchiveCount != 0;
}
void NormalNodeEditorPropertyMenu::hideEvent( QHideEvent *hide_event ) {
	QMenu::hideEvent( hide_event );

}
