#ifndef UINT8OCTVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT8OCTVALIDATORWIDGET_H_H_HEAD__FILE__


#include "../validatorWidget.h"

class UInt8OctValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( const QString &result_text ) override;
public:
	UInt8OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // UINT8OCTVALIDATORWIDGET_H_H_HEAD__FILE__
