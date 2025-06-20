#include "./IInfoWidget.h"

#include <QLabel>
#include <QVBoxLayout>
IInfoWidget::IInfoWidget( QWidget *parent, const QString &title_msg ) {
	mainLayout = new QVBoxLayout( this );
	title = new QLabel( this );
	mainLayout->addWidget( title );
}
QString IInfoWidget::getTitle( ) const {
	return title->text( );
}
