#ifndef UINT16HEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT16HEXVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class UInt16HexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( const QString &result_text ) override;
public:
	UInt16HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // UINT16HEXVALIDATORWIDGET_H_H_HEAD__FILE__
