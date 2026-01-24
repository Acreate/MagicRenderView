#ifndef UINT8DECVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8DECVALIDATORWIDGET_H_H_HEAD__FILE__


#include "../validatorWidget.h"

class UInt8DecValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
public:
	UInt8DecValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( const QString &result_text ) override;
public:
	~UInt8DecValidatorWidget( ) override;
};

#endif // UINT8DECVALIDATORWIDGET_H_H_HEAD__FILE__
