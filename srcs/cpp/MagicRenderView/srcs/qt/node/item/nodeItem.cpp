#include "./nodeItem.h"

#include <QPainter>
#include <QPainterPath>

#include <qt/application/application.h>
#include <qt/node/prot/inputProt/nodeInputPort.h>
#include <qt/node/prot/outputProt/nodeOutputPort.h>

Imp_StaticMetaInfo( NodeItem, QObject::tr( "NodeItem" ), QObject::tr( "item" ) )
bool NodeItem::appendInputProt( NodeInputPort *input_prot ) {
	nodeInputProtVector.emplace_back( input_prot );
	return true;
}
bool NodeItem::removeInputProt( NodeInputPort *input_prot ) {
	size_t count = nodeInputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeInputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ] == input_prot ) {
			nodeInputProtVector.erase( nodeInputProtVector.begin( ) + index );
			return true;
		}
	return false;
}
bool NodeItem::appendOutputProt( NodeOutputPort *output_prot ) {

	nodeOutputProtVector.emplace_back( output_prot );
	return true;
}
bool NodeItem::removeOutputProt( NodeOutputPort *output_port ) {

	size_t count = nodeOutputProtVector.size( ), index = 0;
	if( count == 0 )
		return false;
	auto data = nodeOutputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ] == output_port ) {
			nodeOutputProtVector.erase( nodeOutputProtVector.begin( ) + index );
			return true;
		}
	return false;
}
void NodeItem::updateProtLayout( ) {
	Application *applicationInstancePtr = Application::getApplicationInstancePtr( );
	auto font = applicationInstancePtr->getFont( );
	// 计算字体高度
	auto fontMetrics = QFontMetrics( font );
	int fontHeight = fontMetrics.height( );
	// 顶部留白
	int topSpace = 5;
	// 底部留白
	int boomSpace = 5;
	// 两端上下相间留白
	int lineSpace = 5;
	// 左侧留白
	int leftStartSpaced = 5;
	// 右侧留白
	int rightEndSpaced = 5;
	// 输入输出端口相间留白
	int portSpace = 20;
	// 输入端口最大宽度
	int inputMaxWidth = 0;
	// 输入端口最大高度
	int inputMaxHeight = 0;
	// 输出端口最大宽度
	int outputMaxWidth = 0;
	// 输出端口最大高度
	int outputMaxHeight = 0;
	// 字体占用空间
	int titleUseSpace = fontHeight + topSpace;
	// 输入端口开始坐标
	int inputY = titleUseSpace + lineSpace;
	int inputX = leftStartSpaced;
	// 输出端口开始坐标
	int outputY = inputY;
	int outputX = 0;
	// 端口渲染大小
	QSize protSize;
	// 用于获取端口渲染宽度
	int width;
	// 用于获取端口渲染高度
	int height;
	/*
	 * 检验输入端
	 */
	size_t nodeInputProtVectorCount = nodeInputProtVector.size( ), nodeInputProtVectorIndex = 0;
	auto nodeInputPortDataStartPtr = nodeInputProtVector.data( );
	for( ; nodeInputProtVectorIndex < nodeInputProtVectorCount; ++nodeInputProtVectorIndex ) {
		nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->move( inputX, inputY );
		nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->updateProtLayout( );
		protSize = nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->getSize( );
		width = protSize.width( ), height = protSize.height( );
		inputY += height + lineSpace;
		if( inputMaxWidth < width )
			inputMaxWidth = width;
	}
	/*
	 * 检验输出端
	 */

	size_t nodeOutputProtVectorCount = nodeOutputProtVector.size( ), nodeOutputProtVectorIndex = 0;
	auto nodeOutputPortDataStartPtr = nodeOutputProtVector.data( );

	for( ; nodeOutputProtVectorIndex < nodeOutputProtVectorCount; ++nodeOutputProtVectorIndex ) {
		nodeOutputPortDataStartPtr[ nodeOutputProtVectorIndex ]->updateProtLayout( );
		nodeOutputPortDataStartPtr[ nodeOutputProtVectorIndex ]->moveY( outputY );
		protSize = nodeOutputPortDataStartPtr[ nodeOutputProtVectorIndex ]->getSize( );
		width = protSize.width( ), height = protSize.height( );
		outputY += height + lineSpace;
		if( outputMaxWidth < width )
			outputMaxWidth = width;
	}
	// 比较最大宽度
	width = outputMaxWidth + portSpace + leftStartSpaced + rightEndSpaced + inputMaxWidth;
	// 比较最大高度
	height = outputY > inputY ? outputY : inputY;
	// 加上标题与下边留白
	height += titleUseSpace + boomSpace;
	// 配置大小
	nodePortRender = QImage( width, height, QImage::Format_RGBA8888 );
	nodePortRender.fill( 0 );
	// 生成绘制对象
	QPainter painter( &nodePortRender );
	painter.setFont( font );
	/*
	 * 绘制标题
	 */
	int horizontalAdvance = fontMetrics.horizontalAdvance( nodeTitleName );// 标题长度
	int titleX = ( width - horizontalAdvance ) / 2;
	painter.drawText( titleX, titleUseSpace, nodeTitleName );
	/*
	 * 绘制输入端
	 */
	nodeInputProtVectorIndex = 0;
	for( ; nodeInputProtVectorIndex < nodeInputProtVectorCount; ++nodeInputProtVectorIndex )
		painter.drawImage( nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->getPos( ), nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->getNodePortRender( ) );
	/*
	 * 绘制输出端
	 */
	nodeOutputProtVectorIndex = 0;
	for( ; nodeOutputProtVectorIndex < nodeOutputProtVectorCount; ++nodeOutputProtVectorIndex ) {
		nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->moveX( width - nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->getSize( ).width( ) );
		painter.drawImage( nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->getPos( ), nodeInputPortDataStartPtr[ nodeInputProtVectorIndex ]->getNodePortRender( ) );
	}
}
NodeOutputPort * NodeItem::formPosNodeOutputPort( const QPoint &pos ) {

	size_t count = nodeOutputProtVector.size( ), index = 0;
	if( count == 0 )
		return nullptr;
	auto data = nodeOutputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ]->getPos( ) == pos )
			return data[ index ];
	return nullptr;
}
NodeOutputPort * NodeItem::formIndexNodeOutputPort( const size_t &index ) {
	size_t count = nodeOutputProtVector.size( );
	if( count < index )
		return nodeOutputProtVector.data( )[ index ];
	return nullptr;
}
NodeInputPort * NodeItem::formPosNodeInputPort( const QPoint &pos ) {
	size_t count = nodeInputProtVector.size( ), index = 0;
	if( count == 0 )
		return nullptr;
	auto data = nodeInputProtVector.data( );
	for( ; index < count; ++index )
		if( data[ index ]->getPos( ) == pos )
			return data[ index ];
	return nullptr;
}
NodeInputPort * NodeItem::formIndexNodeInputPort( const size_t &index ) {
	size_t count = nodeInputProtVector.size( );
	if( count < index )
		return nodeInputProtVector.data( )[ index ];
	return nullptr;
}
