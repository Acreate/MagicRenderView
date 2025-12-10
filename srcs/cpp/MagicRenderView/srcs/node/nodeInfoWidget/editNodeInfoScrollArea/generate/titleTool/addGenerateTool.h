#ifndef ADDGENERATETOOL_H_H_HEAD__FILE__
#define ADDGENERATETOOL_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QPushButton;
class QLineEdit;
class QComboBox;
class AddGenerateTool : public QWidget {
	Q_OBJECT;
protected:
	QComboBox *insertIndexComboBox;
	QLineEdit *varEditor;
	QPushButton *insertBtn;
public:
	AddGenerateTool( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setMaxIndex(const size_t& index);
Q_SIGNALS:
	void addItem( AddGenerateTool *signal_ptr, const size_t &index, const QString &var_value );
};

#endif // ADDGENERATETOOL_H_H_HEAD__FILE__
