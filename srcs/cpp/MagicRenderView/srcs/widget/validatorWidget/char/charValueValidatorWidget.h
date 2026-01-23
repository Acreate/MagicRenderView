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
	bool setValidatorWidgetText( QString &result_text ) override;
public:
	CharValueValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // CHARVALUEVALIDATORWIDGET_H_H_HEAD__FILE__
