#ifndef GENERATEQIMAGEWIDGET_H_H_HEAD__FILE__
#define GENERATEQIMAGEWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

class NodeItem;
class GenerateQImageWidget : public QWidget {
	Q_OBJECT;
protected:
	NodeItem *nodeItem;
public:
	GenerateQImageWidget( NodeItem *node_item ) : nodeItem( node_item ) { };
};
#endif // GENERATEQIMAGEWIDGET_H_H_HEAD__FILE__
