#include "startNodeInfoWidget.h"

#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <qboxlayout.h>
#include <qevent.h>

#include <qt/application/application.h>
#include <qt/node/director/nodeDirector.h>
#include <qt/node/director/nodeItemInfo.h>
#include <qt/node/item/nodeItem.h>
#include <qt/tools/tools.h>

#include "nodeItemInfoItemWidget.h"

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
	for( index = 0; index < count; ++index ) {
		QLabel *label = new QLabel( this );
		allRenderNodeInfo.emplace_back( saveNodeItemInfoArrayPtr[ index ], label );
	}
	updateLayout( );
}
void StartNodeInfoWidget::clearRenderNodeInfo( ) {
	size_t count = allRenderNodeInfo.size( );
	if( count == 0 )
		return;
	auto data = allRenderNodeInfo.data( );
	for( size_t index = 0; index < count; ++index )
		delete data[ index ].second;
	allRenderNodeInfo.clear( );
}
void StartNodeInfoWidget::updateLayout( ) {
	int currentWidgetWidth = this->width( );
	updateBtn->setFixedWidth( currentWidgetWidth );
	int miniHeight = updateBtn->height( );
	size_t count = allRenderNodeInfo.size( );
	if( count == 0 ) {
		if( this->height( ) != miniHeight )
			setMinimumHeight( miniHeight );
		return;
	}
	auto data = allRenderNodeInfo.data( );
	for( size_t index = 0; index < count; ++index ) {
		data[ index ].second->move( 0, miniHeight );
		miniHeight += data[ index ].second->height( );
		data[ index ].second->setText( data[ index ].first->getNodeItem( )->getMetaObjectPathName( ) );
	}

	if( this->height( ) != miniHeight )
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
	allRenderNodeInfo.clear( );
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

void StartNodeInfoWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
}
void StartNodeInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );

	if( allRenderNodeInfo.size( ) == 0 )
		fillLinkNodeInfoListWidget( );
}
