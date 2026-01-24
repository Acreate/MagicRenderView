#ifndef UINT8HEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8HEXVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class UInt8HexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( const QString &result_text ) override;
public:
	UInt8HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // UINT8HEXVALIDATORWIDGET_H_H_HEAD__FILE__
