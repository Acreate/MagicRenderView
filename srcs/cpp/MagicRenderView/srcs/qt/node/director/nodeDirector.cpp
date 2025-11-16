#include "nodeDirector.h"

#include <QPainter>
#include <qmenu.h>

#include <qt/application/application.h>
#include <qt/generate/varGenerate.h>
#include <qt/node/item/nodeItem.h>
#include <qt/node/nodeItemMenu/nodeItemMenu.h>
#include <qt/node/prot/inputProt/nodeInputPort.h>
#include <qt/node/prot/outputProt/nodeOutputPort.h>
#include <qt/tools/tools.h>
#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>
#include <qt/widgets/mainWidget/mainWidget.h>

#include "nodeItemBuilderObj.h"
#include "nodeItemGenerateInfo.h"
#include "nodeItemInfo.h"
#include "nodePortLinkInfo.h"

NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ) {

}

bool NodeDirector::linkInstallPort( NodePort *first_port, NodePort *scond_port ) {
	if( first_port == nullptr || scond_port == nullptr || scond_port == first_port )
		return false; // 同一个节点或者为 nullptr
	bool firstIsOutputPort = first_port->isOutputPort( );
	bool scondIsOutputPort = scond_port->isOutputPort( );
	if( firstIsOutputPort == scondIsOutputPort )
		return false; // 同是同一类型，则返回
	if( firstIsOutputPort )
		return linkInstallPort( ( NodeInputPort * ) scond_port, ( NodeOutputPort * ) first_port );
	else
		return linkInstallPort( ( NodeInputPort * ) first_port, ( NodeOutputPort * ) scond_port );

}
bool NodeDirector::linkUnInstallPort( NodePort *first_port, NodePort *scond_port ) {
	if( first_port == nullptr || scond_port == nullptr || scond_port == first_port )
		return false; // 同一个节点或者为 nullptr
	bool firstIsOutputPort = first_port->isOutputPort( );
	bool scondIsOutputPort = scond_port->isOutputPort( );
	if( firstIsOutputPort == scondIsOutputPort )
		return false; // 同是同一类型，则返回
	if( firstIsOutputPort )
		return linkUnInstallPort( ( NodeInputPort * ) scond_port, ( NodeOutputPort * ) first_port );
	else
		return linkUnInstallPort( ( NodeInputPort * ) first_port, ( NodeOutputPort * ) scond_port );
}
bool NodeDirector::linkInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	if( input_port == nullptr || output_port == nullptr )
		return false; // 同一个节点或者为 nullptr
	NodeItem *inputNodeItem = input_port->parentItem;
	if( inputNodeItem == nullptr ) {
		tools::debug::printError( QString( QObject::tr( "%1 非法端口引用 0x%2 异常->未知错误" ) ).arg( input_port->getMetaObjectPathName( ) ).arg( QString::number( ( size_t ) input_port, 16 ).toUpper( ) ) );
		return false;
	}
	NodeItem *outputNodeItem = output_port->parentItem;
	if( outputNodeItem == nullptr ) {
		tools::debug::printError( QString( QObject::tr( "%1 非法端口引用 0x%2 异常->未知错误" ) ).arg( output_port->getMetaObjectPathName( ) ).arg( QString::number( ( size_t ) output_port, 16 ).toUpper( ) ) );
		return false;
	}
	if( inputNodeItem == outputNodeItem )
		return false; // 同一个节点或者为 nullptr

	const I_Type *inputPorVarType = input_port->getVarType( );
	if( inputPorVarType == nullptr ) {
		tools::debug::printError( QString( QObject::tr( "%1 输入端口不存在变量指向" ) ).arg( input_port->getMetaObjectPathName( ) ) );
		return false;
	}

	const I_Type *outputPorVarType = output_port->getVarType( );
	if( outputPorVarType == nullptr ) {
		tools::debug::printError( QString( QObject::tr( "%1 输出端口不存在变量指向" ) ).arg( output_port->getMetaObjectPathName( ) ) );
		return false;
	}

	if( varGenerate->supportType( inputPorVarType->getTypeInfo( ), outputPorVarType->getTypeInfo( ) ) == false )
		return false;
	NodeItemInfo *outputNodeItemInfo;
	if( getNodeItemInfo( outputNodeItem, outputNodeItemInfo ) == false ) {
		tools::debug::printError( QString( QObject::tr( "输出端 %1 不存在节点具象化信息" ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	if( outputNodeItemInfo->inInputNodeItemInfo( inputNodeItem ) ) {
		tools::debug::printError( QString( QObject::tr( "%1 引用 %2 异常->引用循环" ) ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	NodeItemInfo *inputNodeItemInfo;
	if( getNodeItemInfo( inputNodeItem, inputNodeItemInfo ) == false ) {
		tools::debug::printError( QString( QObject::tr( "输入端 %1 不存在节点具象化信息" ) ).arg( inputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	if( outputNodeItemInfo->appendOutputNodeItemInfo( inputNodeItemInfo ) == false ) {
		tools::debug::printError( QString( "%1 引用 %2 异常->未知错误" ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	if( inputNodeItemInfo->appendInputNodeItemInfo( outputNodeItemInfo ) == false ) {
		outputNodeItemInfo->removeInputNodeItemInfo( inputNodeItemInfo );
		tools::debug::printError( QString( QObject::tr( "%1 引用 %2 异常->未知错误" ) ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	size_t count = linkVectorPairt.size( );
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->inputPort == input_port ) {
			bool multiStatus = false;
			bool callResultBool = inputNodeItem->getMultiLinkPortStatus( input_port, multiStatus );
			if( callResultBool == false ) {
				tools::debug::printError( QString( QObject::tr( "%1 非法端口引用 %2 异常->未知错误" ) ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( inputNodeItem->getMetaObjectPathName( ) ) );
				return false;
			}
			if( multiStatus == true )
				return data[ index ]->link( output_port );
			auto outputPorts = data[ index ]->outputPorts;

			std::pair< NodeItem *, std::vector< std::pair< NodeOutputPort *, QAction * > > > *outputNodeItemArrayPtr;
			size_t outputArrayCount;
			std::pair< NodeOutputPort *, QAction * > *outputArrayPtr;
			size_t outputArrayIndex;

			count = outputPorts.size( );
			outputNodeItemArrayPtr = outputPorts.data( );

			for( index = 0; index < count; ++index ) {
				outputArrayCount = outputNodeItemArrayPtr[ index ].second.size( );
				if( outputArrayCount == 0 )
					continue;
				outputArrayPtr = outputNodeItemArrayPtr[ index ].second.data( );
				outputArrayIndex = 0;
				for( index = 0; index < count; ++index )
					if( outputArrayPtr[ outputArrayIndex ].first == output_port )
						return true;
			}

			callResultBool = data[ index ]->link( output_port );
			if( callResultBool == false )
				return false;

			for( index = 0; index < count; ++index ) {
				outputArrayCount = outputNodeItemArrayPtr[ index ].second.size( );
				if( outputArrayCount == 0 )
					continue;
				outputArrayPtr = outputNodeItemArrayPtr[ index ].second.data( );
				outputArrayIndex = 0;
				for( index = 0; index < count; ++index )
					if( outputArrayPtr[ outputArrayIndex ].first )
						linkUnInstallPort( input_port, outputArrayPtr[ outputArrayIndex ].first );
			}
			return true;
		}
	// 没有链接对象就创建
	auto newLinkObjPtr = new NodePortLinkInfo( input_port );

	data = linkVectorPairt.data( );
	index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = newLinkObjPtr;
			break;
		}
	if( index == count )
		linkVectorPairt.emplace_back( newLinkObjPtr );

	newLinkObjPtr->link( output_port );
	connect( newLinkObjPtr, &NodePortLinkInfo::linkNodePort, [this] ( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *output_port ) {
		emit linkNodePortSignal( this, sender_obj_ptr, input_port, output_port );
	} );
	connect( newLinkObjPtr, &NodePortLinkInfo::unlinkNodePort, [this, newLinkObjPtr] ( NodePortLinkInfo *sender_obj_ptr, NodeInputPort *input_port, NodeOutputPort *output_port ) {
		auto outputParentNodeItem = output_port->parentItem;
		if( newLinkObjPtr->hasNodeItem( outputParentNodeItem ) == true )
			return;

		NodeItemInfo *outputInfo;
		if( getNodeItemInfo( outputParentNodeItem, outputInfo ) == false ) {
			QString msg( QObject::tr( "%1 找不到匹配的具体输出" ) );
			tools::debug::printError( msg.arg( outputParentNodeItem->getMetaObjectPathName( ) ) );
			return;
		}

		auto inputParentNodeItem = input_port->parentItem;
		NodeItemInfo *inputInfo;
		if( getNodeItemInfo( inputParentNodeItem, inputInfo ) == false ) {
			QString msg( QObject::tr( "%1 找不到匹配的具体输入" ) );
			tools::debug::printError( msg.arg( inputParentNodeItem->getMetaObjectPathName( ) ) );
			return;
		}
		if( outputInfo->removeOutputNodeItemInfo( inputInfo ) == false )tools::debug::printError( QString( "异常的输出节点删除操作 %1 -> %2" ).arg( outputInfo->nodeItem->getMetaObjectPathName( ) ).arg( inputInfo->nodeItem->getMetaObjectPathName( ) ) );
		if( inputInfo->removeInputNodeItemInfo( outputInfo ) == false )tools::debug::printError( QString( "异常的输入节点删除操作 %2 <- %1" ).arg( outputInfo->nodeItem->getMetaObjectPathName( ) ).arg( inputInfo->nodeItem->getMetaObjectPathName( ) ) );
		emit unlinkNodePortSignal( this, sender_obj_ptr, input_port, output_port );
	} );
	return true;
}
bool NodeDirector::linkUnInstallPort( NodeInputPort *input_port, NodeOutputPort *output_port ) {
	if( input_port == nullptr || output_port == nullptr )
		return false; // 一个节点为 nullptr

	NodeItem *outputNodeItem = output_port->parentItem;
	NodeItem *inputNodeItem = input_port->parentItem;
	if( outputNodeItem == inputNodeItem )
		return false; // 同一个节点

	size_t count = linkVectorPairt.size( );
	if( count == 0 )
		return false;// 不存在匹配的链接端
	auto pair = linkVectorPairt.data( );
	for( size_t index = 0; index < count; ++index )
		if( pair[ index ]->inputPort == input_port )
			return pair[ index ]->unLink( output_port );
	return false; // 不存在
}
bool NodeDirector::setRaise( const NodeItem *raise_node_item ) {

	// 节点个数
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return false;

	// 节点数组指针
	auto data = nodeItemInfoVector.data( );
	// 下标
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->nodeItem == raise_node_item ) {
			count -= 1;
			if( index == count )
				return true;
			auto *makeItem = data[ index ];
			for( ; index < count; index++ )
				data[ index ] = data[ index + 1 ];
			data[ index ] = makeItem;
			return true; // 检测到了
		}
	return false;
}
bool NodeDirector::setRaise( const NodePort *raise_node_port ) {
	return setRaise( raise_node_port->parentItem );
}
NodeItem * NodeDirector::getLastNodeItem( ) {
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return nullptr;
	return nodeItemInfoVector.data( )[ count - 1 ]->nodeItem;
}
void NodeDirector::drawNodeItemLine( QPainter &painter_target ) const {

	size_t count = linkVectorPairt.size( );
	if( count > 0 ) {
		QPoint inport;
		QPoint outport;
		size_t outIndex;

		auto nodePortLinkInfo = linkVectorPairt.data( );
		size_t index = 0;
		size_t outPortCount;
		std::pair< NodeItem *, std::vector< std::pair< NodeOutputPort *, QAction * > > > *outPortData;
		for( ; index < count; ++index )
			if( nodePortLinkInfo[ index ] != nullptr )
				if( outPortCount = nodePortLinkInfo[ index ]->outputPorts.size( ), nodePortLinkInfo[ index ]
					!= nullptr && outPortCount != 0 ) {
					nodePortLinkInfo[ index ]->inputPort->getPos( outport );
					outPortData = nodePortLinkInfo[ index ]->outputPorts.data( );
					for( outIndex = 0; outIndex < outPortCount; ++outIndex ) {
						size_t oupPairtCount = outPortData[ outIndex ].second.size( );
						if( oupPairtCount == 0 )
							continue;
						auto pair = outPortData[ outIndex ].second.data( );
						for( size_t pariIndex = 0; pariIndex < oupPairtCount; ++pariIndex ) {
							pair[ pariIndex ].first->getPos( inport );
							painter_target.drawLine( outport, inport );
						}
					}
				}
	}
}
void NodeDirector::drawNodeItemError( QPainter &painter_target ) const {
	size_t count;
	size_t index;

	count = nodeItemInfoVector.size( );
	index = 0;
	if( count > 0 ) {
		count -= 1;
		auto data = nodeItemInfoVector.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				if( nodeItem == nullptr )
					continue;
				painter_target.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
			}
		painter_target.drawImage( data[ index ]->nodeItem->getPos( ), *data[ index ]->nodeItem->getNodeItemRender( ) );
	}
}
void NodeDirector::drawNodeItemFinish( QPainter &painter_target ) const {
}
void NodeDirector::drawNodeItemSelectorAndFinish( QPainter &painter_target ) const {
}
void NodeDirector::drawNodeItemSelector( QPainter &painter_target ) const {

	size_t count;
	size_t index;

	count = nodeItemInfoVector.size( );
	index = 0;
	if( count > 0 ) {
		auto data = nodeItemInfoVector.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				if( nodeItem == nullptr )
					continue;
				painter_target.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
			}
	}
}
void NodeDirector::drawNodeItemSelectorAndError( QPainter &painter_target ) const {

	size_t count;
	size_t index;

	count = nodeItemInfoVector.size( );
	index = 0;
	if( count > 0 ) {
		auto data = nodeItemInfoVector.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				if( nodeItem == nullptr )
					continue;
				painter_target.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
			}
	}
}
void NodeDirector::drawNodeItemNormal( QPainter &painter_target ) const {

	size_t count;
	size_t index;

	count = nodeItemInfoVector.size( );
	index = 0;
	if( count > 0 ) {
		auto data = nodeItemInfoVector.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				if( nodeItem == nullptr )
					continue;
				painter_target.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
			}
	}
}
void NodeDirector::draw( QPainter &painter_target ) const {

	if( selectNodeItemVector.size( ) != 0 ) {
		if( errorNodeItemInfo.errorNodeItemPtr != nullptr )
			drawNodeItemSelectorAndError( painter_target );
		else
			drawNodeItemSelector( painter_target );
		return;
	}
	if( errorNodeItemInfo.errorNodeItemPtr != nullptr )
		drawNodeItemError( painter_target );
	else
		drawNodeItemNormal( painter_target );

	drawNodeItemLine( painter_target );
}
std_vector< NodeItem * > NodeDirector::getNodeItems( ) const {
	std_vector< NodeItem * > result;
	size_t count = nodeItemInfoVector.size( );
	auto data = nodeItemInfoVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr )
			result.emplace_back( data[ index ]->nodeItem );
	return result;
}

std_vector< QImage * > NodeDirector::getNodeItemRenders( ) const {
	std_vector< QImage * > result;
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return result;
	auto data = nodeItemInfoVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr )
			result.emplace_back( data[ index ]->nodeItem->getNodeItemRender( ) );
	return result;
}

bool NodeDirector::createMenu( ) {

	auto infos = varGenerate->getNodeItemSortMap( );
	if( infos.size( ) == 0 )
		return false;
	QString enumString;
	for( auto &[ enumType,dirNamMap ] : infos ) {
		if( nodeItemEnum::getEnumName( enumType, enumString ) == false )
			continue;
		QMenu *nodeTypeMenu = nodeItemCreateMenu->addMenu( enumString );
		for( auto &[ dir,nameMap ] : dirNamMap ) {
			QMenu *dirMenu = nodeTypeMenu->addMenu( dir );
			for( auto &[ className, typePtr ] : nameMap ) {
				if( className.isEmpty( ) )
					continue;
				auto addAction = dirMenu->addAction( className );
				auto nodeItemGenerateInfo = std_shared_ptr< NodeItemGenerateInfo >( new NodeItemGenerateInfo( dir, className, typePtr ) );
				generateNodeItemInfos.emplace_back( nodeItemGenerateInfo );
				connect( addAction, &QAction::triggered, [this, dir, className, typePtr]( ) {
					if( createNodeItem( dir, className, typePtr ) == nullptr || mainWidget == nullptr )
						return;
				} );
			}
		}
	}
	return true;
}
bool NodeDirector::resetMenu( QObject *del_ptr ) {
	nodeItemCreateMenu = new NodeItemMenu( );
	connect( nodeItemCreateMenu, &QMenu::destroyed, this, &NodeDirector::resetMenu );
	return this->createMenu( );
}

bool NodeDirector::rleaseNodeItem( NodeItem *release ) {
	// 删除 linkVectorPairt

	size_t count = linkVectorPairt.size( );
	size_t index;
	if( count != 0 ) {
		index = 0;
		NodePortLinkInfo *nodePortLinkInfo = nullptr;
		auto nodePortLinkInfoData = linkVectorPairt.data( );
		for( ; index < count; ++index ) {
			if( nodePortLinkInfoData[ index ] != nullptr )
				if( nodePortLinkInfoData[ index ]->inputPort->parentItem == release ) {
					nodePortLinkInfo = linkVectorPairt[ index ];
					linkVectorPairt[ index ] = nullptr;
				} else
					nodePortLinkInfoData[ index ]->releaseNodeItemPtr( release );
		}
		if( nodePortLinkInfo )
			delete nodePortLinkInfo;
	}

	// 删除 generateNodeItems
	count = nodeItemInfoVector.size( );
	NodeItemInfo *itemInfo = nullptr;
	if( count != 0 ) {
		auto nodeitemPtrData = nodeItemInfoVector.data( );
		index = 0;
		for( ; index < count; ++index )
			if( nodeitemPtrData[ index ] != nullptr )
				if( nodeitemPtrData[ index ]->nodeItem == release ) {
					itemInfo = nodeitemPtrData[ index ];
					nodeitemPtrData[ index ] = nullptr;
					break;
				}
		if( itemInfo ) {
			index = 0;
			for( ; index < count; ++index )
				if( nodeitemPtrData[ index ] != nullptr ) {
					nodeitemPtrData[ index ]->removeOutputNodeItemInfo( itemInfo );
					nodeitemPtrData[ index ]->removeInputNodeItemInfo( itemInfo );
				}
			delete itemInfo;
			sortNodeItemInfo( );
			updateNodeItemInfo( );
		}
	}
	return true;
}
bool NodeDirector::sortNodeItemInfo( ) {
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return true;
	auto nodeItemArrayPtr = nodeItemInfoVector.data( );
	size_t index = 0;
	size_t maxCount = 0;
	for( ; index < count; ++index )
		if( nodeItemArrayPtr[ index ] != nullptr && maxCount < nodeItemArrayPtr[ index ]->nodeItem->generateCode )
			maxCount = nodeItemArrayPtr[ index ]->nodeItem->generateCode;

	std_vector< NodeItemInfo * > buff( maxCount, nullptr );

	auto buffArrayPtr = buff.data( );
	index = 0;
	for( ; index < count; ++index )
		if( nodeItemArrayPtr[ index ] != nullptr )
			buffArrayPtr[ nodeItemArrayPtr[ index ]->nodeItem->generateCode - 1 ] = nodeItemArrayPtr[ index ];
	nodeItemInfoVector = buff;
	return true;
}
void NodeDirector::updateNodeItemInfo( ) {
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return;
	auto nodeItemArrayPtr = nodeItemInfoVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( nodeItemArrayPtr[ index ] )
			nodeItemArrayPtr[ index ]->nodeItem->updateLayout( );
}
bool NodeDirector::connectLink( const size_t &input_nodeitem_code, const size_t &input_prot_code, const size_t &output_nodeitem_code, const size_t &outut_prot_code ) {

	size_t count = nodeItemInfoVector.size( );
	if( count == 0 ) {
		QString msg( QObject::tr( "0x%1 不存在任何节点信息" ) );
		QString hex = QString::number( ( size_t ) this, 16 );
		tools::debug::printError( msg.arg( hex.toUpper( ), 8, '0' ) );
		return false;
	}
	NodeItem *inputItem = nullptr;
	NodeItem *outputItem = nullptr;
	auto itemGenerateInfo = nodeItemInfoVector.data( );

	size_t index = 0;
	for( ; ( inputItem == nullptr || outputItem == nullptr ) && index < count; ++index )
		if( itemGenerateInfo[ index ] )
			if( inputItem == nullptr && itemGenerateInfo[ index ]->nodeItem->generateCode == input_nodeitem_code )
				inputItem = itemGenerateInfo[ index ]->nodeItem;
			else if( outputItem == nullptr && itemGenerateInfo[ index ]->nodeItem->generateCode == output_nodeitem_code )
				outputItem = itemGenerateInfo[ index ]->nodeItem;
	if( inputItem == nullptr ) {
		QString msg( QObject::tr( "%1 不存在匹配的输入节点" ) );
		QString hex = QString::number( input_nodeitem_code );
		tools::debug::printError( msg.arg( hex.toUpper( ) ) );
		return false;
	}
	if( outputItem == nullptr ) {
		QString msg( QObject::tr( "%1 不存在匹配的输出节点" ) );
		QString hex = QString::number( output_nodeitem_code );
		tools::debug::printError( msg.arg( hex.toUpper( ) ) );
		return false;
	}

	auto &inputProtVector = inputItem->nodeInputProtVector;
	count = inputProtVector.size( );
	index = 0;
	NodeInputPort *input = nullptr;
	auto inputArrayPtr = inputProtVector.data( );
	for( ; input == nullptr && index < count; ++index )
		if( inputArrayPtr[ index ].first->generateCode == input_prot_code )
			input = inputArrayPtr[ index ].first;
	if( input == nullptr ) {
		QString msg( QObject::tr( "%1 不存在匹配的输入端口" ) );
		QString hex = QString::number( input_prot_code );
		tools::debug::printError( msg.arg( hex.toUpper( ) ) );
		return false;
	}
	NodeOutputPort *output = nullptr;
	auto &outputProtVector = outputItem->nodeOutputProtVector;
	count = outputProtVector.size( );
	index = 0;
	auto outputArrayPtr = outputProtVector.data( );
	for( ; output == nullptr && index < count; ++index )
		if( outputArrayPtr[ index ].first->generateCode == outut_prot_code )
			output = outputArrayPtr[ index ].first;
	if( output == nullptr ) {
		QString msg( QObject::tr( "%1 不存在匹配的输出端口" ) );
		QString hex = QString::number( outut_prot_code );
		tools::debug::printError( msg.arg( hex.toUpper( ) ) );
		return false;
	}
	bool resultOk = this->linkInstallPort( input, output );
	if( resultOk == false ) {
		QString msg( QObject::tr( "[%1.%2 -> %3.%4] 连接异常" ) );
		tools::debug::printError( msg.arg( inputItem->getMetaObjectPathName( ) ).arg( input->getMetaObjectPathName( ) ).arg( outputItem->getMetaObjectPathName( ) ).arg( output->getMetaObjectPathName( ) ) );
		return false;
	}
	return resultOk;
}

bool NodeDirector::getNodeItemInfo( const NodeItem *get_nodeitem_ptr, NodeItemInfo *&result_link ) {
	size_t linkCount = nodeItemInfoVector.size( );
	if( linkCount == 0 )
		return false;
	auto linkArrayDataPtr = nodeItemInfoVector.data( );
	for( size_t index = 0; index < linkCount; ++index )
		if( linkArrayDataPtr[ index ] != nullptr && linkArrayDataPtr[ index ]->nodeItem == get_nodeitem_ptr ) {
			result_link = linkArrayDataPtr[ index ];
			return true;
		}
	return false;
}
bool NodeDirector::setContentWidget( MainWidget *main_widget ) {
	if( main_widget == nullptr )
		return false;
	if( mainWidget == main_widget )
		return true;
	generateNodeItemInfos.clear( );
	auto clone = nodeItemInfoVector;
	nodeItemInfoVector.clear( );
	for( auto removeItem : clone )
		if( removeItem )
			delete removeItem->nodeItem;

	mainWidget = main_widget;
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	varGenerate = applicationInstancePtr->getVarGenerate( );
	if( nodeItemCreateMenu ) {
		nodeItemCreateMenu->disconnect( nodeItemCreateMenu, &QMenu::destroyed, this, &NodeDirector::resetMenu );
		delete nodeItemCreateMenu;
	}
	nodeItemCreateMenu = new NodeItemMenu( );
	connect( nodeItemCreateMenu, &QMenu::destroyed, this, &NodeDirector::resetMenu );

	return this->createMenu( );;
}

NodeItem * NodeDirector::createNodeItem( const QString &dir_name, const QString &node_name, const std_shared_ptr< I_Type > &itype_ptr ) {
	NodeItem *nodeItem = ( NodeItem * ) itype_ptr->getCreate( ).operator()( );
	if( nodeItem == nullptr )
		return nullptr;
	if( appendNodeItem( nodeItem ) )
		return nodeItem;
	delete nodeItem;
	return nullptr;
}
NodeItem * NodeDirector::createNodeItem( const QString &dir_name, const QString &node_name ) {
	size_t count = generateNodeItemInfos.size( );
	if( count == 0 )
		return nullptr;
	auto generateInfoArrayPtr = generateNodeItemInfos.data( );
	for( size_t index = 0; index < count; ++index )
		if( generateInfoArrayPtr[ index ]->isNodeType( dir_name, node_name ) )
			return createNodeItem( dir_name, node_name, generateInfoArrayPtr[ index ]->getCreateTypeInstancePtr( ) );
	return nullptr;

}

size_t NodeDirector::appendNodeItem( NodeItem *new_node_item ) {

	new_node_item->setMainWidget( mainWidget );

	if( new_node_item->intPortItems( mainWidget ) == false )
		return 0;
	size_t count = nodeItemInfoVector.size( );
	auto data = nodeItemInfoVector.data( );
	size_t index = 0;
	NodeItemInfo *nodeItemInfo = new NodeItemInfo( new_node_item );
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = nodeItemInfo;
			new_node_item->generateCode = index + 1;
			index = 0;
			break;
		}
	if( index == count ) {
		nodeItemInfoVector.emplace_back( nodeItemInfo );
		new_node_item->generateCode = count + 1;
	}

	QPoint mapFromGlobal = mainWidget->mapFromGlobal( nodeItemCreateMenu->pos( ) );
	auto size = mainWidget->contentsRect( ).size( );
	int targetHeight = size.height( );
	int targetWidth = size.width( );
	int targetY = mapFromGlobal.y( );
	int targetX = mapFromGlobal.x( );
	if( targetY < 0 )
		mapFromGlobal.setY( 0 );
	else if( targetY > targetHeight )
		mapFromGlobal.setY( targetHeight );
	if( targetX < 0 )
		mapFromGlobal.setX( 0 );
	else if( targetX > targetWidth )
		mapFromGlobal.setX( targetWidth );

	new_node_item->move( mapFromGlobal );
	connect( new_node_item, &NodeItem::releaseThisPtr, [this] ( NodeItem *release_node_item ) {
		rleaseNodeItem( release_node_item ); // 管理对象的所有信息
	} );
	connect( nodeItemInfo, &NodeItemInfo::releaseThisPtr, this, &NodeDirector::releaseNodeItemInfoSignal );
	connect( nodeItemInfo, &NodeItemInfo::nodeItemInfoRefChangeOutputNodeItem, this, &NodeDirector::nodeItemInfoRefChangeOutputNodeItem );
	connect( nodeItemInfo, &NodeItemInfo::nodeItemInfoRefChangeInputNodeItem, this, &NodeDirector::nodeItemInfoRefChangeInputNodeItem );
	new_node_item->updateLayout( );
	emit generateNodeItemSignal( new_node_item );
	emit nodeItemFocusSignal( new_node_item );
	return new_node_item->generateCode;
}
bool NodeDirector::getLinkOutPorts( const NodeInputPort *input_port, std_vector< NodeOutputPort * > &result_vector ) const {
	size_t count = linkVectorPairt.size( );
	if( count == 0 )
		return false;
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->inputPort == input_port )
			return data[ index ]->getLink( result_vector );
	return false;
}
bool NodeDirector::getLinkOutPorts( const NodePort *input_port, std_vector< NodeOutputPort * > &result_vector ) const {
	if( input_port->isOutputPort( ) == false )
		return getLinkOutPorts( ( NodeInputPort * ) input_port, result_vector );
	return false;
}
bool NodeDirector::getLinkInputPorts( const NodeOutputPort *output_port, std_vector< NodeInputPort * > &result_vector ) const {

	size_t count = linkVectorPairt.size( );
	if( count == 0 )
		return false;
	result_vector.clear( );
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		std_vector< NodeOutputPort * > resultInputLink;
		if( data[ index ]->getLink( resultInputLink ) == false )
			continue;
		for( auto &outputPort : resultInputLink )
			if( output_port == outputPort ) {
				result_vector.emplace_back( data[ index ]->inputPort );
				break;
			}
	}
	return false;
}
bool NodeDirector::getLinkInputPorts( const NodePort *output_port, std_vector< NodeInputPort * > &result_vector ) const {
	if( output_port->isOutputPort( ) )
		return getLinkInputPorts( ( NodeOutputPort * ) output_port, result_vector );
	return false;
}
bool NodeDirector::getLinkOutPorts( const NodeItem *input_port_node_item, std_vector_pairt< NodeInputPort *, std_vector< NodeOutputPort * > > &result_vector ) const {

	size_t linkArrayCount = linkVectorPairt.size( );
	if( linkArrayCount == 0 )
		return false;

	size_t findInputCount = input_port_node_item->nodeInputProtVector.size( );
	if( findInputCount == 0 )
		return true;

	result_vector.clear( );
	auto linkArrayPtr = linkVectorPairt.data( );
	auto inputPortArrayPtr = input_port_node_item->nodeInputProtVector.data( );
	size_t linkArrayIndex = 0;
	size_t inputPortArrayIndex;
	std_vector< NodeOutputPort * > resultLink;
	for( ; linkArrayIndex < linkArrayCount; ++linkArrayIndex )
		for( inputPortArrayIndex = 0; linkArrayIndex < linkArrayCount; ++linkArrayIndex )
			if( linkArrayPtr[ linkArrayIndex ]->inputPort == inputPortArrayPtr[ inputPortArrayIndex ].first ) {
				if( linkArrayPtr[ linkArrayIndex ]->getLink( resultLink ) )
					result_vector.emplace_back( inputPortArrayPtr[ inputPortArrayIndex ].first, resultLink );
				break;
			}
	return result_vector.size( ) != 0;

}
bool NodeDirector::getLinkInputPorts( const NodeItem *output_port_node_item, std_vector_pairt< NodeOutputPort *, std_vector< NodeInputPort * > > &result_vector ) const {

	size_t linkArrayCount = linkVectorPairt.size( );
	if( linkArrayCount == 0 )
		return false;

	size_t findInputCount = output_port_node_item->nodeOutputProtVector.size( );
	if( findInputCount == 0 )
		return true;
	result_vector.clear( );
	auto linkArrayPtr = linkVectorPairt.data( );
	auto inputPortArrayPtr = output_port_node_item->nodeOutputProtVector.data( );
	size_t linkArrayIndex = 0;
	size_t inputPortArrayIndex;
	std_vector< NodeOutputPort * > nodeOutputPorts;
	std_vector< NodeInputPort * > appendInputPortBuff;
	for( ; linkArrayIndex < linkArrayCount; ++linkArrayIndex )
		if( linkArrayPtr[ linkArrayIndex ]->getLink( nodeOutputPorts ) == false )
			continue;
		else
			for( inputPortArrayIndex = 0; linkArrayIndex < linkArrayCount; ++linkArrayIndex ) {
				for( auto outputPort : nodeOutputPorts )
					if( inputPortArrayPtr[ inputPortArrayIndex ].first == outputPort ) {
						bool isAppend = false;
						for( auto &[ resultOutputPort,resultInputPortVector ] : result_vector ) {
							if( resultOutputPort == outputPort ) {
								for( auto input : resultInputPortVector )
									if( input == linkArrayPtr[ linkArrayIndex ]->inputPort ) {
										isAppend = true;
										break;
									}
								if( isAppend == false ) {
									resultInputPortVector.emplace_back( linkArrayPtr[ linkArrayIndex ]->inputPort );
									isAppend = true;
								}
								break;
							}
						}
						if( isAppend == false )
							result_vector.emplace_back( outputPort, std_vector { linkArrayPtr[ linkArrayIndex ]->inputPort } );
						break;
					}
			}
	return result_vector.size( ) != 0;

}
bool NodeDirector::getLinkControlMenu( const NodePort *input_port, QMenu *&result_menu_ptr ) const {
	if( input_port->isOutputPort( ) == false )
		return getLinkControlMenu( ( NodeInputPort * ) input_port, result_menu_ptr );
	return false;
}
bool NodeDirector::getLinkControlMenu( const NodeInputPort *input_port, QMenu *&result_menu_ptr ) const {
	size_t count = linkVectorPairt.size( );
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->inputPort == input_port ) {
			result_menu_ptr = data[ index ]->removeLinkMenu;
			return true;
		}
	return false;
}
bool NodeDirector::getItemManageMenu( const NodeItem *node_item_ptr, QMenu *&result_menu_ptr ) {
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return false;
	auto data = nodeItemInfoVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->nodeItem == node_item_ptr ) {
			result_menu_ptr = data[ index ]->manageMenu;
			return true;
		}
	return false;
}
bool NodeDirector::renderLinkListHasNodeItem( const NodeInputPort *input_port, const NodeItem *node_item_ptr ) {
	size_t count = linkVectorPairt.size( );
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ]->inputPort == input_port ) {
			return data[ index ]->hasNodeItem( node_item_ptr );
		}
	return false;
}
size_t NodeDirector::toDataBin( std_vector< uint8_t > &result_data_vector ) {

	size_t resultCount = 0;
	if( applicationInstancePtr->getVarGenerate( )->toBinVector( typeid( NodeDirector ), this, result_data_vector, resultCount ) )
		return resultCount;
	return 0;

}
size_t NodeDirector::loadDataBin( const uint8_t *source_data_ptr, const size_t &source_data_count ) {
	size_t resultCount = 0;
	if( applicationInstancePtr->getVarGenerate( )->toOBjVector( typeid( NodeDirector ), this, resultCount, source_data_ptr, source_data_count ) )
		return resultCount;
	return 0;
}

void NodeDirector::errorNodeItem( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_index, const NodeItemInfo *error_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, nodeItemEnum::Node_Item_Builder_Type info_type ) {
	errorNodeItemInfo.senderSigObjPtr = sender_sig_obj_ptr;
	errorNodeItemInfo.beginIndex = begin_index;
	errorNodeItemInfo.errorNodeItemPtr = error_node_item_ptr;
	errorNodeItemInfo.nodeItemResult = node_item_result;
	errorNodeItemInfo.msg = msg;
	errorNodeItemInfo.infoType = info_type;
	if( error_node_item_ptr && error_node_item_ptr->nodeItem )
		setRaise( error_node_item_ptr->nodeItem );
}
void NodeDirector::finishNodeItem( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_index, const NodeItemInfo *finish_node_item_ptr ) {
	finishNodeItemInfo.senderSigObjPtr = sender_sig_obj_ptr;
	finishNodeItemInfo.beginIndex = begin_index;
	finishNodeItemInfo.finishNodeItemPtr = finish_node_item_ptr;
	if( finish_node_item_ptr && finish_node_item_ptr->nodeItem )
		setRaise( finish_node_item_ptr->nodeItem );
}

NodeDirector::~NodeDirector( ) {
	emit releaseThisSignal( this );
	size_t count;
	size_t index;

	count = nodeItemInfoVector.size( );
	if( count ) {
		index = 0;
		auto data = nodeItemInfoVector.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				NodeItemInfo *nodeItemInfo = data[ index ];
				data[ index ] = nullptr;
				delete nodeItemInfo;
				delete nodeItem;
			}
	}

	count = linkVectorPairt.size( );
	if( count ) {
		index = 0;
		auto data = linkVectorPairt.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				auto *removeItem = data[ index ];
				data[ index ] = nullptr;
				delete removeItem;
			}
	}
	if( nodeItemCreateMenu ) {
		nodeItemCreateMenu->disconnect( nodeItemCreateMenu, &QMenu::destroyed, this, &NodeDirector::resetMenu );
		delete nodeItemCreateMenu;
	}
}

void NodeDirector::setSelectNodeItemVector( const std_vector< NodeItem * > &select_node_item_vector ) {
	selectNodeItemVector = select_node_item_vector;
}
NodeItemBuilderObj * NodeDirector::builderNodeItem( ) {
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return nullptr;
	NodeItemBuilderObj *result = new NodeItemBuilderObj( this );
	auto nodeItemInfoArrayPtr = nodeItemInfoVector.data( );
	for( size_t index = 0; index < count; ++index )
		result->addBuilderNodeItem( nodeItemInfoArrayPtr[ index ] );
	if( result->builderNodeItemVector( ) == false ) {
		delete result;
		return nullptr;
	}
	connect( result, &NodeItemBuilderObj::finish_node_item_signal, [this] ( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_inde, const NodeItemInfo *finish_node_item_ptr ) {
		finishNodeItem( sender_sig_obj_ptr, begin_inde, finish_node_item_ptr );
		errorNodeItemInfo.clear( );
		emit finish_node_item_signal( sender_sig_obj_ptr, begin_inde, finish_node_item_ptr );
	} );
	connect( result, &NodeItemBuilderObj::error_node_item_signal, [this] ( NodeItemBuilderObj *sender_sig_obj_ptr, const size_t &begin_inde, const NodeItemInfo *error_node_item_ptr, nodeItemEnum::Node_Item_Result_Type node_item_result, const QString &msg, nodeItemEnum::Node_Item_Builder_Type info_type ) {
		errorNodeItem( sender_sig_obj_ptr, begin_inde, error_node_item_ptr, node_item_result, msg, info_type );
		finishNodeItemInfo.clear( );
		emit error_node_item_signal( sender_sig_obj_ptr, begin_inde, error_node_item_ptr, node_item_result, msg, info_type );
	} );
	connect( result, &NodeItemBuilderObj::reset_builder_node_item_signal, [this] ( NodeItemBuilderObj *sender_sig_obj_ptr ) {
		errorNodeItemInfo.clear( );
		finishNodeItemInfo.clear( );
		emit reset_builder_node_item_signal( sender_sig_obj_ptr );
	} );
	return result;
}

bool NodeDirector::nodeItemInfoLeftConverVar( NodeItemInfo *input_node_item_ptr ) {
	size_t count = input_node_item_ptr->nodeItem->nodeInputProtVector.size( );
	if( count == 0 )
		return true;
	auto inputArrayPtr = input_node_item_ptr->nodeItem->nodeInputProtVector.data( );

	size_t index = 0;
	for( ; index < count; ++index ) {
		auto inputPort = inputArrayPtr[ index ].first;
		std_vector< NodeOutputPort * > resultVector;
		if( getLinkOutPorts( inputPort, resultVector ) == false )
			return false;
		auto inputVar = inputPort->getVar( );
		auto inputVarPtr = inputVar->getVarPtr( );
		auto inputVarType = inputVar->getTypeInfo( );
		const auto &inputTypeInfo = inputVarType->getTypeInfo( );
		for( auto &outPort : resultVector ) {
			auto outputVar = outPort->getVar( );
			auto outputVarPtr = outputVar->getVarPtr( );
			auto outputVarType = outputVar->getTypeInfo( );
			const auto &outputTypeInfo = outputVarType->getTypeInfo( );
			if( varGenerate->conver( inputTypeInfo, inputVarPtr, outputTypeInfo, outputVarPtr ) == false )
				return false;
		}
	}
	return true;
}
bool NodeDirector::nodeItemInfRightConverVar( NodeItemInfo *output_node_item_ptr ) {
	size_t count = output_node_item_ptr->nodeItem->nodeOutputProtVector.size( );
	if( count == 0 )
		return true;
	auto outputArrayPtr = output_node_item_ptr->nodeItem->nodeOutputProtVector.data( );

	size_t index = 0;
	for( ; index < count; ++index ) {
		auto outputPort = outputArrayPtr[ index ].first;
		std_vector< NodeInputPort * > resultVector;
		if( getLinkInputPorts( outputPort, resultVector ) == false )
			return false;
		auto outputVar = outputPort->getVar( );
		auto outputVarPtr = outputVar->getVarPtr( );
		auto outputVarType = outputVar->getTypeInfo( );
		const auto &outputTypeInfo = outputVarType->getTypeInfo( );
		for( auto &inputPort : resultVector ) {
			auto inputVar = inputPort->getVar( );
			auto inputVarPtr = inputVar->getVarPtr( );
			auto inputVarType = inputVar->getTypeInfo( );
			const auto &inputTypeInfo = inputVarType->getTypeInfo( );
			if( varGenerate->conver( inputTypeInfo, inputVarPtr, outputTypeInfo, outputVarPtr ) == false )
				return false;
		}
	}
	return true;
}
nodeItemEnum::Click_Type NodeDirector::getClickNodeItem( NodeItem *&result_node_item, NodePort * &result_node_port ) {
	return getClickNodeItem( mainWidget->mapFromGlobal( QCursor::pos( ) ), result_node_item, result_node_port );
}
nodeItemEnum::Click_Type NodeDirector::getClickNodeItem( const QPoint &click_pos, NodeItem *&result_node_item, NodePort * &result_node_port ) {

	result_node_item = nullptr;
	result_node_port = nullptr;
	// 节点个数
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return nodeItemEnum::Click_Type::None;
	// 节点数组指针
	auto data = nodeItemInfoVector.data( );
	// 下标
	size_t index = 0;
	// 局部坐标
	QPoint localPoint;

	for( ; index < count; ++index )
		if( data[ index ] != nullptr ) {
			localPoint = click_pos - data[ index ]->nodeItem->getPos( );
			nodeItemEnum::Click_Type pointType = data[ index ]->nodeItem->relativePointType( localPoint );
			if( pointType == nodeItemEnum::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]->nodeItem; // 选中了非空白处
			switch( pointType ) {
				case nodeItemEnum::Click_Type::InputPort :
					result_node_port = data[ index ]->nodeItem->getNodeInputAtRelativePointType( localPoint );
					break;
				case nodeItemEnum::Click_Type::OutputPort :
					result_node_port = data[ index ]->nodeItem->getNodeOutputPortAtRelativePointType( localPoint );
					break;
				default :
					result_node_port = nullptr;
					break;
			}

			return pointType; // 检测到了
		}

	return nodeItemEnum::Click_Type::None;
}
nodeItemEnum::Click_Type NodeDirector::getClickNodeItemInputPort( NodeItem *&result_node_item, NodeInputPort *&result_node_port ) {
	return getClickNodeItemInputPort( mainWidget->mapFromGlobal( QCursor::pos( ) ), result_node_item, result_node_port );
}
nodeItemEnum::Click_Type NodeDirector::getClickNodeItemInputPort( const QPoint &click_pos, NodeItem *&result_node_item, NodeInputPort *&result_node_port ) {

	result_node_item = nullptr;
	result_node_port = nullptr;
	// 节点个数
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return nodeItemEnum::Click_Type::None;
	// 节点数组指针
	auto data = nodeItemInfoVector.data( );
	// 下标
	size_t index = 0;
	// 局部坐标
	QPoint localPoint;

	for( ; index < count; ++index )
		if( data[ index ] != nullptr ) {
			localPoint = click_pos - data[ index ]->nodeItem->getPos( );
			nodeItemEnum::Click_Type pointType = data[ index ]->nodeItem->relativePointType( localPoint );
			if( pointType == nodeItemEnum::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]->nodeItem; // 选中了非空白处
			switch( pointType ) {
				case nodeItemEnum::Click_Type::InputPort :
					result_node_port = data[ index ]->nodeItem->getNodeInputAtRelativePointType( localPoint );
					break;
				default :
					result_node_port = nullptr;
					break;
			}

			return pointType; // 检测到了
		}
	return nodeItemEnum::Click_Type::None;
}
nodeItemEnum::Click_Type NodeDirector::getClickNodeItemOutputPort( NodeItem *&result_node_item, NodeOutputPort *&result_node_port ) {
	return getClickNodeItemOutputPort( mainWidget->mapFromGlobal( QCursor::pos( ) ), result_node_item, result_node_port );
}
nodeItemEnum::Click_Type NodeDirector::getClickNodeItemOutputPort( const QPoint &click_pos, NodeItem *&result_node_item, NodeOutputPort *&result_node_port ) {
	result_node_item = nullptr;
	result_node_port = nullptr;
	// 节点个数
	size_t count = nodeItemInfoVector.size( );
	if( count == 0 )
		return nodeItemEnum::Click_Type::None;
	// 节点数组指针
	auto data = nodeItemInfoVector.data( );
	// 下标
	size_t index = 0;
	// 局部坐标
	QPoint localPoint;

	for( ; index < count; ++index )
		if( data[ index ] != nullptr ) {
			localPoint = click_pos - data[ index ]->nodeItem->getPos( );
			nodeItemEnum::Click_Type pointType = data[ index ]->nodeItem->relativePointType( localPoint );
			if( pointType == nodeItemEnum::Click_Type::None )
				continue; // 空白处，则跳过循环
			result_node_item = data[ index ]->nodeItem; // 选中了非空白处
			switch( pointType ) {
				case nodeItemEnum::Click_Type::OutputPort :
					result_node_port = data[ index ]->nodeItem->getNodeOutputPortAtRelativePointType( localPoint );
					break;
				default :
					result_node_port = nullptr;
					break;
			}

			return pointType; // 检测到了
		}
	return nodeItemEnum::Click_Type::None;
}
