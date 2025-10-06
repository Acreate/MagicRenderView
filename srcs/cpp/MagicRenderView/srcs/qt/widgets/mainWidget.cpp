#include "./mainWidget.h"

#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <QScrollBar>
#include <qboxlayout.h>
#include <qfile.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include <qt/generate/nodeItemGenerate.h>

#include <qt/node/prot/inputProt/nodeInputPort.h>

#include "nodeItemInfoScrollAreaWidget.h"

#include "../generate/varGenerate.h"

#include "../varType/I_Type.h"
#include "../varType/I_Var.h"

MainWidget::MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags ) : QWidget( scroll_area, flags ) {
	scrollArea = scroll_area;
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setWidget( this );
	appInstance = Application::getApplicationInstancePtr( );
	varGenerate = appInstance->getVarGenerate( );
	keyFirst = "Application/MainWindow/MainWidget";

	appInstance->syncAppValueIniFile( );
	rightMouseBtnRemoveOutPortMenu = nullptr;
	rightMouseBtnCreateNodeItemMenu = nullptr;

	leftMouseBtnSelectInputPort = nullptr;
	leftMouseBtnSelectOutputPort = nullptr;
	renderWidgetActiveItem = nullptr;
	leftMouseBtnSelectItem = nullptr;
	leftMouseBtnDragItem = nullptr;
	updateSupport( );
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );
	auto iterator = nodeItemList.begin( );
	auto end = nodeItemList.end( );
	std_vector< NodeItem * > buff( iterator, end );
	nodeItemList.clear( );
	size_t count = buff.size( );
	auto vectorDataPtr = buff.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete vectorDataPtr[ index ];
}
size_t MainWidget::loadBin( const uint8_t *bin_data_ptr, const size_t &bin_data_count ) {

	size_t needCount;
	size_t result;
	auto &sizeTypeInfo = typeid( size_t );
	if( varGenerate->toOBjVector( sizeTypeInfo, &needCount, result, bin_data_ptr, bin_data_count ) == false )
		return 0;
	size_t mod = bin_data_count - result;
	if( needCount > mod )
		return 0;
	auto offset = bin_data_ptr + result;

	auto data = supportBin.data( );
	size_t compCount = supportBin.size( );
	for( result = 0; result < compCount; ++result )
		if( offset[ result ] != data[ result ] )
			return 0;
	offset += result;
	mod -= result;
	if( varGenerate->toOBjVector( sizeTypeInfo, &needCount, result, offset, mod ) == false )
		return 0;

	offset += result;
	mod -= result;
	auto &nodeItemTypeInfo = typeid( NodeItem );
	std_vector< NodeItem * > buffList( needCount );
	auto nodeItemDataPtr = buffList.data( );
	std_vector< QString > name;
	while( needCount ) {
		NodeItem *item = nullptr;
		if( varGenerate->getCheckTypeNames( nodeItemTypeInfo, offset, mod, name ) == false )
			return 0;
		varGenerate->createCheckTypeName( nodeItemTypeInfo, name[ 0 ], [&item] ( I_Var *create_obj_ptr ) {
			item = ( NodeItem * ) create_obj_ptr->getVarPtr( );
			connect( item, &NodeItem::releaseThiNodeItem, [create_obj_ptr]( ) {
				delete create_obj_ptr;
			} );
			return true;
		} );
		if( item == nullptr )
			return 0;
		if( item->intPortItems( this ) == false )
			return 0;
		if( varGenerate->toOBjVector( nodeItemTypeInfo, item, result, offset, mod ) == false )
			return 0;

		offset += result;
		mod -= result;
		--needCount;
		nodeItemDataPtr[ needCount ] = item;
		renderWidgetActiveItem = item;
		ensureVisibleToItemNode( item );
	}

	auto copyMenu = nodeItemList; // 保存旧的

	needCount = buffList.size( );
	nodeItemList.resize( needCount );
	auto desNodeItemPtr = nodeItemList.data( );
	for( result = 0; result < needCount; ++result ) { // 翻转
		desNodeItemPtr[ result ] = nodeItemDataPtr[ needCount - result - 1 ];
		connectNodeItem( desNodeItemPtr[ result ] );
	}

	for( result = 0; result < needCount; ++result )  // 更新
		desNodeItemPtr[ result ]->updataLinkInfo( );

	needCount = copyMenu.size( );
	desNodeItemPtr = copyMenu.data( );
	for( result = 0; result < needCount; ++result ) // 释放
		delete desNodeItemPtr[ result ];

	return offset - bin_data_ptr;
}
size_t MainWidget::saveBin( std_vector< uint8_t > &bin_vector ) {
	std_vector< uint8_t > buff;

	size_t count = nodeItemList.size( );
	auto &sizeTypeInfo = typeid( size_t );
	if( varGenerate->toBinVector( sizeTypeInfo, &count, buff, count ) == false )
		return 0;
	std_vector< uint8_t > resultbuff;
	resultbuff.append_range( buff );
	auto &nodeItemTypeInfo = typeid( NodeItem );

	auto data = nodeItemList.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		NodeItem *nodeItem = data[ index ];
		if( varGenerate->toBinVector( nodeItemTypeInfo, nodeItem, buff, count ) == false )
			return 0;
		resultbuff.append_range( buff );
	}
	count = resultbuff.size( ) + supportBin.size( );
	if( varGenerate->toBinVector( sizeTypeInfo, &count, bin_vector, count ) == false )
		return 0;
	bin_vector.append_range( supportBin );
	bin_vector.append_range( resultbuff );
	return bin_vector.size( );
}
NodeItem * MainWidget::createNodeItem( const QString &dir_name, const QString &node_name ) {
	auto nodeItem = NodeItemGenerate::createNodeItem( dir_name, node_name );
	if( appendNodeItem( nodeItem ) )
		return nodeItem;
	delete nodeItem;
	return nullptr;
}
size_t MainWidget::appendNodeItem( NodeItem *new_node_item ) {

	new_node_item->setMainWidget( this );
	if( new_node_item->intPortItems( this ) == false )
		return 0;
	size_t count = nodeItemList.size( );
	auto data = nodeItemList.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == nullptr ) {
			data[ index ] = new_node_item;
			break;
		}
	if( index == count ) {
		nodeItemList.emplace_back( new_node_item );
		++count;
		data = nodeItemList.data( ); // 更新基址
	}
	size_t checkCode = count;
	for( ; index < count; ++index )
		if( data[ index ]->generateCode != ( index + 1 ) ) { // 掉链子了
			checkCode = index + 1;
			index = 0; // 重新遍历
			for( ; index < count; ++index )
				if( data[ index ]->generateCode == checkCode ) {
					index = checkCode + 1;
					checkCode = count;
					break;
				}
			if( index == count )
				break;

		}
	new_node_item->generateCode = checkCode;

	connectNodeItem( new_node_item );

	renderWidgetActiveItem = new_node_item;
	new_node_item->move( fromGlobalReleasePoint );
	ensureVisibleToItemNode( new_node_item );
	update( );
	return new_node_item->generateCode;
}
NodeItem * MainWidget::getNodeItem( const size_t &generater_code ) const {
	for( auto &item : nodeItemList )
		if( item->generateCode == generater_code )
			return item;
	return nullptr;
}
void MainWidget::connectNodeItem( NodeItem *node_item ) {

	connect( node_item, &NodeItem::releaseThiNodeItem, [this] ( NodeItem *release_Item ) {
		size_t count = nodeItemList.size( );
		auto data = nodeItemList.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == release_Item ) {
				data[ index ] = nullptr;
				update( );
				break;
			}
	} );
}

void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPainterPath painterPath;

	size_t count = nodeItemList.size( );
	auto data = nodeItemList.data( );
	size_t index = 0;
	for( ; index < count; ++index ) {
		NodeItem *nodeItem = data[ index ];
		if( nodeItem == nullptr )
			continue;
		painter.drawImage( nodeItem->getPos( ), *nodeItem->getNodeItemRender( ) );
		auto pairs = nodeItem->getLinkPort( );
		for( auto &item : pairs ) {
			int first = item.first.second.first;
			int second = item.first.second.second;
			int x = item.second.second.first;
			int y = item.second.second.second;

			painterPath.moveTo( first, second );
			painterPath.lineTo( x, y );
		}
	}
	painter.drawPath( painterPath );
	// 不在拖拽情况下，绘制动态线
	if( leftMouseBtnDragItem == nullptr && leftMouseBtnSelectItem )
		painter.drawLine( modPoint, mouseMovePoint );
}
void MainWidget::ensureVisibleToItemNode( const NodeItem *targetItemNode ) {
	auto geometry = targetItemNode->geometry( );
	auto newSize = contentsRect( ).united( geometry ).size( );
	if( size( ) != newSize )
		setMinimumSize( newSize );
	auto targetSize = geometry.bottomRight( );
	scrollArea->ensureVisible( targetSize.x( ), targetSize.y( ) );
}
void MainWidget::updateSupport( ) {
	size_t count = supportNode.size( );
	if( count > 0 ) {
		rightMouseBtnRemoveOutPortMenu->hide( );
		rightMouseBtnCreateNodeItemMenu->hide( );

		for( auto &[ dirMenu, pairs ] : supportNode ) {
			for( auto &[ nodeNameAction, nodeName ] : pairs )
				delete nodeNameAction;
			delete dirMenu;
		}

		delete rightMouseBtnRemoveOutPortMenu;
		delete rightMouseBtnCreateNodeItemMenu;
		delete removeSelectNodeItemMenu;
		supportNode.clear( );
		supportNodeName.clear( );
		supporVarType.clear( );
	}
	rightMouseBtnRemoveOutPortMenu = new QMenu( this );
	removeSelectNodeItemMenu = new QMenu( this );

	removeSelectNodeItemAction = removeSelectNodeItemMenu->addAction( "删除" );
	connect( removeSelectNodeItemAction, &QAction::triggered, [this]( ) {
		if( rightMouseBtnSelectItem == nullptr )
			return;
		delete rightMouseBtnSelectItem;
	} );
	rightMouseBtnCreateNodeItemMenu = new QMenu( this );
	auto infos = NodeItemGenerate::getSupperTyeNodes( );
	for( auto &item : infos ) {
		QString dirName = item.first;
		QMenu *dirMenu = rightMouseBtnCreateNodeItemMenu->addMenu( dirName );
		std_vector_pairt< QAction *, QString > pairs;
		for( auto &className : item.second ) {
			if( className.isEmpty( ) )
				continue;
			auto addAction = dirMenu->addAction( className );
			auto joint = dirName.isEmpty( ) ? className : dirName + "/" + className;
			supportNodeName.emplace_back( joint );
			pairs.emplace_back( addAction, joint );
			connect( addAction, &QAction::triggered, [this, dirName, className]( ) { MainWidget::createNodeItem( dirName, className ); } );
		}
		supportNode.emplace_back( dirMenu, pairs );
	}

	supportInfoToBin( );
}

void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	globalReleasePos = QCursor::pos( );
	fromGlobalReleasePoint = event->pos( );
	size_t count;
	size_t index;
	NodeItem **data;
	switch( mouseButton ) {
		case Qt::RightButton :
			rightMouseBtnSelectItem = nullptr;
			rightMouseBtnSelectPort = nullptr;
			count = nodeItemList.size( );
			if( count != 0 ) {
				data = nodeItemList.data( );
				index = 0;
				for( ; index < count; ++index ) {
					NodeItem *item = data[ index ];
					if( item == nullptr )
						continue;
					QPoint itemPos = item->getPos( );
					modPoint = fromGlobalReleasePoint - itemPos;
					NodeItem::Click_Type pointType = item->relativePointType( modPoint );
					if( pointType != NodeItem::Click_Type::None )
						rightMouseBtnSelectItem = item; // 选中了非空白处
					else
						continue; // 空白处，则跳过循环
					if( pointType == NodeItem::Click_Type::InputPort )
						rightMouseBtnSelectPort = item->getNodeInputAtRelativePointType( modPoint );
					if( rightMouseBtnSelectPort == nullptr )
						break; // 无法获取正确的输入接口
					rightMouseBtnRemoveOutPortMenu->clear( );
					auto nodeOutputPorts = rightMouseBtnSelectPort->getLinkOutputVector( );
					count = nodeOutputPorts.size( );
					if( count == 0 )
						break;
					index = 0;
					auto nodeOutputPortVectorPtr = nodeOutputPorts.data( );
					for( ; index < count; ++index ) {
						auto nodeOutputPort = nodeOutputPortVectorPtr[ index ];
						auto addAction = rightMouseBtnRemoveOutPortMenu->addAction( "删除 [ " + nodeOutputPort->getTitle( ) + " ] 输入接口" );
						connect( addAction, &QAction::triggered, [this, nodeOutputPort]( ) {
							if( rightMouseBtnSelectPort == nullptr )
								return;
							rightMouseBtnSelectPort->disLinkOutputPor( nodeOutputPort );
							update( );
						} );
					}
					// 显示删除定义菜单
					rightMouseBtnRemoveOutPortMenu->move( globalReleasePos );
					rightMouseBtnRemoveOutPortMenu->show( );
					break;
				}
				if( rightMouseBtnSelectItem ) {
					QString text = QString( "删除[%1]" ).arg( rightMouseBtnSelectItem->getMetaObjectPathName( ) );
					removeSelectNodeItemAction->setText( text );
					removeSelectNodeItemMenu->move( globalReleasePos );
					removeSelectNodeItemMenu->show( );
					break; // 如果命中的是面板，而非窗口空白，则跳过
				}
			}
			rightMouseBtnCreateNodeItemMenu->move( globalReleasePos );
			rightMouseBtnCreateNodeItemMenu->show( );
			break;
		case Qt::LeftButton :
			count = nodeItemList.size( );
			if( count != 0 ) {
				data = nodeItemList.data( );
				index = 0;
				for( ; index < count; ++index ) {
					NodeItem *item = data[ index ];
					if( item == nullptr )
						continue;
					QPoint itemPos = item->getPos( );
					modPoint = fromGlobalReleasePoint - itemPos;
					NodeItem::Click_Type pointType = item->relativePointType( modPoint );
					if( pointType == NodeItem::Click_Type::None )
						continue;

					if( doubleClickWidgetActiveItem == item ) {
						auto currentDateTime = QDateTime::currentDateTime( );
						auto seep = currentDateTime - sigClickDateTime;
						if( seep.count( ) < 2000 ) {
							auto editWidget = renderWidgetActiveItem->getEditWidget( );
							if( editWidget ) {
								editWidget->raise( );
								editWidget->show( );
							}

						}
						sigClickDateTime = currentDateTime;
						doubleClickWidgetActiveItem = nullptr;
					} else {
						sigClickDateTime = QDateTime::currentDateTime( );
						doubleClickWidgetActiveItem = item;
					}

					if( leftMouseBtnSelectItem == item )
						break;

					if( leftMouseBtnSelectOutputPort == nullptr && pointType == NodeItem::Click_Type::OutputPort ) {
						leftMouseBtnSelectOutputPort = item->getNodeOutputPortAtRelativePointType( modPoint );
						if( leftMouseBtnSelectOutputPort )
							if( leftMouseBtnSelectOutputPort->getPos( modPoint ) == false )
								leftMouseBtnSelectOutputPort = nullptr;

					} else if( leftMouseBtnSelectInputPort == nullptr && pointType == NodeItem::Click_Type::InputPort ) {
						leftMouseBtnSelectInputPort = item->getNodeInputAtRelativePointType( modPoint );
						if( leftMouseBtnSelectInputPort )
							if( leftMouseBtnSelectInputPort->getPos( modPoint ) == false )
								leftMouseBtnSelectInputPort = nullptr;
					}

					renderWidgetActiveItem = item;
					break;
				}
			}
			break;
	}
	if( leftMouseBtnSelectInputPort && leftMouseBtnSelectOutputPort )
		leftMouseBtnSelectInputPort->linkOutputPort( leftMouseBtnSelectOutputPort );
	else if( leftMouseBtnDragItem ) // 拖拽完毕
		ensureVisibleToItemNode( leftMouseBtnDragItem );
	leftMouseBtnSelectInputPort = nullptr;
	leftMouseBtnSelectOutputPort = nullptr;
	leftMouseBtnSelectItem = nullptr;
	leftMouseBtnDragItem = nullptr;
	update( );
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	mouseMovePoint = event->pos( );
	if( leftMouseBtnDragItem ) {
		QPoint point = mouseMovePoint - modPoint;
		if( point.x( ) < 0 )
			point.setX( 0 );
		if( point.y( ) < 0 )
			point.setY( 0 );
		leftMouseBtnDragItem->move( point );
	}

	doubleClickWidgetActiveItem = nullptr; // 移动则清除双击信息
	update( );
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	globalPressPos = QCursor::pos( );
	fromGlobalPressPoint = event->pos( );
	size_t count;
	size_t index;
	NodeItem **data;
	switch( mouseButton ) {
		case Qt::LeftButton :

			count = nodeItemList.size( );
			if( count == 0 )
				break;
			data = nodeItemList.data( );
			index = 0;
			for( ; index < count; ++index ) {
				NodeItem *item = data[ index ];
				if( item == nullptr )
					continue;
				QPoint itemPos = item->getPos( );
				modPoint = fromGlobalPressPoint - itemPos;
				NodeItem::Click_Type pointType = item->relativePointType( modPoint );
				if( pointType == NodeItem::Click_Type::None )
					continue;
				if( pointType == NodeItem::Click_Type::OutputPort ) {
					leftMouseBtnSelectOutputPort = item->getNodeOutputPortAtRelativePointType( modPoint );
					if( leftMouseBtnSelectOutputPort == nullptr )
						leftMouseBtnDragItem = item;
					if( leftMouseBtnSelectOutputPort->getPos( modPoint ) == false )
						break;
				} else if( pointType == NodeItem::Click_Type::InputPort ) {
					leftMouseBtnSelectInputPort = item->getNodeInputAtRelativePointType( modPoint );
					if( leftMouseBtnSelectInputPort == nullptr )
						leftMouseBtnDragItem = item;
					else if( leftMouseBtnSelectInputPort->getPos( modPoint ) == false )
						break;
				} else
					leftMouseBtnDragItem = item;
				renderWidgetActiveItem = leftMouseBtnSelectItem = item;
				break;
			}
			break;
	}
}
size_t MainWidget::supportInfoToBin( ) {
	size_t result;
	size_t index;
	size_t count = supportNodeName.size( );
	std_vector< uint8_t > buff;
	auto &sizeTTypeInfo = typeid( size_t );
	if( varGenerate->toBinVector( sizeTTypeInfo, &count, supportNodeBin, result ) == false )
		return 0;
	auto data = supportNodeName.data( );
	auto &qstringTypeInfo = typeid( QString );
	for( index = 0; index < count; ++index ) {
		if( varGenerate->toBinVector( qstringTypeInfo, data + index, buff, result ) == false )
			return 0;
		supportNodeBin.append_range( buff );
	}

	count = supporVarType.size( );
	if( varGenerate->toBinVector( sizeTTypeInfo, &count, supportVarTypeBin, result ) == false )
		return 0;
	data = supporVarType.data( );
	for( index = 0; index < count; ++index ) {
		if( varGenerate->toBinVector( qstringTypeInfo, data + index, buff, result ) == false )
			return 0;
		supportVarTypeBin.append_range( buff );
	}

	auto vectorCount = supportVarTypeBin.size( ) + supportNodeBin.size( );

	if( varGenerate->toBinVector( sizeTTypeInfo, &vectorCount, supportBin, result ) == false )
		return 0;
	supportBin.append_range( supportNodeBin );
	supportBin.append_range( supportVarTypeBin );
	return supportBin.size( );
}
