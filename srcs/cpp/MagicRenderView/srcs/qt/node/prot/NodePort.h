#ifndef NODEPORT_H_H_HEAD__FILE__
#define NODEPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <qimage.h>

#include <alias/type_alias.h>

#include <qt/varType/varType.h>

class NodePort : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( );
protected:
	/// @brief 绑定变量
	VarType *var;
	/// @brief 绑定渲染
	QImage nodePortRender;
	/// @brief 相对节点的位置
	QPoint pos;
public:
	NodePort( QObject *parent, VarType *bind_var ) : QObject( parent ), var( bind_var ) {
		if( var )
			connect( var, &VarType::deleteObjBefore, this, &NodePort::releaseVarType );
	}
	virtual const QImage & getNodePortRender( ) const { return nodePortRender; }
	virtual const QPoint & getPos( ) const { return pos; }
	virtual const QSize & getSize( ) const { return nodePortRender.size( ); }
	virtual QRect geometry( ) const { return QRect( getPos( ), getSize( ) ); }
	virtual const VarType * getVar( ) const {
		return var;
	}
	virtual void bindVar( VarType *bind_var ) {
		auto old = var;
		var = bind_var;
		if( old )
			old->disconnect( this );
		if( bind_var )
			connect( var, &VarType::deleteObjBefore, this, &NodePort::releaseVarType );
		emit replaceVar( old, var );
	}
protected Q_SLOTS:
	virtual void releaseVarType( VarType *release_var_type ) {
		if( release_var_type == var )
			bindVar( nullptr );
	}
Q_SIGNALS:
	void replaceVar( VarType *old_var, VarType *new_var );
};
#endif // NODEPORT_H_H_HEAD__FILE__
