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

	for( ; index < count; ++index )
		runvoerVectorPtr[ index ] = itemInfoArrayPtr[ index ];

	// 递归缓存
	std_vector< NodeItemInfo * > overSubBuff;
	// 递归运行
	do {
		for( ; index < count; ++index ) {
			auto &buff = itemInfoArrayPtr[ index ]->getOutputNodeItemVector( );

			size_t buffCount = buff.size( );
			size_t buffIndex = 0;
			auto buffArrayPtr = buff.data( );
			size_t startOffsetIndex = runOverVector.size( );
			runOverVector.resize( startOffsetIndex + buffCount );
			auto runOverVectorPtr = runOverVector.data( );
			overSubBuff.resize( buffCount );
			auto overSubBuffPtr = overSubBuff.data( );
			for( ; buffIndex < buffCount; ++buffIndex ) {
				// todo : 检查引用的问题
				overSubBuffPtr[ buffIndex ] = runOverVectorPtr[ buffIndex + startOffsetIndex ] = buffArrayPtr[ buffIndex ];
			}
		}
		count = overSubBuff.size( );
		if( count == 0 )
			break;
		nodeItemInfos = overSubBuff;
		index = 0;
		itemInfoArrayPtr = nodeItemInfos.data( );
		overSubBuff.clear( );
	} while( true );

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
