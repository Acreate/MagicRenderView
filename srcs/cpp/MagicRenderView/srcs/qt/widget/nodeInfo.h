#ifndef NODEINFO_H_H_HEAD__FILE__
#define NODEINFO_H_H_HEAD__FILE__
#pragma once



#include <QWidget>
class NodeInfo : public QWidget {
	Q_OBJECT;
public:
	NodeInfo( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) ) : QWidget( parent, f ) { }

};
#endif // NODEINFO_H_H_HEAD__FILE__
