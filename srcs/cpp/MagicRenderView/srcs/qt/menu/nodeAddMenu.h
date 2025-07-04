﻿#ifndef NODEADDMENU_H_H_HEAD__FILE__
#define NODEADDMENU_H_H_HEAD__FILE__
#pragma once

#include <QMenu>

#include "qt/functionDeclaration/IFunctionDeclaration.h"
#include "qt/stack/nodeStack/INodeStack.h"

class INodeStack;
class NodeAddAction;

class NodeAddMenu : public QMenu {
	Q_OBJECT;
protected:
	std_vector<INodeStack*> menuSeed;
public:
	NodeAddMenu( QWidget *parent );
	NodeAddMenu( const QString &title = "", QWidget *parent = nullptr )
		: NodeAddMenu( parent ) { }
	~NodeAddMenu( ) override;
	virtual bool appendNodeStackObjectPtrToMenuSubMenu( INodeStack *node_stack );
	void clearMenuActions( QMenu *menu );
Q_SIGNALS:
	/// @brief 选项被正式激活
	/// @param action 激活选项
	void activeAction( QAction *action );
public:
	template< typename TNodeGenerate >
		requires requires ( INodeStack *paren, TNodeGenerate *ta ) {
			paren = ta;
		}
	bool init( ) {
		auto nodeGenerate = INodeStack::getInstance< TNodeGenerate >( );
		return appendNodeStackObjectPtrToMenuSubMenu( nodeGenerate );
	}
};

#endif // NODEADDMENU_H_H_HEAD__FILE__
