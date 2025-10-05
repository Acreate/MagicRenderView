#include "intTypeItemWidget.h"
imp_vareditor_item_first( IntTypeItemWidget, QObject::tr( "VarEditorItemWidget" ), QObject::tr( "IntTypeItemWidget" ), int64_t );

IntTypeItemWidget::IntTypeItemWidget( QWidget *parent )
	: VarEditorItemWidget( parent ) {
}
