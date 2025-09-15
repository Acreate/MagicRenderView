#include "./protOutputItemWidget.h"

#include <QPainter>

#include "../varType/varType.h"

void ProtOutputItemWidget::bindVar( VarType *bind_var ) {
	auto old = var;
	var = bind_var;
	if( old )
		old->disconnect( this );
	if( bind_var )
		connect( var, &VarType::deleteObjBefore, this, &ProtOutputItemWidget::releaseVarType );
	emit replaceVar( old, var );
}
ProtOutputItemWidget::ProtOutputItemWidget( QWidget *parent, VarType *bind_var ) : QWidget( parent ), var( bind_var ) {
	if( var )
		connect( var, &VarType::deleteObjBefore, this, &ProtOutputItemWidget::releaseVarType );
}
void ProtOutputItemWidget::releaseVarType( VarType *release_var_type ) {
	if( release_var_type == var )
		bindVar( nullptr );
}
void ProtOutputItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), QColorConstants::DarkRed );
}
