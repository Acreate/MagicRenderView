#include "nodeItemInfoWidget.h"

#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <qboxlayout.h>
#include <qmenu.h>


#include <qt/node/item/nodeItem.h>


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
void NodeItemInfoWidget::showEvent( QShowEvent *event ) {
	QWidget::showEvent( event );
	
}
