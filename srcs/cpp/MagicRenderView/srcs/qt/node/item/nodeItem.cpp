#include "./nodeItem.h"

#include <QMetaEnum>
#include <QPainter>
#include <QPainterPath>
#include <qdir.h>

#include <qt/application/application.h>
#include <qt/node/prot/inputProt/nodeInputPort.h>
#include <qt/node/prot/outputProt/nodeOutputPort.h>
#include <qt/varType/I_Var.h>
#include <qt/widgets/mainWidget.h>

Imp_StaticMetaInfo( NodeItem, QObject::tr( "NodeItem" ), QObject::tr( "item" ) );

/// @brief 输入输入端口之间的空间大小
int NodeItem::midPortSpace = 25;
/// @brief 边缘顶端空间大小
int NodeItem::borderTopSpace = 0;
/// @brief 上下端口之间的空间大小
int NodeItem::portSpace = 0;
/// @brief 标题到端口的空间大小
int NodeItem::titleToPortSpace = 0;
/// @brief 边缘底部空间大小
int NodeItem::borderBoomSpace = 0;
/// @brief 边缘空间左侧空间大小
int NodeItem::borderLeftSpace = 0;
/// @brief 边缘右侧空间大小
int NodeItem::borderRightSpace = 0;

NodeItem::NodeItem( ) : QObject( ), nodeItemRender( new QImage( 10, 10, QImage::Format_RGBA8888 ) ), inputBuff( new QImage( 10, 10, QImage::Format_RGBA8888 ) ), outputBuff( new QImage( 10, 10, QImage::Format_RGBA8888 ) ), titleBuff( new QImage( 10, 10, QImage::Format_RGBA8888 ) ) {

	inputBuffHeight = 0;
	inputBuffWidth = 0;
	outputBuffHeight = 0;
	outputBuffWidth = 0;
	titleHeight = 0;
	titleWidth = 0;
	applicationInstancePtr = Application::getApplicationInstancePtr( );
	nodeItemRender->fill( 0 );
	inputBuff->fill( 0 );
	outputBuff->fill( 0 );
	titleBuff->fill( 0 );
	nodeItemInfoScrollAreaWidgetWidget = nullptr;
	nodeItemInfoWidget = nullptr;
}
NodeItem::~NodeItem( ) {
	emit releaseThisPtr( this );
	size_t index = 0;
	size_t count = nodeInputProtVector.size( );
	auto inputVectorPtr = nodeInputProtVector.data( );
	for( ; index < count; ++index )
		delete inputVectorPtr[ index ].first;
	nodeInputProtVector.clear( );

	index = 0;
	count = nodeOutputProtVector.size( );
	auto outputVectorPtr = nodeOutputProtVector.data( );
	for( ; index < count; ++index )
		delete outputVectorPtr[ index ].first;
	nodeOutputProtVector.clear( );

	index = 0;
	count = nodeVarVector.size( );
	auto varVectorPtr = nodeVarVector.data( );
	for( ; index < count; ++index )
		delete varVectorPtr[ index ];
	nodeVarVector.clear( );

	delete nodeItemRender;
	delete inputBuff;
	delete outputBuff;
	delete titleBuff;
}
void NodeItem::setMainWidget( MainWidget *parent ) {
	//setParent( parent );
	renderMainWidget = parent;
}
bool NodeItem::getInputPortPos( TConstNodePortInputPortPtr input_port_ptr, QPoint &result_pos ) const {
	for( auto &[ inputPortPtr, pos ] : nodeInputProtVector )
		if( inputPortPtr == input_port_ptr ) {
			result_pos = QPoint { pos.first + borderLeftSpace + nodePosX + inputPortPtr->getIcoWidth( ) / 2, pos.second + titleHeight + titleToPortSpace + borderTopSpace + nodePosY + inputPortPtr->height( ) / 2 };
			return true;
		}
	return false;
}
bool NodeItem::getOutputPortPos( TConstNodePortOutputPortPtr output_port_ptr, QPoint &result_pos ) const {
	for( auto &[ onputPortPtr, pos ] : nodeOutputProtVector )
		if( onputPortPtr == output_port_ptr ) {
			result_pos = QPoint { pos.first + borderLeftSpace + inputBuffWidth + midPortSpace + nodePosX + onputPortPtr->width( ) - onputPortPtr->getIcoWidth( ) / 2, pos.second + titleHeight + titleToPortSpace + borderTopSpace + nodePosY + output_port_ptr->height( ) / 2 };
			return true;
		}
	return false;
}
bool NodeItem::hasInputPort( const NodePort *node_port ) {
	for( auto &[ inputPort, pos ] : nodeInputProtVector )
		if( inputPort == node_port )
			return true;
	return false;
}
bool NodeItem::hasOutputPort( const NodePort *node_port ) {
	for( auto &[ onputPortPtr, pos ] : nodeOutputProtVector )
		if( onputPortPtr == node_port )
			return true;
	return false;
}
nodeItemEnum::Click_Type NodeItem::relativePointType( int x, int y ) const {

	// 任意一个坐标超出范围，即可判定非法
	if( x < 0 || y < 0 || x > nodeItemWidth || y > nodeItemHeith )
		return nodeItemEnum::Click_Type::None;
	int drawX = borderLeftSpace;
	int drawY = borderTopSpace + titleToPortSpace + titleHeight;
	if( x > drawX && y > drawY ) { // 需要匹配是否输入和输出节点
		drawX += inputBuffWidth;
		// 判定输入
		if( x < drawX )
			return nodeItemEnum::Click_Type::InputPort;
		drawX += midPortSpace;
		// 判定中间
		if( x < drawX )
			return nodeItemEnum::Click_Type::Space;
		drawX += outputBuffWidth;
		// 判定输出
		if( x < drawX )
			return nodeItemEnum::Click_Type::OutputPort;
	} else
		return nodeItemEnum::Click_Type::Title;
	return nodeItemEnum::Click_Type::Space;
}
NodeInputPort * NodeItem::getNodeInputAtRelativePointType( int x, int y ) const {
	// 数组数量为 0，直接返回
	size_t count = nodeInputProtVector.size( );
	if( count == 0 )
		return nullptr;
	// x 需要大于左侧边缘
	int drawX = borderLeftSpace;
	if( x < drawX )
		return nullptr;
	// x 不能超过输入端宽度
	drawX += inputBuffWidth;
	if( x > drawX )
		return nullptr;
	// y 需要大于 顶部边缘、标题与端口之间留白与标题高度的和
	int drawY = borderTopSpace + titleToPortSpace + titleHeight;
	if( y < drawY )
		return nullptr;
	// y 不能超出输入端高度
	drawY += inputBuffHeight;
	if( y > drawY )
		return nullptr;

	auto data = nodeInputProtVector.data( );
	drawY = borderTopSpace + titleToPortSpace + titleHeight;
	do
		// 从末尾开始判定，如果当前 y 大于端口的 y 所在，则返回这个
		if( --count, y > ( data[ count ].second.second + drawY ) )
			return data[ count ].first;
	while( count > 0 );
	// 最后返回
	return data[ 0 ].first;
}
NodeOutputPort * NodeItem::getNodeOutputPortAtRelativePointType( int x, int y ) const {

	// 数组数量为 0，直接返回
	size_t count = nodeOutputProtVector.size( );
	if( count == 0 )
		return nullptr;
	// x 需要大于 输入端，左侧留白，两端之间留白的和
	int drawX = borderLeftSpace + inputBuffWidth + midPortSpace;

	if( x < drawX )
		return nullptr;
	// 如果大于整个节点宽度
	drawX += outputBuffWidth;
	if( x > drawX )
		return nullptr;

	// y 需要大于 标题，顶端留白，端口与标题两者之间留白的和
	int drawY = borderTopSpace + titleToPortSpace + titleHeight;
	if( y < drawY )
		return nullptr;
	// 如果大于整个节点高度
	drawY += outputBuffHeight;
	if( y > drawY )
		return nullptr;

	auto data = nodeOutputProtVector.data( );
	drawY = borderTopSpace + titleToPortSpace + titleHeight;
	do
		// 从末尾开始判定，如果当前 y 大于端口的 y 所在，则返回这个
		if( --count, y > ( data[ count ].second.second + drawY ) )
			return data[ count ].first;
	while( count > 0 );
	// 最后返回
	return data[ 0 ].first;
}
bool NodeItem::intPortItems( MainWidget *parent ) {
	if( parent == nullptr )
		return false;
	setMainWidget( parent );

	return true;
}
void NodeItem::setNodeTitleName( const NodeItemString_Type &node_title_name ) {
	nodeTitleName = node_title_name;
}

NodeOutputPort * NodeItem::getOutputPort( const QString &output_port_name ) const {
	size_t count = nodeOutputProtVector.size( );
	if( count == 0 )
		return nullptr;
	auto data = nodeOutputProtVector.data( );
	for( size_t index = 0; index < count; ++index )
		if( data[ index ].first->getTitle( ) == output_port_name )
			return data[ index ].first;

	return nullptr;
}

bool NodeItem::appendInputProt( NodeInputPort *input_prot ) {
	nodeInputProtVector.emplace_back( TPortWidgetPort< TNodePortInputPortPtr >( input_prot, { 0, 0 } ) );
	return true;
}
bool NodeItem::removeInputProt( TConstNodePortInputPortPtr input_prot ) {
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
bool NodeItem::removeOutputProt( TConstNodePortOutputPortPtr output_port ) {

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

	// 计算原本高度
	size_t drawCount = nodeInputProtVector.size( );
	if( drawCount == 0 )
		return true;
	int width;
	size_t index = 0;
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
			tools::debug::printError( "改变布局大小失败[" + getMetaObjectPathName( ) + "]" );
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

	// 计算原本高度
	size_t drawCount = nodeOutputProtVector.size( );
	if( drawCount == 0 )
		return true;
	int width;
	size_t index = 0;
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
			tools::debug::printError( "改变布局大小失败[" + getMetaObjectPathName( ) + "]" );
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
		pair.second.first = outputBuffWidth - nodePortRender->width( );
		painter.drawImage( pair.second.first, width, *nodePortRender );
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
	titleHeight = fontMetrics.height( );

	if( nodeItemInfoWidget ) {

		auto nodeItemWidgetIco = applicationInstancePtr->getNodeItemWidgetIco( );

		int imageHeight = nodeItemWidgetIco->height( );
		if( titleHeight < imageHeight )
			titleHeight = imageHeight;
		int imageWidth = nodeItemWidgetIco->width( );
		QSize newSize( titleWidth + 20 + imageWidth, titleHeight );
		if( titleBuff->size( ) != newSize ) {
			*titleBuff = titleBuff->scaled( newSize );
			if( titleBuff->isNull( ) ) {
				tools::debug::printError( "标题适配失败[" + getMetaObjectPathName( ) + "]" );
				return false;
			}
		}

		titleBuff->fill( 0 );
		QPainter painter( titleBuff );
		painter.setFont( font );
		int leading = fontMetrics.leading( );
		int descent = fontMetrics.descent( );
		int y = titleHeight - leading - descent;
		painter.drawText( 0, y, nodeTitleName );
		titleWidth += 20;
		imageHeight = ( titleHeight - imageHeight ) / 2;
		painter.drawImage( titleWidth, imageHeight, *nodeItemWidgetIco );
		titleWidth += imageWidth;
		painter.end( );
	} else {
		QSize newSize( titleWidth, titleHeight );
		if( titleBuff->size( ) != newSize ) {
			*titleBuff = titleBuff->scaled( newSize );
			if( titleBuff->isNull( ) ) {
				tools::debug::printError( "标题适配失败[" + getMetaObjectPathName( ) + "]" );
				return false;
			}
		}
		titleBuff->fill( 0 );
		QPainter painter( titleBuff );
		painter.setFont( font );
		int leading = fontMetrics.leading( );
		int descent = fontMetrics.descent( );
		int y = titleHeight - leading - descent;
		painter.drawText( 0, y, nodeTitleName );
		painter.end( );
	}

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

bool NodeItem::initNodeItem( MainWidget *parent, const std_function< bool( MainWidget *main_widget_parent ) > &init_function ) {
	if( parent == nullptr )
		return false;
	if( NodeItem::intPortItems( parent ) == false )
		return false;
	if( init_function( parent ) == false )
		return false;

	// 更新标题渲染布局
	updateTitleLayout( );
	// 更新输入渲染布局
	updateInputLayout( );
	// 更新输出渲染布局
	updateOutputLayout( );
	// 更新整体渲染布局
	integrateLayout( );
	return true;
}
