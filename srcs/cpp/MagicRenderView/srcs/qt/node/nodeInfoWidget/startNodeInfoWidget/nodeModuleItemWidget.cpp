#include "nodeModuleItemWidget.h"

#include <QPainter>
#include <QLabel>
#include <qboxlayout.h>

#include "runNodeModuleItemWidget.h"

#include "../../director/nodeItemInfo.h"

#include "../../item/nodeItem.h"
NodeModuleItemWidget::NodeModuleItemWidget( const std_vector< NodeItemInfo * > &run_node_item_infos, QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ), runNodeItemInfos( run_node_item_infos ) {
	QVBoxLayout *mainLayout = new QVBoxLayout( this );
	size_t count = run_node_item_infos.size( );
	auto data = run_node_item_infos.data( );
	QString labelTitile( "%1 [%2]" );
	for( size_t index = 0; index < count; ++index ) {
		NodeItem *nodeItem = data[ index ]->getNodeItem( );
		auto label = new RunNodeModuleItemWidget( nodeItem, this );
		mainLayout->addWidget( label );
	}
	mainLayout->addSpacerItem( new QSpacerItem( 10, 10, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding ) );
}
void NodeModuleItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	int penWidth = 5;
	auto pen = painter.pen( );
	pen.setColor( Qt::GlobalColor::blue );
	pen.setWidth( penWidth );
	int doublePenWidth = penWidth * 2;
	painter.drawRect( penWidth, penWidth, width( ) - doublePenWidth, height( ) - doublePenWidth );
}
