#include "nodeItemInfoWidget.h"

#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <qboxlayout.h>

#include "../application/application.h"

#include "../node/item/nodeItem.h"

#include "../tools/tools.h"

#include "varEditorWidgets/varEditorWidget.h"
NodeItemInfoWidget::NodeItemInfoWidget( NodeItem *node_item, QWidget *parent ) : QWidget( parent ) {
	setNodeItemTarget( node_item );
	updateOver = false;

	/// @brief 标题的布局
	QHBoxLayout *titleLayout;
	/// @brief 更新点击
	QPushButton *updateIco;
	/// @brief 节点标题
	QLabel *nodeTitleName;

	titileWidget = new QWidget( this );
	titleLayout = new QHBoxLayout( titileWidget );
	titleLayout->addSpacerItem( new QSpacerItem( 20, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored ) );
	nodeTitleName = new QLabel( nodeItemTarget->getMetaObjectPathName( ), this );
	titleLayout->addWidget( nodeTitleName );
	updateIco = new QPushButton( this );
	updateIco->setIcon( QIcon( ":/ico/updateIco.png" ) );

	titleLayout->addWidget( updateIco );
	titleLayout->addSpacerItem( new QSpacerItem( 20, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored ) );

	mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( titileWidget );
	mainLayout->addSpacerItem( new QSpacerItem( 0, 20, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding ) );

}
void NodeItemInfoWidget::setNodeItemTarget( NodeItem *node_item_target ) {
	nodeItemTarget = node_item_target;
}
bool NodeItemInfoWidget::updateNodeItemInfo( ) {
	if( updateOver )
		return true;
	size_t count = itemInfos.size( );
	size_t index;
	VarEditorWidget **data;
	if( count > 0 ) {
		data = itemInfos.data( );
		index = 0;
		for( ; index < count; ++index )
			delete data[ index ];
		itemInfos.clear( );
	}

	auto &nodeVarVector = nodeItemTarget->nodeVarVector;
	count = nodeVarVector.size( );
	if( count != 0 ) {
		itemInfos.resize( count );
		data = itemInfos.data( );
		auto varData = nodeVarVector.data( );
		index = 0;
		for( ; index < count; ++index ) {
			data[ index ] = new VarEditorWidget( this, varData[ index ] );
			data[ index ]->updateEditorContent( );
		}
	}

	updateOver = true;
	return updateOver;
}
void NodeItemInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	if( updateNodeItemInfo( ) == false )
		tools::debug::printError( QString( "更新信息异常，请检查节点对象 %1" ).arg( nodeItemTarget->getMetaObjectPathName( ) ) );
}
