#include "./mainWidget.h"

#include <QMetaEnum>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qfile.h>
#include <qmenu.h>

#include <qt/application/application.h>

#include <qt/node/prot/inputProt/nodeInputPort.h>

#include <qt/generate/varGenerate.h>

#include <qt/varType/I_Type.h>
#include <qt/varType/I_Var.h>

#include "../node/director/nodeDirector.h"
#include "../node/widgets/nodeItemInfoScrollAreaWidget.h"

MainWidget::MainWidget( QScrollArea *scroll_area, Qt::WindowFlags flags ) : QWidget( scroll_area, flags ) {
	scrollArea = scroll_area;
	scrollArea->setWidgetResizable( true );
	scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scrollArea->setWidget( this );
	appInstance = Application::getApplicationInstancePtr( );
	varGenerate = appInstance->getVarGenerate( );

	nodeDirector = appInstance->getNodeDirector( );
	keyFirst = "Application/MainWindow/MainWidget";

	appInstance->syncAppValueIniFile( );

	leftFirstSelectItem = leftScondSelectItem = nullptr;
	leftFirstSelectPort = leftScondSelecttPort = nullptr;
	nodeDirector->setContentWidget( this );
	rightMouseBtnCreateNodeItemMenu = nodeDirector->getNodeItemCraeteMenu( );
}
MainWidget::~MainWidget( ) {
	appInstance->syncAppValueIniFile( );
}
size_t MainWidget::loadBin( const uint8_t *bin_data_ptr, const size_t &bin_data_count ) {

	//size_t needCount;
	//size_t result;
	//auto &sizeTypeInfo = typeid( size_t );
	//if( varGenerate->toOBjVector( sizeTypeInfo, &needCount, result, bin_data_ptr, bin_data_count ) == false )
	//	return 0;
	//size_t mod = bin_data_count - result;
	//if( needCount > mod )
	//	return 0;
	//auto offset = bin_data_ptr + result;

	//auto data = supportBin.data( );
	//size_t compCount = supportBin.size( );
	//for( result = 0; result < compCount; ++result )
	//	if( offset[ result ] != data[ result ] )
	//		return 0;
	//offset += result;
	//mod -= result;
	//if( varGenerate->toOBjVector( sizeTypeInfo, &needCount, result, offset, mod ) == false )
	//	return 0;

	//offset += result;
	//mod -= result;
	//auto &nodeItemTypeInfo = typeid( NodeItem );
	//std_vector< NodeItem * > buffList( needCount );
	//auto nodeItemDataPtr = buffList.data( );
	//std_vector< QString > name;
	//while( needCount ) {
	//	NodeItem *item = nullptr;
	//	if( varGenerate->getCheckTypeNames( nodeItemTypeInfo, offset, mod, name ) == false )
	//		return 0;
	//	varGenerate->createCheckTypeName( nodeItemTypeInfo, name[ 0 ], [&item] ( I_Var *create_obj_ptr ) {
	//		item = ( NodeItem * ) create_obj_ptr->getVarPtr( );
	//		connect( item, &NodeItem::releaseThiNodeItem, [create_obj_ptr]( ) {
	//			delete create_obj_ptr;
	//		} );
	//		return true;
	//	} );
	//	if( item == nullptr )
	//		return 0;
	//	if( item->intPortItems( this ) == false )
	//		return 0;
	//	if( varGenerate->toOBjVector( nodeItemTypeInfo, item, result, offset, mod ) == false )
	//		return 0;

	//	offset += result;
	//	mod -= result;
	//	--needCount;
	//	nodeItemDataPtr[ needCount ] = item;
	//	renderWidgetActiveItem = item;
	//	ensureVisibleToItemNode( item );
	//}

	//auto copyMenu = nodeItemList; // 保存旧的

	//needCount = buffList.size( );
	//nodeItemList.resize( needCount );
	//auto desNodeItemPtr = nodeItemList.data( );
	//for( result = 0; result < needCount; ++result ) { // 翻转
	//	desNodeItemPtr[ result ] = nodeItemDataPtr[ needCount - result - 1 ];
	//	connectNodeItem( desNodeItemPtr[ result ] );
	//}

	//for( result = 0; result < needCount; ++result )  // 更新
	//	desNodeItemPtr[ result ]->updataLinkInfo( );

	//needCount = copyMenu.size( );
	//desNodeItemPtr = copyMenu.data( );
	//for( result = 0; result < needCount; ++result ) // 释放
	//	delete desNodeItemPtr[ result ];

	//return offset - bin_data_ptr;
	return 0;
}
size_t MainWidget::saveBin( std_vector< uint8_t > &bin_vector ) {
	std_vector< uint8_t > buff;

	//size_t count = nodeItemList.size( );
	//auto &sizeTypeInfo = typeid( size_t );
	//if( varGenerate->toBinVector( sizeTypeInfo, &count, buff, count ) == false )
	//	return 0;
	//std_vector< uint8_t > resultbuff;
	//resultbuff.append_range( buff );
	//auto &nodeItemTypeInfo = typeid( NodeItem );

	//auto data = nodeItemList.data( );
	//size_t index = 0;
	//for( ; index < count; ++index ) {
	//	NodeItem *nodeItem = data[ index ];
	//	if( varGenerate->toBinVector( nodeItemTypeInfo, nodeItem, buff, count ) == false )
	//		return 0;
	//	resultbuff.append_range( buff );
	//}
	//count = resultbuff.size( ) + supportBin.size( );
	//if( varGenerate->toBinVector( sizeTypeInfo, &count, bin_vector, count ) == false )
	//	return 0;
	//bin_vector.append_range( supportBin );
	//bin_vector.append_range( resultbuff );
	return bin_vector.size( );
}

void MainWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	nodeDirector->draw( painter );
	// 不在拖拽情况下，绘制动态线
	if( leftFirstSelectPort )
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

void MainWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	globalReleasePos = QCursor::pos( );
	fromGlobalReleasePoint = event->pos( );
	switch( mouseButton ) {
		case Qt::RightButton :
			clickNodeItemType = nodeDirector->getClickNodeItem( fromGlobalReleasePoint, rightMouseBtnSelectItem, rightMouseBtnSelectPort );
			if( clickNodeItemType == NodeItem::Click_Type::InputPort )
				tools::debug::printError( "右击输出接口" );
			else
				rightMouseBtnCreateNodeItemMenu->popup( globalReleasePos );
			break;
		case Qt::LeftButton :

			break;
	}

	update( );
}
void MainWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( leftFirstSelectItem == nullptr )
		return;
	QPoint point;
	switch( clickNodeItemType ) {
		case NodeItem::Click_Type::Space :
		case NodeItem::Click_Type::Title :
			mouseMovePoint = event->pos( );
			point = mouseMovePoint - modPoint;
			if( point.x( ) < 0 )
				point.setX( 0 );
			if( point.y( ) < 0 )
				point.setY( 0 );
			leftFirstSelectItem->move( point );
			break;
		case NodeItem::Click_Type::InputPort :
		case NodeItem::Click_Type::OutputPort :
		case NodeItem::Click_Type::None :
			break;
	}
	update( );
}
void MainWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	Qt::MouseButton mouseButton = event->button( );
	globalPressPos = QCursor::pos( );
	fromGlobalPressPoint = event->pos( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			clickNodeItemType = nodeDirector->getClickNodeItem( fromGlobalReleasePoint, leftScondSelectItem, leftScondSelecttPort );
			if( clickNodeItemType != NodeItem::Click_Type::None ) {
				tools::debug::printError( "左击选中接口" );
				nodeDirector->setRaise( leftScondSelectItem );
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
