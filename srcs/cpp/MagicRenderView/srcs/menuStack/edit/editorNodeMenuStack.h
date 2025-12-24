#ifndef EDITORNODEMENUSTACK_H_H_HEAD__FILE__
#define EDITORNODEMENUSTACK_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class EditorNodeMenuStack : public QObject {
	Q_OBJECT;
public:
	EditorNodeMenuStack( QObject *parent = nullptr );
	virtual bool initStack( );
};

#endif // EDITORNODEMENUSTACK_H_H_HEAD__FILE__
