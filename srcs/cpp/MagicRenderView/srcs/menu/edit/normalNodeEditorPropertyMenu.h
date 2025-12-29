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
	class ActionLinkInfoPair {
		AutoAction *trigAction;
		OutputPort *outputPort;
		InputPort *inputPort;
	public:
		virtual ~ActionLinkInfoPair( ) = default;
		ActionLinkInfoPair( AutoAction *trig_action, OutputPort *output_port, InputPort *input_port );
		virtual AutoAction * getTrigAction( ) const { return trigAction; }
		virtual OutputPort * getOutputPort( ) const { return outputPort; }
		virtual InputPort * getInputPort( ) const { return inputPort; }
	};
	class ActionNodeInfoPair {
		AutoAction *trigAction;
		Node *node;
		OutputPort *outputPort;
		InputPort *inputPort;
	public:
		virtual ~ActionNodeInfoPair( ) = default;
		ActionNodeInfoPair( AutoAction *trig_action, Node *node, OutputPort *output_port, InputPort *input_port );
		virtual AutoAction * getTrigAction( ) const { return trigAction; }
		virtual Node * getNode( ) const { return node; }
		virtual OutputPort * getOutputPort( ) const { return outputPort; }
		virtual InputPort * getInputPort( ) const { return inputPort; }
	};
protected:
	/// @brief 当前节点指针
	Node *currentNode;
	/// @brief 删除菜单
	QMenu *deleteMenu;
	/// @brief 显示菜单
	QMenu *dislayMenu;
	/// @brief 输入管理菜单
	QMenu *inputMneu;
	/// @brief 输出管理菜单
	QMenu *outputMenu;
	/// @brief 显示输入引用节点菜单
	QMenu *displayInputRef;
	/// @brief 显示我输出引用节点菜单
	QMenu *displayOutputRef;
	/// @brief 删除输入端中的输出引用
	QMenu *deleteInputAtOutputRef;
	/// @brief 删除输出端中的输出引用
	QMenu *deleteOutputAtInputRef;
	/// @brief 端口连接删除输入映射
	std::vector< ActionLinkInfoPair > unLinkPortActionInputMap;
	/// @brief 端口连接删除输入映射个数
	size_t unLinkPortActionInputMapCount;
	/// @brief 端口连接删除输入映射起始地址
	ActionLinkInfoPair *unLinkPortActionInputMapArrayPtr;
	/// @brief 端口连接删除输入映射
	std::vector< ActionLinkInfoPair > unLinkPortActionOutputMap;
	/// @brief 端口连接删除输入映射个数
	size_t unLinkPortActionOutputMapCount;
	/// @brief 端口连接删除输入映射起始地址
	ActionLinkInfoPair *unLinkPortActionOutputMapArrayPtr;

	/// @brief 端口输入节点引用映射
	std::vector< ActionNodeInfoPair > refInputPortActionMap;
	/// @brief 端口输入节点引用映射个数
	size_t refInputPortActionMapCount;
	/// @brief 端口输入节点引用映射起始地址
	ActionNodeInfoPair *refInputPortActionMapArrayPtr;
	/// @brief 端口输出节点引用映射
	std::vector< ActionNodeInfoPair > refOutputPortActionMap;
	/// @brief 端口输出节点引用映射个数
	size_t refOutputPortActionMapCount;
	/// @brief 端口输出节点引用映射起始地址
	ActionNodeInfoPair *refOutputPortActionMapArrayPtr;
	/// @brief 删除该匹配节点
	AutoAction *deleteNodeAction;
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
	virtual bool appendRefOutputNodeActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port );
	virtual bool appendRefInputNodeActionInfo( AutoAction *auto_action, OutputPort *output_port, InputPort *input_port );
private Q_SLOTS:
	void removeInoutPortRefLinkAction( QAction *tr_obj_ptr );
	void removeNodeAction( );
	void removeOutoutPortRefLinkAction( QAction *tr_obj_ptr );
	void displayInfoWidget( QAction *tr_obj_ptr );
	void displayAtRefOutputNodeEnsureToWidget( QAction *tr_obj_ptr );
	void displayAtRefInputNodeEnsureToWidget( QAction *tr_obj_ptr );
public:
	NormalNodeEditorPropertyMenu( );
	~NormalNodeEditorPropertyMenu( ) override;
	virtual bool initNormalNodeEditorPropertyMenu( );
	virtual bool setNode( Node *node );
protected:
	void hideEvent( QHideEvent * ) override;
Q_SIGNALS:
	void release_signal( NormalNodeEditorPropertyMenu *release_ptr );
	void remove_node_action_signal( NormalNodeEditorPropertyMenu *signal_ptr, Node *remove_target );
	void unLink_signal( NormalNodeEditorPropertyMenu *signal_ptr, OutputPort *output_port, InputPort *input_port );
	void show_node_edit_info_widget_signal( NormalNodeEditorPropertyMenu *signal_ptr, Node *show_node, NodeInfoWidget *show_info_widget );
	void show_node_at_widget_signal( NormalNodeEditorPropertyMenu *signal_ptr, Node *ensure_node );
};

#endif // NORMALNODEEDITORPROPERTYMENU_H_H_HEAD__FILE__
