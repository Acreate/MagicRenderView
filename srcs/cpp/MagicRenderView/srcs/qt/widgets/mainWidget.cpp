#include "./mainWidget.h"

#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qfile.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include <qt/generate/nodeItemGenerate.h>

#include <qt/node/prot/inputProt/nodeInputPort.h>

MainWidget::MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags ) : QWidget( scroll_area, flags ) {
	nodeItemGenerateCode = 1;
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

size_t MainWidget::loadBin( const char *bin_data_ptr, const size_t &bin_data_count ) {
	return 0;
}
size_t MainWidget::saveBin( std_vector<uint8_t> &bin_vector ) {
	return 0;
}
NodeItem * MainWidget::createNodeItem( const QString &dir_name, const QString &node_name ) {
	auto nodeItem = NodeItemGenerate::createNodeItem( dir_name, node_name );
	if( appendNodeItem( nodeItem ) == 0 ) {
		delete nodeItem;
		return nullptr;
	}
	nodeItem->move( fromGlobalReleasePoint );
	return nodeItem;
}
size_t MainWidget::appendNodeItem( NodeItem *new_node_item ) {

	new_node_item->setMainWidget( this );
	if( new_node_item->intPortItems( this ) == false )
		return 0;
	nodeItemList.emplace_back( new_node_item );
	if( new_node_item->generateCode == 0 )
		new_node_item->generateCode = nodeItemList.size( );

	connect( new_node_item, &NodeItem::releaseThiNodeItem, [this] ( NodeItem *release_Item ) {
		auto iterator = nodeItemList.begin( );
		auto end = nodeItemList.end( );
		for( ; iterator != end; ++iterator )
			if( *iterator == release_Item ) {
				nodeItemList.erase( iterator );
				break;
			}
	} );

	renderWidgetActiveItem = new_node_item;
	new_node_item->move( fromGlobalReleasePoint );
	ensureVisibleToItemNode( new_node_item );
	update( );
	return new_node_item->generateCode;
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
	supportBin.clear( );
	//BinGenerate::toBin( supportNodeName, supportNodeBin );
	//BinGenerate::toBin( supporVarType, supportVarTypeBin );
	std_vector< uint8_t > countBuff;
	auto vectorCount = supportVarTypeBin.size( ) + supportNodeBin.size( );
	//BinGenerate::toBin( vectorCount, countBuff );
	supportBin.append_range( countBuff );
	supportBin.append_range( supportNodeBin );
	supportBin.append_range( supportVarTypeBin );
	return supportBin.size( );
}
