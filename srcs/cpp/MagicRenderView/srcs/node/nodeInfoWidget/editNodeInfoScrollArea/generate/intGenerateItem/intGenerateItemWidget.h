#ifndef INTGENERATEITEMWIDGET_H_H_HEAD__FILE__
#define INTGENERATEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QPushButton;
class QLabel;
class IntGenerateItemWidget : public QWidget {
	Q_OBJECT;
protected:
	QLabel *showInfo;
	QPushButton *removeButton;
	QString infoFormmattion;
	QString index;
	QString varValue;
protected:
	virtual void updateInfoString( );
public:
	IntGenerateItemWidget( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setindex( const size_t &index );
	virtual void setVarValue( const QString &var_value );
	virtual void setInfo(const size_t & index, const QString &var_value );
Q_SIGNALS:
	void clickRemoveItemBtn( IntGenerateItemWidget *signal_ptr, const QString &index, const QString &var_value );
};

#endif // INTGENERATEITEMWIDGET_H_H_HEAD__FILE__
