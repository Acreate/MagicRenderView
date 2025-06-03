#ifndef NODELIST_H_H_HEAD__FILE__
#define NODELIST_H_H_HEAD__FILE__
#pragma once

#include <QWidget>
class NodeList : public QWidget {
	Q_OBJECT;
public:
	NodeList( QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags( ) ) : QWidget( parent, f ) { }

};
#endif // NODELIST_H_H_HEAD__FILE__
