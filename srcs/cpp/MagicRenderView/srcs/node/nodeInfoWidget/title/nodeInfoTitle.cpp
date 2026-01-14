#include "nodeInfoTitle.h"

#include <QVBoxLayout>
#include <QLabel>
NodeInfoTitle::NodeInfoTitle( QWidget *parent ) : QWidget( parent ) {
	auto mainLayout = new QVBoxLayout( this );
	title = new QLabel( this );
	mainLayout->addWidget( title, 0, Qt::AlignCenter );
}
void NodeInfoTitle::setTitleText( const QString &new_title_text ) {
	title->setText( new_title_text );
}
QString NodeInfoTitle::getTitleText( ) const {
	return title->text( );
}
