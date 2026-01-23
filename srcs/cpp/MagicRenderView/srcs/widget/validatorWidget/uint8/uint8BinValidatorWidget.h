#ifndef UINT8BINVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8BINVALIDATORWIDGET_H_H_HEAD__FILE__
#include "../validatorWidget.h"

class Uint8BinValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel* title;
	QLineEdit* editorWidget;
public:
	Uint8BinValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( QString &result_text ) override;
public:
	~Uint8BinValidatorWidget( ) override;
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
};

#endif // UINT8BINVALIDATORWIDGET_H_H_HEAD__FILE__
