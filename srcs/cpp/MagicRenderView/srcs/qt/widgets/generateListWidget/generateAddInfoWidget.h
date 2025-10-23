#ifndef GENERATEADDINFOWIDGET_H_H_HEAD__FILE__
#define GENERATEADDINFOWIDGET_H_H_HEAD__FILE__
#pragma once
#include "GenerateListItemWidget.h"

class QHBoxLayout;
class GenerateAddInfoWidget : public QWidget {
	Q_OBJECT;
protected:
	QHBoxLayout* mainLayout;
public:
	GenerateAddInfoWidget( QWidget *parent = nullptr );
};

#endif // GENERATEADDINFOWIDGET_H_H_HEAD__FILE__
