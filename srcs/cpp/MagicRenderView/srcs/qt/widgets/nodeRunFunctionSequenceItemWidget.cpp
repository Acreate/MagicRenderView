#include "./nodeRunFunctionSequenceItemWidget.h"

#include <QLabel>
#include <QPainter>
#include <qboxlayout.h>

#include <qt/functionDeclaration/IFunctionDeclaration.h>
#include <qt/widgets/nodeRunSequenceWidget.h>

#include "nodeControlItemWidge.h"
/// @brief 双击时钟
std::chrono::system_clock::time_point NodeRunFunctionSequenceItemWidget::doubleClickClock = std::chrono::system_clock::now( );
/// @brief 双击对象
NodeRunFunctionSequenceItemWidget *NodeRunFunctionSequenceItemWidget::doubleClickObj = nullptr;
NodeRunFunctionSequenceItemWidget::NodeRunFunctionSequenceItemWidget( NodeRunSequenceWidget *node_run_sequence_widget, const std::shared_ptr< IFunctionDeclaration > &function_declaration ) : QWidget( node_run_sequence_widget ), itemParent( node_run_sequence_widget ) {
	IFunctionDeclaration *functionDeclaration = function_declaration.get( );
	if( functionDeclaration->isIsControlCode( ) == false )
		itemChild = nullptr;
	else
		itemChild = new NodeControlItemWidge( node_run_sequence_widget );

	auto oldLayout = layout( );
	if( oldLayout )
		delete oldLayout;
	auto mainLayout = new QVBoxLayout( this );
	auto title = new QLabel( this );
	mainLayout->addWidget( title, 0, Qt::AlignTop | Qt::AlignHCenter );
	title->setAlignment( Qt::AlignCenter );
	title->setText( functionDeclaration->getDeclarationName( ) );
	itemActive = true;
}
NodeRunFunctionSequenceItemWidget::~NodeRunFunctionSequenceItemWidget( ) {
	itemParent->removeItem( this );
	disconnect( );
}
void NodeRunFunctionSequenceItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	auto pen = painter.pen( );
	int penWidth = 4;
	pen.setWidth( penWidth );
	penWidth *= 2;
	pen.setColor( Qt::GlobalColor::darkGray );
	painter.setPen( pen );
	painter.drawRect( 0, 0, width( ) - penWidth, height( ) - penWidth );
}
void NodeRunFunctionSequenceItemWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	auto timePoint = std::chrono::system_clock::now( );
	if( doubleClickObj == this ) {
		auto duration = timePoint - doubleClickClock;
		auto durationCast = std::chrono::duration_cast< std::chrono::milliseconds >( duration );
		int count = durationCast.count( );
		if( count < 500 ) {
			emit doubleClick( );
			doubleClickObj = nullptr;
			doubleClickClock = timePoint;
			return;
		}
	}
	doubleClickObj = this;
	doubleClickClock = timePoint;
}
