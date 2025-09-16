#include "./nodeItem.h"

#include <QPainter>
#include <QPainterPath>
#include <qdir.h>

#include <qt/application/application.h>
#include <qt/node/prot/inputProt/nodeInputPort.h>
#include <qt/node/prot/outputProt/nodeOutputPort.h>

Imp_StaticMetaInfo( NodeItem, QObject::tr( "NodeItem" ), QObject::tr( "item" ) );
NodeItem::NodeItem( NodeItem_ParentPtr_Type *parent ) : QObject( parent ), nodeItemRender( new QImage( 10, 10, QImage::Format_RGBA8888 ) ), inputBuff( new QImage( 10, 10, QImage::Format_RGBA8888 ) ), outputBuff( new QImage( 10, 10, QImage::Format_RGBA8888 ) ), titleBuff( new QImage( 10, 10, QImage::Format_RGBA8888 ) ) {
	midPortSpace = 5 * 3;
	borderTopSpace = 5;
	borderRightSpace = 5;
	borderLeftSpace = 5;
	borderBoomSpace = 5;
	titleToPortSpace = 5;
	portSpace = 5;
	inputBuffHeight = 0;
	inputBuffWidth = 0;
	outputBuffHeight = 0;
	outputBuffWidth = 0;
	titleHeight = 0;
	titleWidth = 0;
	applicationInstancePtr = Application::getApplicationInstancePtr( );
}
NodeItem::~NodeItem( ) {
	delete nodeItemRender;
	delete inputBuff;
	delete outputBuff;
	delete titleBuff;
}
NodeItem::Click_Type NodeItem::relativePointType( int x, int y ) const {

	// 任意一个坐标超出范围，即可判定非法
	if( x < 0 || y < 0 || x > nodeItemWidth || y > nodeItemHeith )
		return Click_Type::None;
	int drawX = borderLeftSpace;
	int drawY = borderTopSpace + titleToPortSpace + titleHeight;
	if( x > drawX && y > drawY ) { // 需要匹配是否输入和输出节点
		drawX += inputBuffWidth;
		// 判定输入
		if( x < drawX )
			return Click_Type::InputPort;
		drawX += midPortSpace;
		// 判定中间
		if( x < drawX )
			return Click_Type::Space;
		drawX += outputBuffWidth;
		// 判定输出
		if( x < drawX )
			return Click_Type::OutputPort;

	} else
		return Click_Type::Title;
	return Click_Type::Space;
}
NodeInputPort * NodeItem::getNodeInputAtRelativePointType( int x, int y ) const {
	size_t count = nodeInputProtVector.size( );
	if( count == 0 )
		return nullptr;
	int drawX = borderLeftSpace;

	if( x < drawX )
		return nullptr;
	drawX += inputBuffWidth;
	if( x > drawX )
		return nullptr;

	int drawY = borderTopSpace + titleToPortSpace + titleHeight;
	if( y < drawY )
		return nullptr;
	drawY += inputBuffHeight;
	if( y > drawY )
		return nullptr;

	auto data = nodeInputProtVector.data( );
	--count;
	do

		if( y > ( data[ count ].second.second + borderLeftSpace ) )
			return data[ count ].first;
		else
			--count;
	while( count != 0 );

	return data[ 0 ].first;
}
NodeOutputPort * NodeItem::getNodeOutputPortAtRelativePointType( int x, int y ) const {

	size_t count = nodeOutputProtVector.size( );
	if( count == 0 )
		return nullptr;
	int drawX = borderLeftSpace + inputBuffWidth + midPortSpace;

	if( x < drawX )
		return nullptr;
	drawX += outputBuffWidth;
	if( x > drawX )
		return nullptr;

	int drawY = borderTopSpace + titleToPortSpace + titleHeight;
	if( y < drawY )
		return nullptr;
	drawY += outputBuffHeight;
	if( y > drawY )
		return nullptr;

	auto data = nodeOutputProtVector.data( );
	drawX = borderLeftSpace + inputBuffWidth + midPortSpace;
	--count;
	do
		if( y > ( data[ count ].second.second + drawX ) )
			return data[ count ].first;
		else
			--count;
	while( count != 0 );

	return data[ 0 ].first;
}
bool NodeItem::intPortItems( ) {
	setNodeTitleName( getMetaObjectName( ) );
	return true;
}
void NodeItem::setNodeTitleName( const NodeItemString_Type &node_title_name ) {
	nodeTitleName = node_title_name;
}

bool NodeItem::appendInputProt( NodeInputPort *input_prot ) {
	nodeInputProtVector.emplace_back( TPortWidgetPort< TNodePortInputPortPtr >( input_prot, { 0, 0 } ) );
	return true;
}
bool NodeItem::removeInputProt( NodeInputPort *input_prot ) {
	size_t count = nodeInputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeInputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ].first == input_prot ) {
			nodeInputProtVector.erase( nodeInputProtVector.begin( ) + index );
			return true;
		}
	return false;
}
bool NodeItem::appendOutputProt( NodeOutputPort *output_prot ) {

	nodeOutputProtVector.emplace_back( TPortWidgetPort< TNodePortOutputPortPtr >( output_prot, { 0, 0 } ) );

	return true;
}
bool NodeItem::removeOutputProt( NodeOutputPort *output_port ) {

	size_t count = nodeOutputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeOutputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ].first == output_port ) {
			nodeOutputProtVector.erase( nodeOutputProtVector.begin( ) + index );
			return true;
		}
	return false;
}

bool NodeItem::updateInputLayout( ) {

	int width;
	// 计算原本高度
	size_t drawCount = nodeInputProtVector.size( ), index = 0;
	auto drawPortDataPtr = nodeInputProtVector.data( );
	for( ; index < drawCount; ++index ) {
		NodeInputPort *nodeInputPort = drawPortDataPtr[ index ].first;
		if( nodeInputPort->updateProtLayout( ) == false )
			return false;
		QImage *nodePortRender = nodeInputPort->getNodePortRender( );
		inputBuffHeight += nodePortRender->height( ) + portSpace;
		width = nodePortRender->width( );
		if( inputBuffWidth < width )
			inputBuffWidth = width;
	}
	if( drawCount != 0 )
		inputBuffHeight -= portSpace;
	auto newImageSize = QSize( inputBuffWidth, inputBuffHeight );
	// 缩放
	if( inputBuff->size( ) != newImageSize ) {
		*inputBuff = inputBuff->scaled( newImageSize );
		if( inputBuff->isNull( ) ) {
			tools::debug::printError( "改变布局大小失败[" + getMetaObjectName( ) + "]" );
			return false;
		}
	}
	// 填充
	inputBuff->fill( 0 );
	// 绘制
	QPainter painter( inputBuff );
	width = 0; // 充当临时 y 坐标
	for( index = 0; index < drawCount; ++index ) {
		auto &pair = drawPortDataPtr[ index ];
		NodeInputPort *nodeInputPort = pair.first;
		auto nodePortRender = nodeInputPort->getNodePortRender( );
		painter.drawImage( 0, width, *nodePortRender );
		pair.second.first = 0;
		pair.second.second = width;
		width += nodePortRender->height( ) + portSpace;
	}
	painter.end( );
	return true;
}
bool NodeItem::updateOutputLayout( ) {

	int width;

	// 计算原本高度
	size_t drawCount = nodeOutputProtVector.size( ), index = 0;
	auto drawPortDataPtr = nodeOutputProtVector.data( );
	for( ; index < drawCount; ++index ) {
		NodeOutputPort *nodeOutputPort = drawPortDataPtr[ index ].first;
		if( nodeOutputPort->updateProtLayout( ) == false )
			return false;
		QImage *nodePortRender = nodeOutputPort->getNodePortRender( );
		outputBuffHeight += nodePortRender->height( ) + portSpace;
		width = nodePortRender->width( );
		if( outputBuffWidth < width )
			outputBuffWidth = width;
	}
	if( drawCount != 0 )
		outputBuffHeight -= portSpace;

	auto newImageSize = QSize( outputBuffWidth, outputBuffHeight );
	// 缩放
	if( outputBuff->size( ) != newImageSize ) {
		*outputBuff = outputBuff->scaled( newImageSize );
		if( outputBuff->isNull( ) ) {
			tools::debug::printError( "改变布局大小失败[" + getMetaObjectName( ) + "]" );
			return false;
		}
	}
	// 填充
	outputBuff->fill( 0 );
	// 绘制
	QPainter painter( outputBuff );
	width = 0; // 充当临时 y 坐标
	for( index = 0; index < drawCount; ++index ) {
		auto &pair = drawPortDataPtr[ index ];
		NodeOutputPort *nodeOutputPort = pair.first;
		auto nodePortRender = nodeOutputPort->getNodePortRender( );
		painter.drawImage( 0, width, *nodePortRender );
		pair.second.first = 0;
		pair.second.second = width;
		width += nodePortRender->height( ) + portSpace;
	}
	painter.end( );
	return true;
}
bool NodeItem::updateTitleLayout( ) {
	auto font = applicationInstancePtr->getFont( );
	QFontMetrics fontMetrics( font );
	auto boundingRect = fontMetrics.boundingRect( nodeTitleName );

	titleWidth = boundingRect.width( ) + boundingRect.x( );
	titleHeight = fontMetrics.leading( );
	int fontHeight = fontMetrics.height( ) + titleHeight;
	titleHeight = fontHeight - fontMetrics.descent( ) - titleHeight;
	QSize newSize( titleWidth, titleHeight );
	if( titleBuff->size( ) != newSize ) {
		*titleBuff = titleBuff->scaled( newSize );
		if( titleBuff->isNull( ) ) {
			tools::debug::printError( "标题适配失败[" + getMetaObjectName( ) + "]" );
			return false;
		}
	}

	titleBuff->fill( 0 );

	QPainter painter( titleBuff );
	painter.setFont( font );
	painter.drawText( 0, titleHeight, nodeTitleName );
	painter.end( );
	return true;
}
bool NodeItem::integrateLayout( ) {

	// 输入与输入端高度比较，获取最大高度
	nodeItemHeith = inputBuffHeight > outputBuffHeight ? inputBuffHeight : outputBuffHeight;
	// 得到输入输出端的面板宽度
	nodeItemWidth = outputBuffWidth + inputBuffWidth + midPortSpace;
	// 面板宽度与标题宽度比较，获取最大值
	nodeItemWidth = titleWidth > nodeItemWidth ? titleWidth : nodeItemWidth;

	nodeItemHeith += titleHeight + titleToPortSpace + borderBoomSpace + borderTopSpace;
	nodeItemWidth += borderLeftSpace + borderRightSpace;

	*nodeItemRender = nodeItemRender->scaled( nodeItemWidth, nodeItemHeith );
	if( nodeItemRender->isNull( ) ) {
		tools::debug::printError( "节点渲染适配大小失败[" + getStaticMetaObjectName( ) + "]" );
		return false;
	}
	nodeItemRender->fill( 0 );

	QPainter painter( nodeItemRender );
	// 绘制标题
	int drawX = ( nodeItemWidth - titleWidth ) / 2;
	int drawY = borderTopSpace;
	painter.drawImage( drawX, drawY, *titleBuff );
	// 绘制左侧面板
	drawX = borderLeftSpace;
	drawY = borderTopSpace + titleHeight + titleToPortSpace;
	painter.drawImage( drawX, drawY, *inputBuff );
	// 绘制右侧面板
	drawX = borderLeftSpace + inputBuffWidth + midPortSpace;
	drawY = borderTopSpace + titleHeight + titleToPortSpace;
	painter.drawImage( drawX, drawY, *outputBuff );
	// 绘制边缘
	auto pen = painter.pen( );
	pen.setColor( Qt::GlobalColor::darkYellow );
	pen.setWidth( 2 );
	painter.setPen( pen );
	painter.drawRect( 0, 0, nodeItemWidth, nodeItemHeith );
	painter.end( );

	return true;
}

NodeOutputPort * NodeItem::formIndexNodeOutputPort( const size_t &index ) {
	size_t count = nodeOutputProtVector.size( );
	if( count < index )
		return nodeOutputProtVector.data( )[ index ].first;
	return nullptr;
}
NodeInputPort * NodeItem::formIndexNodeInputPort( const size_t &index ) {
	size_t count = nodeInputProtVector.size( );
	if( count < index )
		return nodeInputProtVector.data( )[ index ].first;
	return nullptr;
}
