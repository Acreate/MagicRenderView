#include "bottomNodeInfoTool.h"

#include <QHBoxLayout>
#include <qpushbutton.h>
BottomNodeInfoTool::BottomNodeInfoTool( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	auto mainLayout = new QHBoxLayout( this );
	okPushButton = new QPushButton( tr( "确认" ), this );
	cancelPushButton = new QPushButton( tr( "取消" ), this );
	connect( okPushButton, &QPushButton::clicked, this, &BottomNodeInfoTool::ok_signal );
	connect( cancelPushButton, &QPushButton::clicked, this, &BottomNodeInfoTool::cancel_signal );
	mainLayout->addWidget( okPushButton, 0, Qt::AlignCenter );
	mainLayout->addWidget( cancelPushButton, 0, Qt::AlignCenter );
}
