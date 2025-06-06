#ifndef INODEWIDGET_H_H_HEAD__FILE__
#define INODEWIDGET_H_H_HEAD__FILE__
#pragma once

#include <QWidget>

#include "alias/type_alias.h"

#include "qt/functionDeclaration/IFunctionDeclaration.h"
class IFunctionDeclaration;
class INodeWidget : public QWidget {
	Q_OBJECT;
protected:
	/// @brief 引用的函数
	std_shared_ptr< IFunctionDeclaration > functionDeclarationPtr;
public:
	INodeWidget( QWidget *parent, const std_shared_ptr< IFunctionDeclaration > &function_declaration_ptr, const Qt::WindowFlags &f ): QWidget( parent, f ), functionDeclarationPtr( function_declaration_ptr ) {
	}
	virtual void call( ) const {
		if( functionDeclarationPtr )
			functionDeclarationPtr.get( )->call( );
	}
	virtual const std_shared_ptr< IFunctionDeclaration > & getFunctionDeclarationPtr( ) const { return functionDeclarationPtr; }
};

#endif // INODEWIDGET_H_H_HEAD__FILE__
