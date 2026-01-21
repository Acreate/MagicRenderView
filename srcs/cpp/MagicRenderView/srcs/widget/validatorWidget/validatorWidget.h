#ifndef VALIDATORWIDGET_H_H_HEAD__FILE__
#define VALIDATORWIDGET_H_H_HEAD__FILE__
#include <QWidget>

class Validator;
class QLabel;
class QLineEdit;
class ValidatorWidget : public QWidget {
	Q_OBJECT;
protected:
	QLineEdit *lineEdit;
	QLabel *titleLabel;
	Validator *validator;
protected:
	virtual void editingFinished_Slot( );
public:
	ValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
	virtual bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt );
	virtual bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text );
	virtual bool setDecValue( const QString &normal_dec_text );
	virtual bool getDecValue( QString &result_normal_dec_text );
Q_SIGNALS:
	void overEditorFinish_Signal( ValidatorWidget *sender_ptr, const QString &dec_txt );
};

#endif // VALIDATORWIDGET_H_H_HEAD__FILE__
