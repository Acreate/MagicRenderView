#include "nodeItemInfoWidget.h"

#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <qboxlayout.h>
#include <qmenu.h>

#include <qt/widgets/varEditorWidgets/varEditorWidget.h>

#include <qt/node/item/nodeItem.h>

void NodeItemInfoWidget::connectItem( VarEditorWidget *new_var_edit_item ) {
	connect( new_var_edit_item, &VarEditorWidget::destroyed, [this] ( QObject *ptr ) {

		auto data = itemInfos.data( );
		auto count = itemInfos.size( );
		size_t index = 0;
		for( ; index < count; ++index )
			if( data[ index ] == ptr ) {
				delete data[ index ];
				itemInfos.erase( itemInfos.begin( ) + index );
			}
	} );
}
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

	QWidget *addItemWidget = new QWidget( this );
	auto addItemLayout = new QHBoxLayout( addItemWidget );
	auto addTitle = new QLabel( tr( "添加" ), addItemWidget );
	auto addBtn = new QPushButton( addItemWidget );
	addBtn->setIcon( QIcon( ":/ico/item_add.png" ) );
	addItemLayout->addSpacerItem( new QSpacerItem( 20, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored ) );
	addItemLayout->addWidget( addTitle );
	addItemLayout->addWidget( addBtn );
	connect( addBtn, &QPushButton::clicked, [this]( ) {
		createVarItemMenu->move( QCursor::pos( ) );
		createVarItemMenu->show( );
	} );
	addItemLayout->addSpacerItem( new QSpacerItem( 20, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored ) );
	mainLayout->addWidget( addItemWidget );
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
			VarEditorWidget *varEditorWidget = new VarEditorWidget( this, varData[ index ] );
			data[ index ] = varEditorWidget;
			varEditorWidget->updateEditorContent( );
			mainLayout->insertWidget( mainLayout->count( ) - 2, varEditorWidget );
			connectItem( varEditorWidget );
		}
	}

	updateOver = true;
	return updateOver;
}
bool NodeItemInfoWidget::insterLast( VarEditorWidget *new_var_edit_item ) {
	mainLayout->insertWidget( mainLayout->count( ) - 2, new_var_edit_item );
	itemInfos.emplace_back( new_var_edit_item );
	connectItem( new_var_edit_item );
	return true;
}
void NodeItemInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	if( updateNodeItemInfo( ) == false )
		tools::debug::printError( QString( "更新信息异常，请检查节点对象 %1" ).arg( nodeItemTarget->getMetaObjectPathName( ) ) );
}
