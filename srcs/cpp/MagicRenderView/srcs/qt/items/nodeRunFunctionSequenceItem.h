#ifndef NODERUNFUNCTIONSEQUENCEITEM_H_H_HEAD__FILE__
#define NODERUNFUNCTIONSEQUENCEITEM_H_H_HEAD__FILE__
#pragma once
#include <qobject.h>

#include <alias/type_alias.h>

class NodeScriptsWidget;
class IFunctionDeclaration;
class NodeRunFunctionSequenceItem : public QObject {
	Q_OBJECT;
public:
	friend class NodeRunSequenceWidget;
	friend class NodeRunSequenceItemWidget;
	friend class NodeRunSequenceItemFunctionWidget;
	/// @brief 遍历函数
	using foreachCallBack = std_function< void( std_list< NodeRunFunctionSequenceItem * >::iterator &beg, std_list< NodeRunFunctionSequenceItem * >::iterator &end ) >;
protected:
	/// @brief 子级项
	std_list< NodeRunFunctionSequenceItem * > subItems;
	/// @brief 上级项
	NodeRunFunctionSequenceItem *topLayerItem;
	/// @brief 函数定义
	std_shared_ptr< IFunctionDeclaration > functionDeclaration;
	/// @brief 该节点的渲染 ui
	NodeRunSequenceItemFunctionWidget *renderCurrentNodeFunctionWidget;
	/// @brief 子节点的渲染 ui
	NodeRunSequenceItemWidget *renderSubItemsNodeWidget;
	/// @brief 顶层渲染容器
	NodeRunSequenceWidget *runMainSequenceWidget;
public:
	NodeRunFunctionSequenceItem( NodeRunSequenceWidget *run_sequence_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration = nullptr, NodeRunFunctionSequenceItem *top_layer_item = nullptr );
	~NodeRunFunctionSequenceItem( ) override;
public:
	/// @brief 获取渲染该项的渲染窗口
	/// @return 窗口指针
	virtual NodeRunSequenceItemFunctionWidget * getRenderCurrentNodeWidget( ) const { return renderCurrentNodeFunctionWidget; }
	/// @brief 获取渲染子项的渲染窗口
	/// @return 窗口指针
	virtual NodeRunSequenceItemWidget * getRenderSubItemsNodeWidget( ) const { return renderSubItemsNodeWidget; }
	/// @brief 获取顶级渲染窗口
	/// @return 窗口指针
	virtual NodeRunSequenceWidget * getMainRunSequenceWidget( ) const { return runMainSequenceWidget; }
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
	virtual NodeRunFunctionSequenceItem * insertNodeRender( NodeScriptsWidget *generater_scripts_widget, const std_shared_ptr< IFunctionDeclaration > &function_declaration, const QPoint &glob_point, const QPoint &set_point );
Q_SIGNALS:
	void subItemChange( );
	void currentItemRemove( NodeRunFunctionSequenceItem *remove_item_ptr );
	void showSubItemWidget( NodeRunSequenceItemWidget *event_widget, bool is_show, NodeRunFunctionSequenceItem *item );
	void showCurrentItemWidget( NodeRunSequenceItemFunctionWidget *event_widget, bool is_show, NodeRunFunctionSequenceItem *item );
	void currentItemDoubleClick( NodeRunSequenceItemFunctionWidget *event_widget, NodeRunFunctionSequenceItem *item );
};

#endif // NODERUNFUNCTIONSEQUENCEITEM_H_H_HEAD__FILE__
