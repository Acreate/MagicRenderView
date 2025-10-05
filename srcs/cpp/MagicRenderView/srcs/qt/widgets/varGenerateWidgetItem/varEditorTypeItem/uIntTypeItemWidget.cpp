#include "uIntTypeItemWidget.h"

#include <QLabel.h>
#include <qboxlayout.h>
imp_vareditor_item_first( UIntTypeItemWidget, QObject::tr( "VarEditorItemWidget" ), QObject::tr( "UIntTypeItemWidget" ), uint64_t );

UIntTypeItemWidget::UIntTypeItemWidget( QWidget *parent ) : VarEditorItemWidget( parent ) {
	auto mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( new QLabel( getStaticMetaObjectName( ), this ) );
	auto itemWidget = new QWidget( this );
	auto itemLayout = new QHBoxLayout( itemWidget );
	itemLayout->addWidget( new QLabel( "名称", this ) );
	itemLayout->addWidget( new QLabel( "值", this ) );
	mainLayout->addWidget( itemWidget );
}
