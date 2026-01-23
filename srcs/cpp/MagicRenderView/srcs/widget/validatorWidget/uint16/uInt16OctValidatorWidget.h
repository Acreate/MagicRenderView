#ifndef UINT16OCTVALIDATORWIDGET_H_H_HEAD__FILE__
#define UINT16OCTVALIDATORWIDGET_H_H_HEAD__FILE__


#include "../validatorWidget.h"

class UInt16OctValidatorWidget : public ValidatorWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QLineEdit *editorWidget;
protected:
	QObject * getBindEditorObjPtr( ) const override;
	bool getValidatorWidgetText( QString &result_text ) const override;
	bool setValidatorWidgetText( QString &result_text ) override;
public:
	UInt16OctValidatorWidget( const QString &title, const QString &dec_value, QWidget *parent );
};
#endif // UINT16OCTVALIDATORWIDGET_H_H_HEAD__FILE__
