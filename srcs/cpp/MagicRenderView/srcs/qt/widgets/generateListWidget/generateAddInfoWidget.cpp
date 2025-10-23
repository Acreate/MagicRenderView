#include "generateAddInfoWidget.h"

#include <qboxlayout.h>
#include <QLineEdit>
#include <QPushButton>
GenerateAddInfoWidget::GenerateAddInfoWidget( QWidget *parent ) : QWidget( parent ) {
	mainLayout = new QHBoxLayout( this );
	QLineEdit *textLine = new QLineEdit( this );
	mainLayout->addWidget( textLine, 8, Qt::AlignLeading );
	QPushButton *addClick = new QPushButton( tr( "加入" ), this );
	mainLayout->addWidget( addClick, 2, Qt::AlignRight );
}
