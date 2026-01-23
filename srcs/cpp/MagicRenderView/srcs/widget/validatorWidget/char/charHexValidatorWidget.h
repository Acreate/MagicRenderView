#ifndef CHARHEXVALIDATORWIDGET_H_H_HEAD__FILE__
#define CHARHEXVALIDATORWIDGET_H_H_HEAD__FILE__

#include "../validatorWidget.h"

class CharHexValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( QString &result_text ) override;
public:
	CharHexValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // CHARHEXVALIDATORWIDGET_H_H_HEAD__FILE__
