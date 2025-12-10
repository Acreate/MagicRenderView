#ifndef GENERATEITEMWIDGET_H_H_HEAD__FILE__
#define GENERATEITEMWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>
class QPushButton;
class QLabel;
class GenerateItemWidget : public QWidget {
	Q_OBJECT;
public:
	QLabel *showInfo;
	QPushButton *removeButton;
	QString infoFormmattion;
	QString index;
	QString varValue;
protected:
	virtual void updateInfoString( );
public:
	GenerateItemWidget( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	virtual void setInfo( const size_t &index, const QString &var_value );
Q_SIGNALS:
	void clickRemoveItemBtn( GenerateItemWidget *signal_ptr, const QString &index, const QString &var_value );
};

#endif // GENERATEITEMWIDGET_H_H_HEAD__FILE__
