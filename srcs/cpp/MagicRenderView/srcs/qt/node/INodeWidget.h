#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "alias/type_alias.h"
class IFunctionDeclaration;
class INodeWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 引用的函数
	std_shared_ptr< IFunctionDeclaration > functionDeclarationPtr;
public:
	INodeWidget( QWidget *const parent, const std_shared_ptr< IFunctionDeclaration > &function_declaration_ptr, const Qt::WindowFlags &f );
	virtual void call( ) const;
	const std_shared_ptr< IFunctionDeclaration > & getFunctionDeclarationPtr( ) const { return functionDeclarationPtr; }
};

#endif // INODEWIDGET_H_H_HEAD__FILE__
