#ifndef NUMBERVARLINEEDIT_H_H_HEAD__FILE__
#define NUMBERVARLINEEDIT_H_H_HEAD__FILE__

#include <QLineEdit>
class NumberVarLineEdit : public QLineEdit {
	Q_OBJECT;
protected Q_SLOTS:
	virtual void changedText_Slot( const QString &text );
public:
	NumberVarLineEdit( uint64_t value, QWidget *parent );
Q_SIGNALS:
	void text_changed_signal( NumberVarLineEdit *sender_obj, const QString &text );
};

#endif // NUMBERVARLINEEDIT_H_H_HEAD__FILE__
