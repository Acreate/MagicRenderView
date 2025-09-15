#include "./protInputItemWidget.h"

#include <QPainter>

#include "../varType/varType.h"

void ProtInputItemWidget::bindVar( VarType *bind_var ) {
	auto old = var;
	var = bind_var;
	if( old )
		old->disconnect( this );
	if( bind_var )
		connect( var, &VarType::deleteObjBefore, this, &ProtInputItemWidget::releaseVarType );
	emit replaceVar( old, var );
}
ProtInputItemWidget::ProtInputItemWidget( QWidget *parent, VarType *bind_var ) : QWidget( parent ), var( bind_var ) {
	if( var )
		connect( var, &VarType::deleteObjBefore, this, &ProtInputItemWidget::releaseVarType );
}
void ProtInputItemWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), QColorConstants::DarkYellow );
}
void ProtInputItemWidget::releaseVarType( VarType *release_var_type ) {
	if( release_var_type == var )
		bindVar( nullptr );
}
