#include "nodeDirector.h"

#include <QPainter>
#include <qmenu.h>

#include <qt/application/application.h>
#include <qt/generate/varGenerate.h>
#include <qt/node/nodeItemMenu/nodeItemMenu.h>
#include <qt/node/prot/inputProt/nodeInputPort.h>
#include <qt/widgets/mainWidget.h>

#include "nodeItemBuilderLink.h"
#include "nodeItemGenerateInfo.h"
#include "nodeItemInfo.h"
#include "nodePortLinkInfo.h"

#include "../../varType/I_Var.h"
NodeDirector::NodeDirector( QObject *parent ) : QObject( parent ) {
}
NodeItemInfoScrollAreaWidget * NodeDirector::requestGetNodeEditorWidget( const type_info &request_type, NodeItem *request_node_item_ptr ) {
	return nullptr;
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
	NodeItem *outputNodeItem = output_port->parentItem;
	if( inputNodeItem == outputNodeItem )
		return false; // 同一个节点或者为 nullptr
	const I_Type *inputPorVarType = input_port->getVarType( );
	if( inputPorVarType == nullptr ) {
		tools::debug::printError( QString( "%1 输入端口不存在变量指向" ).arg( input_port->getMetaObjectPathName( ) ) );
		return false;
	}

	const I_Type *outputPorVarType = output_port->getVarType( );
	if( outputPorVarType == nullptr ) {
		tools::debug::printError( QString( "%1 输出端口不存在变量指向" ).arg( output_port->getMetaObjectPathName( ) ) );
		return false;
	}

	if( varGenerate->supportType( inputPorVarType->getTypeInfo( ), outputPorVarType->getTypeInfo( ) ) == false )
		return false;
	NodeItemInfo *outputNodeItemInfo;
	if( getNodeItemInfo( outputNodeItem, outputNodeItemInfo ) == false ) {
		tools::debug::printError( QString( "输出端 %1 不存在节点具象化信息" ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	if( outputNodeItemInfo->inInputNodeItemInfo( inputNodeItem ) ) {
		tools::debug::printError( QString( "%1 引用 %2 异常->引用循环" ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	NodeItemInfo *inputNodeItemInfo;
	if( getNodeItemInfo( inputNodeItem, inputNodeItemInfo ) == false ) {
		tools::debug::printError( QString( "输入端 %1 不存在节点具象化信息" ).arg( inputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}
	//if( inputNodeItemInfo->inOutputNodeItemInfo( outputNodeItem ) ) {
	//	tools::debug::printError( QString( "%1 引用 %2 异常->引用循环" ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
	//	return false;
	//}

	if( outputNodeItemInfo->appendOutputNodeItemInfo( inputNodeItemInfo ) == false ) {
		tools::debug::printError( QString( "%1 引用 %2 异常->未知错误" ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	if( inputNodeItemInfo->appendInputNodeItemInfo( outputNodeItemInfo ) == false ) {
		outputNodeItemInfo->removeInputNodeItemInfo( inputNodeItemInfo );
		tools::debug::printError( QString( "%1 引用 %2 异常->未知错误" ).arg( inputNodeItem->getMetaObjectPathName( ) ).arg( outputNodeItem->getMetaObjectPathName( ) ) );
		return false;
	}

	size_t count = linkVectorPairt.size( );
	auto data = linkVectorPairt.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] != nullptr && data[ index ]->inputPort == input_port )
			return data[ index ]->link( output_port );
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
			QString msg( "%1 找不到匹配的具体输出" );
			tools::debug::printError( msg.arg( outputParentNodeItem->getMetaObjectPathName( ) ) );
			return;
		}

		auto inputParentNodeItem = input_port->parentItem;
		NodeItemInfo *inputInfo;
		if( getNodeItemInfo( inputParentNodeItem, inputInfo ) == false ) {
			QString msg( "%1 找不到匹配的具体输入" );
			tools::debug::printError( msg.arg( inputParentNodeItem->getMetaObjectPathName( ) ) );
			return;
		}

		outputInfo->removeInputNodeItemInfo( inputInfo );
		inputInfo->removeOutputNodeItemInfo( outputInfo );
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
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;

	// 节点数组指针
	auto data = generateNodeItems.data( );
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
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return nullptr;
	return generateNodeItems.data( )[ count - 1 ]->nodeItem;
}
void NodeDirector::draw( QPainter &painter_target ) const {

	size_t count = generateNodeItems.size( );
	size_t index = 0;
	if( count > 0 ) {
		auto data = generateNodeItems.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				if( nodeItem == nullptr )
					continue;
				painter_target.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
			}
	}

	count = linkVectorPairt.size( );
	if( count > 0 ) {
		QPoint inport;
		QPoint outport;
		size_t outIndex;

		auto nodePortLinkInfo = linkVectorPairt.data( );
		index = 0;
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
std_vector< NodeItem * > NodeDirector::getNodeItems( ) const {
	std_vector< NodeItem * > result;
	size_t count = generateNodeItems.size( );
	auto data = generateNodeItems.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ] != nullptr )
			result.emplace_back( data[ index ]->nodeItem );
	return result;
}

std_vector< QImage * > NodeDirector::getNodeItemRenders( ) const {
	std_vector< QImage * > result;
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return result;
	auto data = generateNodeItems.data( );
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
	return this->createMenu( );
}
// todo : 节点释放调用
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
	count = generateNodeItems.size( );
	NodeItemInfo *itemInfo = nullptr;
	if( count != 0 ) {
		auto nodeitemPtrData = generateNodeItems.data( );
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
		}
	}
	return true;
}

bool NodeDirector::getNodeItemInfo( const NodeItem *get_nodeitem_ptr, NodeItemInfo *&result_link ) {
	size_t linkCount = generateNodeItems.size( );
	if( linkCount == 0 )
		return false;
	auto linkArrayDataPtr = generateNodeItems.data( );
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
	auto clone = generateNodeItems;
	generateNodeItems.clear( );
	for( auto removeItem : clone )
		if( removeItem )
			delete removeItem->nodeItem;

	mainWidget = main_widget;
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	varGenerate = applicationInstancePtr->getVarGenerate( );
	if( nodeItemCreateMenu )
		delete nodeItemCreateMenu;
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
	size_t count = generateNodeItems.size( );
	auto data = generateNodeItems.data( );
	size_t index = 0;
	NodeItemInfo *nodeItemInfo = new NodeItemInfo( new_node_item );
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = nodeItemInfo;
			break;
		}
	if( index == count ) {
		generateNodeItems.emplace_back( nodeItemInfo );
		++count;
		data = generateNodeItems.data( ); // 更新基址
	}
	size_t checkCode = count;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr || data[ index ]->nodeItem->generateCode != ( index + 1 ) ) { // 掉链子了
			checkCode = index + 1;
			index = 0; // 重新遍历
			for( ; index < count; ++index )
				if( data[ index ] == nullptr || data[ index ]->nodeItem->generateCode == checkCode ) {
					index = checkCode + 1;
					checkCode = count;
					break;
				}
			if( index == count )
				break;

		}
	new_node_item->generateCode = checkCode;
	new_node_item->move( mainWidget->mapFromGlobal( nodeItemCreateMenu->pos( ) ) );
	connect( new_node_item, &NodeItem::releaseThisPtr, [this] ( NodeItem *release_node_item ) {
		rleaseNodeItem( release_node_item ); // 管理对象的所有信息
	} );
	connect( nodeItemInfo, &NodeItemInfo::releaseThisPtr, this, &NodeDirector::releaseNodeItemInfoSignal );
	connect( nodeItemInfo, &NodeItemInfo::nodeItemInfoRefChangeOutputNodeItem, this, &NodeDirector::nodeItemInfoRefChangeOutputNodeItem );
	connect( nodeItemInfo, &NodeItemInfo::nodeItemInfoRefChangeInputNodeItem, this, &NodeDirector::nodeItemInfoRefChangeInputNodeItem );
	emit generateNodeItemSignal( new_node_item );
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
		if( data[ index ]->inputPort == input_port ) {
			result_menu_ptr = data[ index ]->removeLinkMenu;
			return true;
		}
	return false;
}
bool NodeDirector::getItemManageMenu( const NodeItem *node_item_ptr, QMenu *&result_menu_ptr ) {
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return false;
	auto data = generateNodeItems.data( );
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
	if( applicationInstancePtr->getVarGenerate( )->toOBjVector( typeid( NodeDirector ), this, resultCount, source_data_ptr, resultCount ) )
		return resultCount;
	return 0;
}

NodeDirector::~NodeDirector( ) {
	emit releaseThisSignal( this );
	size_t count;
	size_t index;

	count = generateNodeItems.size( );
	if( count ) {
		index = 0;
		auto data = generateNodeItems.data( );
		for( ; index < count; ++index )
			if( data[ index ] != nullptr ) {
				NodeItem *nodeItem = data[ index ]->nodeItem;
				NodeItemInfo *nodeItemInfo = data[ index ];
				data[ index ] = nullptr;
				delete nodeItemInfo;
				delete nodeItem;
			}
	}

	nodeItemCreateMenu->disconnect( nodeItemCreateMenu, &QMenu::destroyed, this, &NodeDirector::resetMenu );
	delete nodeItemCreateMenu;
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
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return nodeItemEnum::Click_Type::None;
	// 节点数组指针
	auto data = generateNodeItems.data( );
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
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return nodeItemEnum::Click_Type::None;
	// 节点数组指针
	auto data = generateNodeItems.data( );
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
	size_t count = generateNodeItems.size( );
	if( count == 0 )
		return nodeItemEnum::Click_Type::None;
	// 节点数组指针
	auto data = generateNodeItems.data( );
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
