#ifndef NODEPORT_H_H_HEAD__FILE__
#define NODEPORT_H_H_HEAD__FILE__
#pragma once

#include <QObject>
#include <qimage.h>

#include <alias/type_alias.h>

class VarType;
class Application;
class NodeItem;
class NodePort : public QObject, public Type_Alias {
	Q_OBJECT;
	Def_Last_StaticMetaInfo( );
private:
	friend class NodeWidgetSerialization;
	friend class NodeItemSerialization;
	friend class MainWidget;
protected:
	size_t generateCode;
	/// @brief 绑定变量
	size_t varCode;
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
	NodeItem *parentItem;
	/// @brief 引用对象指针
	Application *applicationInstancePtr;
public:
	NodePort( NodeItem *parent_item );
	~NodePort( ) override;
	virtual bool getPos( QPoint &result_pos ) const = 0;
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
	virtual bool updateProtLayout( ) = 0;

Q_SIGNALS:
	void releaseThiNodeProt(NodePort* release_ptr);
};
#endif // NODEPORT_H_H_HEAD__FILE__
