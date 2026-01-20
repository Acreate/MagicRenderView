#ifndef NUMBERVARLINEEDIT_H_H_HEAD__FILE__
#define NUMBERVARLINEEDIT_H_H_HEAD__FILE__

#include <QLineEdit>
class NumberVarLineEdit : public QLineEdit {
	Q_OBJECT;
protected Q_SLOTS:
	virtual void changedText_Slot( const QString &text );
protected:
	int base = 10;
public:
	NumberVarLineEdit( uint64_t value, QWidget *parent );
	virtual bool toInt64( const QString &conver_text, int64_t &result_value ) const =0;
	virtual bool toUInt64( const QString &conver_text, uint64_t &result_value ) const =0;
	virtual void setVarToLineEdit( const uint64_t &var ) ;
	virtual void setVarToLineEdit( const int64_t &var );
	virtual int getBase( ) const { return base; }
Q_SIGNALS:
	void text_changed_signal( NumberVarLineEdit *sender_obj, const QString &text );
};

#endif // NUMBERVARLINEEDIT_H_H_HEAD__FILE__
