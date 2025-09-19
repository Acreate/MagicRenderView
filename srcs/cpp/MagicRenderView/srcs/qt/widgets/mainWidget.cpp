#include "./mainWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qfile.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include "../generate/nodeItemGenerate.h"
#include "../generate/varTypeGenerate.h"

#include "../node/prot/inputProt/nodeInputPort.h"

MainWidget::MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags ) : QWidget( scroll_area, flags ) {
	scrollArea = scroll_area;
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setWidget( this );
	appInstance = Application::getApplicationInstancePtr( );

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
	for( size_t index = 0; index < count; ++index )
		delete vectorDataPtr[ index ];
}
void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	QPainterPath painterPath;
	auto iterator = nodeItemList.begin( );
	auto end = nodeItemList.end( );
	for( ; iterator != end; ++iterator ) {
		NodeItem *nodeItem = *iterator;
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
		supportNode.clear( );
		supportNodeName.clear( );
		supporVarType.clear( );
	}
	rightMouseBtnRemoveOutPortMenu = new QMenu( this );
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
			connect( addAction, &QAction::triggered, [this, dirName, className]( ) {
				auto nodeItem = NodeItemGenerate::createNodeItem( this, dirName, className );
				if( nodeItem->intPortItems( ) == false ) {
					delete nodeItem;
					return;
				}
				nodeItem->move( fromGlobalReleasePoint );
				nodeItemList.emplace_back( nodeItem );

				connect( nodeItem, &NodeItem::releaseThiNodeItem, [this] ( NodeItem *release_Item ) {
					auto iterator = nodeItemList.begin( );
					auto end = nodeItemList.end( );
					for( ; iterator != end; ++iterator )
						if( *iterator == release_Item ) {
							nodeItemList.erase( iterator );
							break;
						}
				} );

				renderWidgetActiveItem = nodeItem;

				ensureVisibleToItemNode( nodeItem );
				update( );
			} );
		}
		supportNode.emplace_back( dirMenu, pairs );
	}
	supporVarType = VarTypeGenerate::supportTypes( );
	supportInfoToBin( );
}

void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	globalReleasePos = QCursor::pos( );
	fromGlobalReleasePoint = event->pos( );
	switch( mouseButton ) {
		case Qt::RightButton :
			rightMouseBtnSelectItem = nullptr;
			rightMouseBtnSelectPort = nullptr;
			for( NodeItem *item : nodeItemList ) {
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
				auto &nodeOutputPorts = rightMouseBtnSelectPort->getLinkOutputVector( );
				size_t count = nodeOutputPorts.size( );
				if( count == 0 )
					break;
				size_t index = 0;
				auto nodeOutputPortVectorPtr = nodeOutputPorts.data( );
				for( ; index < count; ++index ) {
					NodeOutputPort *nodeOutputPort = nodeOutputPortVectorPtr[ index ];
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
			if( rightMouseBtnSelectItem )
				break; // 如果命中的是面板，而非窗口空白，则跳过
			rightMouseBtnCreateNodeItemMenu->move( globalReleasePos );
			rightMouseBtnCreateNodeItemMenu->show( );
			break;
		case Qt::LeftButton :
			for( NodeItem *item : nodeItemList ) {
				QPoint itemPos = item->getPos( );
				modPoint = fromGlobalReleasePoint - itemPos;
				NodeItem::Click_Type pointType = item->relativePointType( modPoint );
				if( pointType == NodeItem::Click_Type::None )
					continue;
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
	if( leftMouseBtnSelectItem == nullptr )
		return;
	mouseMovePoint = event->pos( );
	if( leftMouseBtnDragItem )
		leftMouseBtnDragItem->move( mouseMovePoint - modPoint );
	update( );
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );

	globalPressPos = QCursor::pos( );
	fromGlobalPressPoint = event->pos( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			for( NodeItem *item : nodeItemList ) {
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

	supportNodeBin.clear( );
	supportVarTypeBin.clear( );
	supportBin.clear( );
	std_vector< uint8_t > foreachBuff;
	size_t index = 0;
	size_t vectorCount = 0;
	size_t count = supportNodeName.size( );
	auto data = supportNodeName.data( );
	std_vector< uint8_t > strBuff;
	std_vector< uint8_t > countBuff;
	BinGenerate::toVectorUInt8Data( count, countBuff );
	foreachBuff.append_range( countBuff );

	for( ; index < count; ++index ) {
		BinGenerate::toVectorUInt8Data( data[ index ], strBuff );
		vectorCount = strBuff.size( );
		BinGenerate::toVectorUInt8Data( vectorCount, countBuff );
		foreachBuff.append_range( countBuff );
		foreachBuff.append_range( strBuff );
	}
	vectorCount = foreachBuff.size( );
	BinGenerate::toVectorUInt8Data( vectorCount, countBuff );
	supportNodeBin.append_range( countBuff );
	supportNodeBin.append_range( foreachBuff );

	foreachBuff.clear(  );
	index = 0;
	vectorCount = 0;
	count = supporVarType.size( );
	data = supporVarType.data( );
	BinGenerate::toVectorUInt8Data( count, countBuff );
	foreachBuff.append_range( countBuff );
	for( ; index < count; ++index ) {
		BinGenerate::toVectorUInt8Data( data[ index ], strBuff );
		vectorCount = strBuff.size( );
		BinGenerate::toVectorUInt8Data( vectorCount, countBuff );
		foreachBuff.append_range( countBuff );
		foreachBuff.append_range( strBuff );
	}
	vectorCount = foreachBuff.size( );
	BinGenerate::toVectorUInt8Data( vectorCount, countBuff );
	supportVarTypeBin.append_range( countBuff );
	supportVarTypeBin.append_range( foreachBuff );

	vectorCount = supportVarTypeBin.size( ) + supportNodeBin.size( );
	BinGenerate::toVectorUInt8Data( vectorCount, countBuff );
	supportBin.append_range( countBuff );
	supportBin.append_range( supportNodeBin );
	supportBin.append_range( supportVarTypeBin );
	return supportBin.size( );
}
