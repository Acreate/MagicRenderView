#include "./nodeDefineVarWidget.h"

#include <QMenuBar>
#include <QTreeWidget.h>
#include <qboxlayout.h>
NodeDefineVarWidget::NodeDefineVarWidget( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f ) {
	defindeTree = new QTreeWidget( this );

	defindeTree->setColumnCount( 2 );
	defindeTree->setHeaderLabels( { "名称", "值" } );
	mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( defindeTree );

	menuBar = new QMenuBar( this );
	menuBar->setStyleSheet( "QMenuBar {background-color:rgba(0,0,0,0);}" );
	mainLayout->setMenuBar( menuBar );
	auto addItemMenu = menuBar->addMenu( "添加" );
	auto addVarAction = addItemMenu->addAction( "变量..." );
	auto addRenderAction = addItemMenu->addAction( "渲染..." );

	defindeTree->clear( );
	auto topItem = new QTreeWidgetItem( defindeTree );
	topItem->setText( 0, "标准" );
	topItem->setText( 1, "软件常规自动生成列表" );
}
