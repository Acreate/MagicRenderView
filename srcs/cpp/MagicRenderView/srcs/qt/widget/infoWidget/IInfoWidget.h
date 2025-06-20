#ifndef IINFOWIDGET_H_H_HEAD__FILE__
#define IINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class QVBoxLayout;
class QLabel;
class IInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	QLabel *title;
	QVBoxLayout* mainLayout;
public:
	IInfoWidget( QWidget *parent, const QString &title_msg );
	virtual QString getTitle( ) const;
};

#endif // IINFOWIDGET_H_H_HEAD__FILE__