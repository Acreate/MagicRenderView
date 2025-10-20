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
	runBtn->setEnabled( false );
	if( nodeItemInfo == nullptr ) {
		builderVector.clear( );
		if( nodeDirector->getNodeItemInfo( nodeItem, nodeItemInfo ) == false ) {
			runBtn->setEnabled( false );
			tools::debug::printError( "无法匹配正确的 NodeItemInfo 类型实例对象" );
			return;
		}
	}

	auto nodeItemInfos = nodeItemInfo->getOutputNodeItemVector( );
	size_t count = nodeItemInfos.size( );
	size_t index = 0;
	auto itemInfoArrayPtr = nodeItemInfos.data( );
	runOverVector.resize( count ); // 模拟运行
	auto runvoerVectorPtr = runOverVector.data( );

	size_t checkIndex;
	size_t checkMaxCount;
	size_t inputRefCount;
	size_t inputRefIndex;
	size_t buffCount;
	size_t buffIndex;
	NodeItemInfo *const*buffArrayPtr;
	size_t startOffsetIndex;

	NodeItemInfo *const*inputRefArrayPtr;
	for( ; index < count; ++index ) {

		auto &inputNodeItemVector = itemInfoArrayPtr[ index ]->getInputNodeItemVector( );

		inputRefCount = inputNodeItemVector.size( );
		inputRefArrayPtr = inputNodeItemVector.data( );
		inputRefIndex = 0;
		for( ; inputRefIndex < inputRefCount; ++inputRefIndex )
			if( inputRefArrayPtr[ inputRefIndex ] != nullptr && inputRefArrayPtr[ inputRefIndex ] != nodeItemInfo ) {
				for( checkIndex = 0; checkIndex < index; ++checkIndex )
					if( inputRefArrayPtr[ inputRefIndex ] != nullptr && runvoerVectorPtr[ checkIndex ] == inputRefArrayPtr[ inputRefIndex ] )
						break;
				if( checkIndex == index ) {
					tools::debug::printError( QString( "%1 不存在运行列表当中" ).arg( inputRefArrayPtr[ inputRefIndex ]->getNodeItem( )->getMetaObjectPathName( ) ) );
					return; // 没有发现运行单元中存在已运行节点
				}
			}

		runvoerVectorPtr[ index ] = itemInfoArrayPtr[ index ];
	}

	// 递归缓存
	std_vector< NodeItemInfo * > overSubBuff;
	size_t overSubBuffCount = 0;
	size_t overSubBuffOffsetIndex;
	NodeItemInfo **overSubBuffPtr;
	// 递归运行
	do {
		for( ; index < count; ++index ) {
			auto &buff = itemInfoArrayPtr[ index ]->getOutputNodeItemVector( );

			buffCount = buff.size( );
			buffIndex = 0;
			buffArrayPtr = buff.data( );
			startOffsetIndex = runOverVector.size( );
			runOverVector.resize( startOffsetIndex + buffCount );
			runvoerVectorPtr = runOverVector.data( );
			overSubBuffOffsetIndex = overSubBuff.size( );

			overSubBuffCount = buffCount + overSubBuffOffsetIndex;
			overSubBuff.resize( overSubBuffCount );
			overSubBuffPtr = overSubBuff.data( );
			for( ; buffIndex < buffCount; ++buffIndex ) {
				// todo : 检查引用的问题

				auto &inputNodeItemVector = buffArrayPtr[ buffIndex ]->getInputNodeItemVector( );

				inputRefCount = inputNodeItemVector.size( );
				inputRefArrayPtr = inputNodeItemVector.data( );
				inputRefIndex = 0;
				for( ; inputRefIndex < inputRefCount; ++inputRefIndex )
					if( inputRefArrayPtr[ inputRefIndex ] != nodeItemInfo ) {
						for( checkIndex = 0, checkMaxCount = buffIndex + startOffsetIndex; checkIndex < checkMaxCount; ++checkIndex )
							if( runvoerVectorPtr[ checkIndex ] == inputRefArrayPtr[ inputRefIndex ] )
								break;
						if( checkIndex == checkMaxCount ) {
							tools::debug::printError( QString( "%1 不存在运行列表当中" ).arg( inputRefArrayPtr[ inputRefIndex ]->getNodeItem( )->getMetaObjectPathName( ) ) );
							return; // 没有发现运行单元中存在已运行节点
						}
					}
				overSubBuffPtr[ buffIndex + overSubBuffOffsetIndex ] = runvoerVectorPtr[ buffIndex + startOffsetIndex ] = buffArrayPtr[ buffIndex ];
			}
		}
		if( overSubBuffCount == 0 )
			break;
		count = overSubBuffCount;
		nodeItemInfos = overSubBuff;
		index = 0;
		itemInfoArrayPtr = nodeItemInfos.data( );
		overSubBuff.clear( );
	} while( true );
	runBtn->setEnabled( true );
}
void StartNodeInfoWidget::updateNodeItemInfoBuilderVector( NodeItemInfo *node_item_info ) {

	if( nodeItemInfo == nullptr ) {
		builderVector.clear( );
		if( nodeDirector->getNodeItemInfo( nodeItem, nodeItemInfo ) == false ) {
			runBtn->setEnabled( false );
			return;
		}
	}
	if( node_item_info == nodeItemInfo ) {
		runBtn->setEnabled( false );
		return;
	}
	size_t count = builderVector.size( );
	if( count == 0 ) {
		runBtn->setEnabled( false );
		return;
	}
	auto data = builderVector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( data[ index ] == node_item_info )
			break;

	if( index == count )
		return; // 没有改变编译的输出依赖
	runBtn->setEnabled( false );
}
StartNodeInfoWidget::StartNodeInfoWidget( NodeItem *node_item ) : nodeItem( node_item ) {
	toolBtnVector = new QWidget( this );
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
	nodeItemInfo = nullptr;
	connect( nodeDirector, &NodeDirector::nodeItemInfoRefChangeInputNodeItem, this, &StartNodeInfoWidget::updateNodeItemInfoBuilderVector );
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
