#ifndef INT64HEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define INT64HEXVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class Int64HexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( QString &result_text ) override;
public:
	Int64HexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};

#endif // INT64HEXVALIDATORWIDGET_H_H_HEAD__FILE__
