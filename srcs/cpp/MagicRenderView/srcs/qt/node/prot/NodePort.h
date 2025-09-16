#ifndef NODEPORT_H_H_HEAD__FILE__
#define NODEPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <qimage.h>

#include <alias/type_alias.h>

#include <qt/varType/varType.h>

class Application;
class NodeItem;
class NodePort : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( );
protected:
	/// @brief 绑定变量
	VarType *var;
	/// @brief 绑定渲染
	QImage *nodePortRender;
	/// @brief 图标
	QImage *ico;
	/// @brief 端口宽度
	int portItemWidth;
	/// @brief 端口高度
	int portItemHeith;
	/// @brief 图标宽度
	int icoItemWidth;
	/// @brief 图标高度
	int icoItemHeith;
	/// @brief 标题
	QString title;
	/// @brief 父节点
	NodeItem *parent;
	/// @brief 引用对象指针
	Application *applicationInstancePtr;
public:
	NodePort( NodeItem *parent );
	~NodePort( ) override;
	virtual int getIcoWidth( ) const { return icoItemWidth; }
	virtual int getIcoHeith( ) const { return icoItemHeith; }
	virtual const QString & getTitle( ) const { return title; }
	virtual void setTitle( const QString &title ) { this->title = title; }
	virtual QImage * getIco( ) const {
		return ico;
	}
	virtual void setIco( const QImage &new_ico ) {
		*ico = new_ico;
		icoItemHeith = ico->height( );
		icoItemWidth = ico->width( );
	}
	virtual void setIco( const QString &new_ico_path );
	virtual bool renderLayout( bool ico_is_end );
	virtual QImage * getNodePortRender( ) const { return nodePortRender; }
	virtual int height( ) const {
		return portItemHeith;
	}
	virtual int width( ) const {
		return portItemWidth;
	}
	virtual QSize getSize( ) const { return QSize( portItemWidth, portItemHeith ); }

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
	virtual bool updateProtLayout( ) = 0;
protected Q_SLOTS:
	virtual void releaseVarType( VarType *release_var_type ) {
		if( release_var_type == var )
			bindVar( nullptr );
	}
Q_SIGNALS:
	void replaceVar( VarType *old_var, VarType *new_var );
};
#endif // NODEPORT_H_H_HEAD__FILE__
