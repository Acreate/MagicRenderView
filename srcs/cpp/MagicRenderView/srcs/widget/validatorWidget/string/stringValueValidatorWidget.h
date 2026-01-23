#ifndef STRINGVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#define STRINGVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#include "../validatorWidget.h"

class QTextEdit;
class StringValueValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel* title;
	QTextEdit* textEditPtr;
	QString decTxt;
protected Q_SLOTS:
	void textChanged_Slot();
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( const QString &result_text ) override;
public:
	StringValueValidatorWidget( const QString &title, const QString &default_text_value, QWidget *parent );
	StringValueValidatorWidget( const QString &title, const QString &default_text_value, QWidget *parent , bool is_enable_editoring_signal);

	bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) override;
	bool getDecValue( QString &result_normal_dec_text ) override;
	bool setDecValue( const QString &normal_dec_text ) override;
	bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) override;
protected:
	
	bool eventFilter( QObject *watched, QEvent *event ) override;
};
#endif // STRINGVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
