#ifndef NUMBERVARTITLELINEEDIT_H_H_HEAD__FILE__
#define NUMBERVARTITLELINEEDIT_H_H_HEAD__FILE__

#include <QWidget>

class QVBoxLayout;
class NumberVarLineEdit;
class QLabel;
class NumberVarTitleLineEdit : public QWidget {
	Q_OBJECT;
protected:
	QLabel *titile;
	NumberVarLineEdit *numberVarLineEdit;
	QVBoxLayout *mainLayout;
protected Q_SLOTS:
	void textChanged_Slots( NumberVarLineEdit *sender_obj, const QString &text );
public:
	NumberVarTitleLineEdit( const QString &titile_text, uint64_t max_var, QWidget *parent );
	virtual NumberVarLineEdit * getNumberVarLineEdit( ) const { return numberVarLineEdit; }
	virtual void setNumberVarLineEdit( NumberVarLineEdit *number_var_line_edit );
	virtual void setTitleText( const QString &new_title_text );
	virtual QString getTitleText( );
	virtual void setVarToLineEdit( const uint64_t &var );
	virtual void setVarToLineEdit( const int64_t &var );
	virtual QString getNumberValue( ) const;
	bool toInt64( const QString &conver_text, int64_t &result_value ) const;
	bool toUInt64( const QString &conver_text, uint64_t &result_value ) const;
Q_SIGNALS:
	void text_changed_signal( NumberVarTitleLineEdit *sender_obj, NumberVarLineEdit *edite_event, const QString &text );
};

#endif // NUMBERVARTITLELINEEDIT_H_H_HEAD__FILE__
