#ifndef NODERUNFUNCTIONSEQUENCEITEM_H_H_HEAD__FILE__
#define NODERUNFUNCTIONSEQUENCEITEM_H_H_HEAD__FILE__
#pragma once
#include <qobject.h>

#include <alias/type_alias.h>

class NodeScriptsWidget;
class IFunctionDeclaration;
class NodeRunSequenceWidget;
class NodeRunFunctionSequenceItemRnderWidget;
class NodeRunFunctionSequenceItem : public QObject {
	Q_OBJECT;
public:
	friend class NodeRunSequenceWidget;
	/// @brief 遍历函数
	using foreachCallBack = std_function< void( std_list< NodeRunFunctionSequenceItem * >::iterator &beg, std_list< NodeRunFunctionSequenceItem * >::iterator &end ) >;
protected:
	std_list< NodeRunFunctionSequenceItem * > subItems;
	NodeRunFunctionSequenceItem *topLayerItem;
	NodeRunFunctionSequenceItemRnderWidget *renderWidget;
	NodeRunSequenceWidget *runSequenceWidget;
public:
	NodeRunFunctionSequenceItem( NodeRunSequenceWidget *run_sequence_widget, NodeRunFunctionSequenceItem *top_layer_item = nullptr );
	~NodeRunFunctionSequenceItem( ) override;
public:
	/// @brief 获取渲染窗口
	/// @return 队列窗口 ui 窗口
	virtual NodeRunFunctionSequenceItemRnderWidget * getRenderWidget( ) const {
		return renderWidget;
	}
public:
	/// @brief 在该节点之前插入一个节点
	/// @param insert_item 插入的节点
	/// @return 失败返回 false
	virtual bool insertBefore( NodeRunFunctionSequenceItem *insert_item );
	/// @brief 在该节点之后插入一个节点
	/// @param insert_item 插入的节点
	/// @return 失败返回 false
	virtual bool insertAfter( NodeRunFunctionSequenceItem *insert_item );
	/// @brief 在该节点最开始插入一个节点
	/// @param insert_item 插入的节点
	/// @return 失败返回 false
	virtual bool insertFirst( NodeRunFunctionSequenceItem *insert_item );
	/// @brief 在该节点最末尾插入一个节点
	/// @param insert_item 插入的节点
	/// @return 失败返回 false
	virtual bool insertEnd( NodeRunFunctionSequenceItem *insert_item );
	/// @brief 该节点替换指定节点
	/// @param insert_item 替换的节点
	/// @return 成功返回 true
	virtual bool replace( NodeRunFunctionSequenceItem *insert_item );
	/// @brief 遍历子队列
	/// @param foreach_call_brack 变量调用函数
	/// @return 成功遍历返回 true
	virtual bool foreachSubLayerBeg( const foreachCallBack &foreach_call_brack );

	/// @brief 获取遍历当前所在队列的权限
	/// @param foreach_call_brack 
	/// @return 返回 false 表示不存在父节点队列
	virtual bool foreachSupperLayerBeg( const foreachCallBack &foreach_call_brack ) {
		if( topLayerItem )
			return topLayerItem->foreachSubLayerBeg( foreach_call_brack );
		return false;
	}
	
	/// @brief 在指定位置配置节点窗口
	/// @param generater_scripts_widget 调用窗口
	/// @param function_declaration 绘制目标
	/// @param glob_point 全局位置
	/// @param set_point 绘制位置
	/// @return 绘制生成的节点窗口
	virtual NodeRunFunctionSequenceItem * setRunFunctionWidget( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point );
Q_SIGNALS:
	void itemChange( );
};

#endif // NODERUNFUNCTIONSEQUENCEITEM_H_H_HEAD__FILE__
