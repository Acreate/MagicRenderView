#ifndef NUMBERVARLINEEDIT_H_H_HEAD__FILE__
#define NUMBERVARLINEEDIT_H_H_HEAD__FILE__

#include <QLineEdit>
class Validator;
class NumberVarLineEdit : public QLineEdit {
	Q_OBJECT;
protected Q_SLOTS:
	virtual void changedText_Slot( const QString &text );
protected:
	Validator *validator;
public:
	NumberVarLineEdit( QWidget *parent );
	~NumberVarLineEdit( ) override;
	virtual bool toInt64( const QString &conver_text, int64_t &result_value ) const;
	virtual bool toUInt64( const QString &conver_text, uint64_t &result_value ) const;
	virtual void setVarToLineEdit( const uint64_t &var );
	virtual void setVarToLineEdit( const int64_t &var );

	virtual int getBase( ) const;
Q_SIGNALS:
	void text_changed_signal( NumberVarLineEdit *sender_obj, const QString &text );
};

#endif // NUMBERVARLINEEDIT_H_H_HEAD__FILE__
