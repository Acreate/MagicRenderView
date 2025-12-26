#ifndef NORMALNODEEDITORPROPERTYMENU_H_H_HEAD__FILE__
#define NORMALNODEEDITORPROPERTYMENU_H_H_HEAD__FILE__
#pragma once
#include <QMenu>

class AutoAction;
class NodeInfoWidget;
class OutputPort;
class InputPort;
class Node;
class NormalNodeEditorPropertyMenu : public QMenu {
	Q_OBJECT;
public:
	class ActionPair {
		AutoAction *trigAction;
		OutputPort *outputPort;
		InputPort *inputPort;
	public:
		virtual ~ActionPair( ) = default;
		ActionPair( AutoAction *trig_action, OutputPort *output_port, InputPort *input_port );
		virtual AutoAction * getTrigAction( ) const { return trigAction; }
		virtual OutputPort * getOutputPort( ) const { return outputPort; }
		virtual InputPort * getInputPort( ) const { return inputPort; }
	};
protected:
	/// @brief 当前节点指针
	Node* currentNode;
	/// @brief 显示菜单
	QMenu *dislayMenu;
	/// @brief 输入管理菜单
	QMenu *inputMneu;
	/// @brief 输出管理菜单
	QMenu *outputMenu;
	/// @brief 显示输入引用节点菜单
	QMenu *dislayInputRef;
	/// @brief 显示我输出引用节点菜单
	QMenu *dislayOutputRef;
	/// @brief 删除输入端中的输出引用
	QMenu *deleteInputAtOutputRef;
	/// @brief 删除输出端中的输出引用
	QMenu *deleteOutputAtInputRef;
	/// @brief 端口连接删除输入映射
	std::vector< ActionPair > unLinkPortActionInputMap;
	/// @brief 端口连接删除输入映射个数
	size_t unLinkPortActionInputMapCount;
	/// @brief 端口连接删除输入映射起始地址
	ActionPair *unLinkPortActionInputMapArrayPtr;
	/// @brief 端口连接删除输入映射
	std::vector< ActionPair > unLinkPortActionOutputMap;
	/// @brief 端口连接删除输入映射个数
	size_t unLinkPortActionOutputMapCount;
	/// @brief 端口连接删除输入映射起始地址
	ActionPair *unLinkPortActionOutputMapArrayPtr;
	/// @brief 显示编辑节点菜单
	AutoAction *displayInfoWidgetAction;
	/// @brief 不存在节点编辑窗口时，显示该对象
	AutoAction *noteInfoWidgetAction;
	/// @brief 不存在输出引用
	AutoAction *noteRemoveOutputLinkAction;
	/// @brief 不存在输入引用
	AutoAction *noteRemoveInputputLinkAction;
	std::vector< AutoAction * > qactionArchiveVector;
	NodeInfoWidget *nodeInfoWidget;
	size_t qactionArchiveCount;
	AutoAction **actionArchiveArrayPtr;
protected:
	virtual bool extendQActionArchiveVectorCount( size_t extendCount = 1024 );
	virtual bool appendRmoveOutputRefActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port );
	virtual bool appendRmoveInputRefActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port );
private Q_SLOTS:
	void removeInoutPortRefLinkAction( QAction *tr_obj_ptr );
	void removeOutoutPortRefLinkAction( QAction *tr_obj_ptr );
	void displayInfoWidget( QAction *tr_obj_ptr );
	void displayAtNodEnsureToWidget( QAction *tr_obj_ptr );
public:
	NormalNodeEditorPropertyMenu( );
	~NormalNodeEditorPropertyMenu( ) override;
	virtual bool initNormalNodeEditorPropertyMenu( );
	virtual bool setNode( Node *node );
Q_SIGNALS:
	void release_signal( NormalNodeEditorPropertyMenu *release_ptr );
	void unLink_signal( NormalNodeEditorPropertyMenu *signal_ptr, OutputPort *output_port, InputPort *input_port );
	void show_node_edit_info_widget_signal( NormalNodeEditorPropertyMenu *signal_ptr, Node *show_node, NodeInfoWidget *show_info_widget );
	void show_node_at_widget_signal( NormalNodeEditorPropertyMenu *signal_ptr, Node *ensure_node );
};

#endif // NORMALNODEEDITORPROPERTYMENU_H_H_HEAD__FILE__
