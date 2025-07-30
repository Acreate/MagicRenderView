#ifndef INODEGENERATERITEM_H_H_HEAD__FILE__
#define INODEGENERATERITEM_H_H_HEAD__FILE__
#pragma once
#include <qt/types/ITypeObject.h>

#include "../../functionDeclaration/IFunctionDeclaration.h"

class INodeWidget;
class INodeGeneraterItem : public QObject {
	Q_OBJECT;
protected:
	IFunctionDeclaration functionDeclaration;
public:
	INodeGeneraterItem( const IFunctionDeclaration &function_declaration, QObject *parent = nullptr );
	virtual size_t sortCode( ) const;
	/// @brief 创建显示列表节点
	/// @return 显示列表节点
	QWidget * createListNodeWidget( ) const;
	/// @brief 创建节点窗口
	/// @return 窗口
	INodeWidget * createScriptNodeWidget( ) const;
	/// @brief 创建节点图片
	/// @return 节点图片
	std_shared_ptr< QImage > createNodeImage( ) const;
};

#endif // INODEGENERATERITEM_H_H_HEAD__FILE__
