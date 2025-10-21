#include "startNodeInfoWidget.h"

#include <QFileDialog>
#include <QPushButton>
#include <qboxlayout.h>

#include <qt/application/application.h>

#include <qt/node/director/nodeDirector.h>

#include "../../director/nodeItemInfo.h"
void StartNodeInfoWidget::run( ) {
}
void StartNodeInfoWidget::builder( ) {
	if( currentNodeItemInfo == nullptr )
		if( nodeDirector->getNodeItemInfo( nodeItem, currentNodeItemInfo ) == false ) {
			runBtn->setEnabled( false );
			return;
		}
	runList.clear( );
	runList.emplace_back( std_vector { currentNodeItemInfo } );
	if( fillLinkNodeInfo( currentNodeItemInfo ) == false ) {
		runBtn->setEnabled( false );
		tools::debug::printError( QString( "%1(%2) 节点未被正确引用" ).arg( errorNodeItemInfo->nodeItem->getMetaObjectPathName( ) ).arg( errorNodeItemInfo->nodeItem->getGenerateCode( ) ) );
		return;
	}
	runBtn->setEnabled( true );
}
bool StartNodeInfoWidget::fillLinkNodeInfo( const NodeItemInfo *node_item ) {

	size_t forCount = node_item->outputNodeItemVector.size( );
	auto forArrayPtr = node_item->outputNodeItemVector.data( );
	size_t forIndex = 0;
	std_vector< NodeItemInfo * > runAppendVector;
	for( ; forIndex < forCount; ++forIndex )
		if( forArrayPtr[ forIndex ] != nullptr )
			runAppendVector.emplace_back( forArrayPtr[ forIndex ] );

	runList.emplace_back( runAppendVector );
	forCount = runAppendVector.size( );
	auto appendArrayPtr = runAppendVector.data( );
	forIndex = 0;
	for( ; forIndex < forCount; ++forIndex )
		if( fillLinkNodeInfo( appendArrayPtr[ forIndex ] ) == false )
			return false;

	forCount = node_item->inputNodeItemInfoVector.size( );
	forArrayPtr = node_item->inputNodeItemInfoVector.data( );
	forIndex = 0;
	for( ; forIndex < forCount; ++forIndex )
		if( forArrayPtr[ forIndex ] != nullptr && inputNodeItemLegitimate( forArrayPtr[ forIndex ] ) == false )
			return false;
	return true;
}
void StartNodeInfoWidget::removeNodeInfo( const NodeItemInfo *node_item ) {
	if( currentNodeItemInfo == nullptr )
		return;
	auto runListArrayCount = runList.size( );
	if( runListArrayCount == 0 ) {
		currentNodeItemInfo = nullptr;
		runBtn->setEnabled( false );
		return;
	}
	auto runListArrayPtr = runList.data( );
	size_t runListArrayIndex = 0;
	for( ; runListArrayIndex < runListArrayCount; ++runListArrayIndex ) {
		auto &subRunList = runListArrayPtr[ runListArrayIndex ];
		auto subRunListArrayCount = subRunList.size( );
		auto subRunListArrayPtr = subRunList.data( );
		size_t subRunListArrayIndex = 0;
		for( ; subRunListArrayIndex < subRunListArrayCount; ++subRunListArrayIndex )
			if( subRunListArrayPtr[ subRunListArrayIndex ] == node_item ) {
				currentNodeItemInfo = nullptr;
				runList.clear( );
				runBtn->setEnabled( false );
				return;
			}
	}
}
void StartNodeInfoWidget::updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info ) {
	if( currentNodeItemInfo == nullptr ) {
		runBtn->setEnabled( false );
		return;
	}
	if( hasNodeInfo( node_item_info->nodeItem ) )
		runBtn->setEnabled( false );
}

bool StartNodeInfoWidget::hasNodeInfo( const NodeItem *node_item ) {
	for( auto &subNodeItemInfoVector : runList )
		for( auto &nodeItemInfo : subNodeItemInfoVector )
			if( nodeItemInfo->nodeItem == nodeItem )
				return true;
	return false;
}
bool StartNodeInfoWidget::inputNodeItemLegitimate( const NodeItemInfo *input_node_item ) {
	errorNodeItemInfo = nullptr;
	std_vector< NodeItemInfo * > inAppendVector;
	auto forCount = input_node_item->inputNodeItemInfoVector.size( );
	if( forCount == 0 )
		if( input_node_item->nodeItem->getNodeMetaType( ) != nodeItemEnum::Node_Item_Type::Begin ) {
			errorNodeItemInfo = input_node_item;
			return false;
		} else
			return true;

	auto forArrayPtr = input_node_item->inputNodeItemInfoVector.data( );
	auto forIndex = 0;
	for( ; forIndex < forCount; ++forIndex )
		if( forArrayPtr[ forIndex ] != nullptr )
			if( hasNodeInfo( forArrayPtr[ forIndex ]->nodeItem ) == false ) {
				errorNodeItemInfo = forArrayPtr[ forIndex ];
				return false; // 找不到已运行
			} else
				inAppendVector.emplace_back( forArrayPtr[ forIndex ] );
	forCount = inAppendVector.size( );
	forArrayPtr = inAppendVector.data( );
	forIndex = 0;
	for( ; forIndex < forCount; ++forIndex )
		if( inputNodeItemLegitimate( forArrayPtr[ forIndex ] ) == false )
			return false;
	return true;
}
StartNodeInfoWidget::StartNodeInfoWidget( NodeItem *node_item ) : nodeItem( node_item ) {
	toolBtnVector = new QWidget( this );
	currentNodeItemInfo = nullptr;
	QHBoxLayout *qhBoxLayout = new QHBoxLayout( toolBtnVector );

	runBtn = new QPushButton( toolBtnVector );
	runBtn->setText( "运行" );
	connect( runBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::run );
	runBtn->setEnabled( false );
	qhBoxLayout->addWidget( runBtn );

	builderBtn = new QPushButton( toolBtnVector );
	builderBtn->setText( "编译" );
	connect( builderBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::builder );
	qhBoxLayout->addWidget( builderBtn );

	application = Application::getApplicationInstancePtr( );
	nodeDirector = application->getNodeDirector( );
	varGenerate = application->getVarGenerate( );

	connect( nodeDirector, &NodeDirector::nodeItemInfoRefChangeInputNodeItem, this, &StartNodeInfoWidget::updateNodeItemInfoBuilderVector );
	connect( nodeDirector, &NodeDirector::releaseNodeItemInfoSignal, this, &StartNodeInfoWidget::removeNodeInfo );
}
void StartNodeInfoWidget::toolWidgetMoveToMid( ) {
	int toolWidgetWidth = toolBtnVector->width( );
	int width = this->width( );
	int mid = width - toolWidgetWidth;
	mid /= 2;
	toolBtnVector->move( mid, 0 );
}
void StartNodeInfoWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	toolWidgetMoveToMid( );
}
void StartNodeInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	toolWidgetMoveToMid( );
}
