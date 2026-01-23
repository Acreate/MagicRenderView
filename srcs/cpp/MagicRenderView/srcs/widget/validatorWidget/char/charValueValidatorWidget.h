#ifndef CHARVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
#define CHARVALUEVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class CharValueValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( const QString &result_text ) override;
public:
	~CharValueValidatorWidget( ) override;
protected:
	void currentEditing_Slot( const QString &txt ) override;
public:
	bool decStringToValidatorString( const QString &normal_dec_text, QString &result_normal_validator_var_txt ) override;
protected:
	void editingFinished_Slot( ) override;
	bool eventFilter( QObject *watched, QEvent *event ) override;
public:
	bool getDecValue( QString &result_normal_dec_text ) override;
	bool isValidatorWidgetFocus( ) const override;
	bool setDecValue( const QString &normal_dec_text ) override;
	bool validatorStringToDecString( const QString &normal_validator_var_txt, QString &result_normal_dec_text ) override;
	CharValueValidatorWidget( const QString &title, const QChar &dec_value, QWidget *parent );
};
#endif // CHARVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
