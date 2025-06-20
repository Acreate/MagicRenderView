#ifndef ERRORMSGWIDGET_H_H_HEAD__FILE__
#define ERRORMSGWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

#include "../IInfoWidget.h"
class QLineEdit;
class QLabel;

class ErrorMsgWidget : public IInfoWidget {
	Q_OBJECT;
protected:
	QLabel *title;
public:
	ErrorMsgWidget( QWidget *parent, const QString &error_msg );
};

#endif // ERRORMSGWIDGET_H_H_HEAD__FILE__
