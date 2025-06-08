#ifndef NODEFILEINFO_H_H_HEAD__FILE__
#define NODEFILEINFO_H_H_HEAD__FILE__
#pragma once
#include "qt/node/nodeWidget/INodeWidget.h"

class NodeFileInfo : public INodeWidget {
	Q_OBJECT;
public:
	NodeFileInfo( QWidget *parent, Qt::WindowFlags f );
	NodeFileInfo( ) : NodeFileInfo( nullptr, Qt::WindowFlags( ) ) { }
};

#endif // NODEFILEINFO_H_H_HEAD__FILE__
