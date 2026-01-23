#ifndef BOOLVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#define BOOLVALUEVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class QComboBox;
class BoolValueValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QComboBox *boolComboBox;
	QString trueText;
	QString falseText;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( QString &result_text ) override;
public:
	BoolValueValidatorWidget( const QString &title, bool bool_value, QWidget *parent );
	virtual bool setBoolValue(bool set_new_bool_var);
	virtual bool getBoolValue( bool &result_get_new_bool_var );
protected:
	bool eventFilter( QObject *watched, QEvent *event ) override;
};
#endif // BOOLVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
