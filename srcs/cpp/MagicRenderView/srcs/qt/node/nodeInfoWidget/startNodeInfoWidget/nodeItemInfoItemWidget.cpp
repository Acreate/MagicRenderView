#include "nodeItemInfoItemWidget.h"

#include <QLabel>
#include <QPainter>
#include <qboxlayout.h>

#include "../../director/nodeItemInfo.h"

#include "../../item/nodeItem.h"

NodeItemInfoItemWidget::NodeItemInfoItemWidget( NodeItemInfo *node_item_item_info, QWidget *parent, const Qt::WindowFlags &f ) : QLabel( parent, f ), nodeItemInfo( node_item_item_info ) {

}
void NodeItemInfoItemWidget::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
	emit clickNodeItemWidget( this, nodeItemInfo );
}
void NodeItemInfoItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::blue );
}
