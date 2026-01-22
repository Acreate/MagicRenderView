#include "boolValueValidatorWidget.h"

#include <QLineEdit>

BoolValueValidatorWidget::BoolValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent ) : ValidatorWidget( title, dec_value, parent ) {

}
bool BoolValueValidatorWidget::eventFilter( QObject *watched, QEvent *event ) {
	bool eventFilter = ValidatorWidget::eventFilter( watched, event );
	
	return eventFilter;
}
