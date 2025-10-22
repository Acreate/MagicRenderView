#include "startNodeInfoWidget.h"

#include <QFileDialog>
#include <QPushButton>
#include <qboxlayout.h>

#include <qt/application/application.h>
#include <qt/node/director/nodeDirector.h>
#include <qt/node/director/nodeItemInfo.h>

#include "nodeModuleScrollArea.h"
#include "nodeModuleWidget.h"
void StartNodeInfoWidget::run( ) {
	if( nodeModuleWidget->isEnd( ) == true )
		return;
	setRunBtnStatus( false );
	std_vector< NodeItemInfo * > resultList;
	while( nodeModuleWidget->getCurrentRunNodeItemInfoVector( resultList ) ) {
		if( runNodeItemInfoVector( resultList ) == false )
			break;
		if( nodeModuleWidget->next( ) == false )
			break;
	}
	nextBtn->setEnabled( true );
}
bool StartNodeInfoWidget::runNodeItemInfoVector( const std_vector< NodeItemInfo * > &run_node_item_info ) {

	// todo : 执行节点
	
	runHistoryVector.emplace_back( run_node_item_info ); // 执行历史
	return true;
}
void StartNodeInfoWidget::setRunBtnStatus( bool flag ) {
	runBtn->setEnabled( flag );
	nextBtn->setEnabled( flag );
}
void StartNodeInfoWidget::runNext( ) {
	std_vector< NodeItemInfo * > resultList;
	if( nodeModuleWidget->getCurrentRunNodeItemInfoVector( resultList ) == false || runNodeItemInfoVector( resultList ) || nodeModuleWidget->next( ) == false ) {
		setRunBtnStatus( false );
		return;
	}
}
void StartNodeInfoWidget::builder( ) {
	if( currentNodeItemInfo == nullptr )
		if( nodeDirector->getNodeItemInfo( nodeItem, currentNodeItemInfo ) == false ) {
			setRunBtnStatus( false );
			return;
		}
	runList.clear( );
	runList.emplace_back( std_vector { currentNodeItemInfo } );
	if( fillLinkNodeInfo( currentNodeItemInfo ) == false ) {
		setRunBtnStatus( false );
		tools::debug::printError( QString( QObject::tr( "%1(%2) 节点未被正确引用" ) ).arg( errorNodeItemInfo->nodeItem->getMetaObjectPathName( ) ).arg( errorNodeItemInfo->nodeItem->getGenerateCode( ) ) );
		return;
	}
	nodeModuleWidget->setRunList( &runList );
	if( nodeModuleWidget->toBegin( ) == false )
		setRunBtnStatus( false );
	else
		setRunBtnStatus( true );
}
bool StartNodeInfoWidget::fillLinkNodeInfo( const NodeItemInfo *node_item ) {

	size_t forCount = node_item->outputNodeItemVector.size( );
	auto forArrayPtr = node_item->outputNodeItemVector.data( );
	size_t forIndex = 0;
	std_vector< NodeItemInfo * > runAppendVector;
	for( ; forIndex < forCount; ++forIndex )
		if( forArrayPtr[ forIndex ] != nullptr )
			runAppendVector.emplace_back( forArrayPtr[ forIndex ] );
	forCount = runAppendVector.size( );
	if( forCount != 0 ) {
		runList.emplace_back( runAppendVector );
		auto appendArrayPtr = runAppendVector.data( );
		forIndex = 0;
		for( ; forIndex < forCount; ++forIndex )
			if( fillLinkNodeInfo( appendArrayPtr[ forIndex ] ) == false )
				return false;
	}

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
		setRunBtnStatus( false );
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
				setRunBtnStatus( false );
				return;
			}
	}
}
void StartNodeInfoWidget::updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info ) {
	if( currentNodeItemInfo == nullptr ) {
		setRunBtnStatus( false );
		return;
	}
	if( hasNodeInfo( node_item_info->nodeItem ) )
		setRunBtnStatus( false );
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
	if( forCount == 0 )
		return true;
	forArrayPtr = inAppendVector.data( );
	forIndex = 0;
	for( ; forIndex < forCount; ++forIndex )
		if( inputNodeItemLegitimate( forArrayPtr[ forIndex ] ) == false )
			return false;
	return true;
}
StartNodeInfoWidget::StartNodeInfoWidget( NodeItem *node_item ) : nodeItem( node_item ) {
	topBtnWidget = new QWidget( this );
	bottomBtnWidget = new QWidget( this );
	nodeModuleScrollArea = new NodeModuleScrollArea( &runList, this );
	nodeModuleWidget = nodeModuleScrollArea->getNodeModuleWidget( );
	currentNodeItemInfo = nullptr;
	QHBoxLayout *qhBoxLayout = new QHBoxLayout( topBtnWidget );

	runBtn = new QPushButton( topBtnWidget );
	runBtn->setText( QObject::tr( "运行" ) );
	connect( runBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::run );
	qhBoxLayout->addWidget( runBtn );

	builderBtn = new QPushButton( topBtnWidget );
	builderBtn->setText( QObject::tr( "编译" ) );
	connect( builderBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::builder );
	qhBoxLayout->addWidget( builderBtn );

	qhBoxLayout = new QHBoxLayout( bottomBtnWidget );
	nextBtn = new QPushButton( QObject::tr( "下一步" ), bottomBtnWidget );
	qhBoxLayout->addWidget( nextBtn );
	connect( builderBtn, &QPushButton::clicked, this, &StartNodeInfoWidget::runNext );

	application = Application::getApplicationInstancePtr( );
	nodeDirector = application->getNodeDirector( );
	varGenerate = application->getVarGenerate( );

	connect( nodeDirector, &NodeDirector::nodeItemInfoRefChangeInputNodeItem, this, &StartNodeInfoWidget::updateNodeItemInfoBuilderVector );
	connect( nodeDirector, &NodeDirector::releaseNodeItemInfoSignal, this, &StartNodeInfoWidget::removeNodeInfo );

	setRunBtnStatus( false );
}

void StartNodeInfoWidget::updateLayout( ) {
	int currentWidgetWidth = this->width( );
	int currentWidgetHeight = this->height( );

	int topBtnWidgetWidth = topBtnWidget->width( );
	int mid = currentWidgetWidth - topBtnWidgetWidth;
	mid /= 2;
	topBtnWidget->move( mid, 0 );

	int toolWidgetWidth = bottomBtnWidget->width( );
	int bottomHeight = bottomBtnWidget->height( );
	mid = currentWidgetWidth - toolWidgetWidth;
	mid /= 2;
	bottomBtnWidget->move( mid, currentWidgetHeight - bottomHeight );

	nodeModuleScrollArea->move( 0, bottomHeight );
	int topBtnHeight = topBtnWidget->height( );
	nodeModuleScrollArea->setFixedSize( currentWidgetWidth, currentWidgetHeight - topBtnHeight - bottomHeight );
}
void StartNodeInfoWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	updateLayout( );
}
void StartNodeInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	updateLayout( );
}
