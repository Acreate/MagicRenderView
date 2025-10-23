#ifndef GENERATEBINWIDGET_H_H_HEAD__FILE__
#define GENERATEBINWIDGET_H_H_HEAD__FILE__
#pragma once
#include <QWidget>

class NodeItem;
class GenerateBinWidget : public QWidget{
	Q_OBJECT;
protected:
	NodeItem* nodeItem;
public:
	GenerateBinWidget( NodeItem *node_item );
};

#endif // GENERATEBINWIDGET_H_H_HEAD__FILE__
