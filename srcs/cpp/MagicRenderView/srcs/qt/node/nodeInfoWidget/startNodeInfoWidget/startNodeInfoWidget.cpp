#include "startNodeInfoWidget.h"

#include <QFileDialog>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qevent.h>

#include <qt/application/application.h>
#include <qt/node/director/nodeDirector.h>
#include <qt/node/director/nodeItemInfo.h>
#include <qt/node/item/nodeItem.h>
#include <qt/tools/tools.h>

void StartNodeInfoWidget::fillLinkNodeInfoListWidget( ) {
	clearRenderNodeInfo( );
	if( currentNodeItemInfo == nullptr )
		if( nodeDirector->getNodeItemInfo( nodeItem, currentNodeItemInfo ) == false ) {
			QString msg( "[%1] 无法匹配对应的信息实例对象" );
			msg = msg.arg( nodeItem->getMetaObjectPathName( ) );
			tools::debug::printError( msg );
			return;
		}
	using nodeItemInfoPtrVector = std_vector< NodeItemInfo * >;
	using nodeItemInfoPtrVectorPtr = NodeItemInfo **;
	nodeItemInfoPtrVector nodeItemLayoutBuff;
	nodeItemInfoPtrVector nodeItemLayoutSubBuff;
	nodeItemInfoPtrVector allRenderNodeInfoBuff;

	allRenderNodeInfoBuff = currentNodeItemInfo->outputNodeItemVector;
	size_t count = currentNodeItemInfo->outputNodeItemVector.size( );
	nodeItemInfoPtrVectorPtr saveNodeItemInfoArrayPtr = currentNodeItemInfo->outputNodeItemVector.data( );
	size_t index;

	for( index = 0; index < count; ++index )
		nodeItemLayoutBuff.append_range( saveNodeItemInfoArrayPtr[ index ]->outputNodeItemVector );
	allRenderNodeInfoBuff.append_range( nodeItemLayoutBuff );
	for( count = nodeItemLayoutBuff.size( ); count != 0; count = nodeItemLayoutBuff.size( ) ) {
		saveNodeItemInfoArrayPtr = nodeItemLayoutBuff.data( );
		for( index = 0; index < count; ++index )
			nodeItemLayoutSubBuff.append_range( saveNodeItemInfoArrayPtr[ index ]->outputNodeItemVector );
		allRenderNodeInfoBuff.append_range( nodeItemLayoutBuff );
		nodeItemLayoutBuff = nodeItemLayoutSubBuff;
		nodeItemLayoutSubBuff.clear( );
	}
	count = allRenderNodeInfoBuff.size( );
	saveNodeItemInfoArrayPtr = allRenderNodeInfoBuff.data( );
	auto font = application->getFont( );
	QPainter painter;
	QString drawText( "%1->%2" );

	QString metaObjectPathName;
	QImage *renderTextToImage;
	NodeItem *nodeItem;
	std_pairt< QImage *, QPoint > renderPair;
	QImage *itemWidgetIco = application->getNodeItemWidgetIco( );
	QPen pen;
	pen.setWidth( 2 );
	pen.setColor( Qt::GlobalColor::blue );
	for( index = 0; index < count; ++index ) {
		nodeItem = saveNodeItemInfoArrayPtr[ index ]->nodeItem;
		// 生成节点
		metaObjectPathName = nodeItem->getMetaObjectPathName( );
		renderTextToImage = application->renderTextToImageAtRectBound( &painter, drawText.arg( metaObjectPathName ).arg( nodeItem->generateCode ), Qt::GlobalColor::black, 2 );
		renderPair = std_pairt( renderTextToImage, QPoint( ) );
		if( nodeItem->getNodeItemWidget( ) ) {
			// 存在创建
			int height = itemWidgetIco->height( );
			int textRenderHeight = renderTextToImage->height( );
			if( height != textRenderHeight ) {
				// 缩放一次
				QImage buffIco = itemWidgetIco->scaledToHeight( textRenderHeight );
				int width = buffIco.width( );
				int renderIamgeWidth = renderTextToImage->width( );
				int icoSpace = renderIamgeWidth + 20;
				int newWidth = width + icoSpace;
				int midY = textRenderHeight / 2;
				QImage renderTextToImageBff = QImage( newWidth, textRenderHeight, QImage::Format_RGBA8888 );
				renderTextToImageBff.fill( 0 );
				painter.begin( &renderTextToImageBff );
				painter.drawImage( 0, 0, *renderTextToImage );
				painter.drawImage( icoSpace, 0, buffIco );
				painter.setPen( pen );
				painter.drawLine( renderIamgeWidth, midY, icoSpace, midY );
				painter.end( );
				*renderTextToImage = renderTextToImageBff;
			} else {
				// 正常绘制
				int width = itemWidgetIco->width( );
				int renderIamgeWidth = renderTextToImage->width( );
				int icoSpace = renderIamgeWidth + 20;
				int newWidth = icoSpace + width;
				int midY = textRenderHeight / 2;
				QImage renderTextToImageBff = QImage( newWidth, textRenderHeight, QImage::Format_RGBA8888 );
				renderTextToImageBff.fill( 0 );
				painter.begin( &renderTextToImageBff );
				painter.drawImage( 0, 0, *renderTextToImage );
				painter.drawImage( renderIamgeWidth + 20, 0, *itemWidgetIco );
				painter.setPen( pen );
				painter.drawLine( renderIamgeWidth, midY, icoSpace, midY );
				painter.end( );
				*renderTextToImage = renderTextToImageBff;
			}
		}
		allRenderNodeInfo.emplace_back( saveNodeItemInfoArrayPtr[ index ], renderPair );
	}
	updateLayout( );
}
void StartNodeInfoWidget::clearRenderNodeInfo( ) {
	size_t count = allRenderNodeInfo.size( );
	if( count == 0 )
		return;
	auto data = allRenderNodeInfo.data( );
	for( size_t index = 0; index < count; ++index )
		delete data[ index ].second.first;
	allRenderNodeInfo.clear( );
}
void StartNodeInfoWidget::updateLayout( ) {
	int currentWidgetWidth = this->width( );
	updateBtn->setFixedWidth( currentWidgetWidth );
	int miniHeight = updateBtn->height( );
	size_t count = allRenderNodeInfo.size( );
	auto miniSize = minimumSize( );
	if( count == 0 ) {
		if( miniSize.height( ) < miniHeight )
			setMinimumHeight( miniHeight );
		return;
	}
	miniHeight += 5;
	auto data = allRenderNodeInfo.data( );

	int itemWidgetHeight;
	int itemWidgetWidth;

	for( size_t index = 0; index < count; ++index ) {
		data[ index ].second.second = QPoint( 5, miniHeight );
		itemWidgetWidth = data[ index ].second.first->width( );
		if( currentWidgetWidth < itemWidgetWidth )
			currentWidgetWidth = itemWidgetWidth;
		itemWidgetHeight = data[ index ].second.first->height( );
		miniHeight += itemWidgetHeight + 5;
	}

	if( miniSize.height( ) < miniHeight || miniSize.width( ) < currentWidgetWidth )
		setMinimumHeight( miniHeight );
}

void StartNodeInfoWidget::updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info ) {
	if( currentNodeItemInfo == nullptr )
		if( nodeDirector->getNodeItemInfo( nodeItem, currentNodeItemInfo ) == false ) {
			QString msg( "[%1] 无法匹配对应的信息实例对象" );
			msg = msg.arg( nodeItem->getMetaObjectPathName( ) );
			tools::debug::printError( msg );
			return;
		}

	size_t count = allRenderNodeInfo.size( );
	if( count == 0 )
		return;
	auto data = allRenderNodeInfo.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ].first == node_item_info ) {
			clearRenderNodeInfo( );
			return;
		}

}

StartNodeInfoWidget::StartNodeInfoWidget( NodeItem *node_item ) : nodeItem( node_item ) {
	setMinimumSize( 100, 200 );
	currentNodeItemInfo = nullptr;
	application = Application::getApplicationInstancePtr( );
	nodeDirector = application->getNodeDirector( );
	varGenerate = application->getVarGenerate( );

	updateBtn = new QPushButton( tr( "更新" ), this );

	connect( updateBtn, &QPushButton::clicked, [this] {
		this->fillLinkNodeInfoListWidget( );
	} );
	connect( nodeDirector, &NodeDirector::nodeItemInfoRefChangeInputNodeItem, this, &StartNodeInfoWidget::updateNodeItemInfoBuilderVector );
	connect( nodeDirector, &NodeDirector::releaseNodeItemInfoSignal, this, &StartNodeInfoWidget::updateNodeItemInfoBuilderVector );
	connect( nodeItem, &NodeItem::releaseThisPtr, [this] ( NodeItem *release_ptr ) {
		if( release_ptr != nodeItem )
			return;
		deleteLater( );
	} );
}
void StartNodeInfoWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );

	size_t count = allRenderNodeInfo.size( );
	if( count == 0 )
		return;
	auto data = allRenderNodeInfo.data( );
	auto clickPos = event->pos( );
	int clickPosY = clickPos.y( );
	size_t index = count - 1; // 比较最后一个
	int maxPosY = data[ index ].second.second.y( );
	if( clickPosY > maxPosY ) {
		maxPosY = data[ index ].second.first->height( ) + maxPosY;
		if( maxPosY < clickPosY )
			return; // 在末尾的下面
		clickNodeItemSig( this, data[ index ].first );
		QWidget *nodeItemWidget = data[ index ].first->nodeItem->getNodeItemWidget( );
		if( nodeItemWidget ) {
			nodeItemWidget->show( );
			nodeItemWidget->raise( );
		}
		return;
	}

	maxPosY = data[ 0 ].second.second.y( );
	if( clickPosY < maxPosY )
		return;// 在开始的前面

	index = 1; // 不检测第一个
	for( ; index < count; ++index )
		if( maxPosY = data[ index ].second.second.y( ), clickPosY < maxPosY ) {
			// 如果坐标小于第二个，则检查第一个高度
			index -= 1;
			maxPosY = data[ index ].second.first->height( ) + maxPosY;
			if( maxPosY < clickPosY )
				return; // 未知异常
			clickNodeItemSig( this, data[ index ].first );
			QWidget *nodeItemWidget = data[ index ].first->nodeItem->getNodeItemWidget( );
			if( nodeItemWidget ) {
				nodeItemWidget->show( );
				nodeItemWidget->raise( );
			}
			return;
		}

}
void StartNodeInfoWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	size_t count = allRenderNodeInfo.size( );
	if( count == 0 )
		return;
	QPainter painter( this );
	auto data = allRenderNodeInfo.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		painter.drawImage( data[ index ].second.second, *data[ index ].second.first );
}

void StartNodeInfoWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
}
void StartNodeInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );

	if( allRenderNodeInfo.size( ) == 0 )
		fillLinkNodeInfoListWidget( );
}
