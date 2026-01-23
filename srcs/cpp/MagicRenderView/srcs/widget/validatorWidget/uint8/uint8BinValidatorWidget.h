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
	bool setValidatorWidgetText( const QString &result_text ) override;
};

#endif // UINT8BINVALIDATORWIDGET_H_H_HEAD__FILE__
