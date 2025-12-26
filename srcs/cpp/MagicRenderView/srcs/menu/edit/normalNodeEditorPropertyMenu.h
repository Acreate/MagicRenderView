#ifndef NORMALNODEEDITORPROPERTYMENU_H_H_HEAD__FILE__
#define NORMALNODEEDITORPROPERTYMENU_H_H_HEAD__FILE__
#pragma once
#include <QMenu>

class OutputPort;
class InputPort;
class Node;
class NormalNodeEditorPropertyMenu : public QMenu {
	Q_OBJECT;
public:
	class ActionPair {
		QAction *trigAction;
		OutputPort *outputPort;
		InputPort *inputPort;
	public:
		virtual ~ActionPair( ) = default;
		ActionPair( QAction *trig_action, OutputPort *output_port, InputPort *input_port )
			: trigAction( trig_action ),
			outputPort( output_port ),
			inputPort( input_port ) { }
		virtual QAction * getTrigAction( ) const { return trigAction; }
		virtual OutputPort * getOutputPort( ) const { return outputPort; }
		virtual InputPort * getInputPort( ) const { return inputPort; }
	};
protected:
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
	std::vector< ActionPair > actionMap;
public:
	NormalNodeEditorPropertyMenu( );
	virtual bool initNormalNodeEditorPropertyMenu( );
	virtual bool setNode( Node *node );
Q_SIGNALS:
	void release_signal( NormalNodeEditorPropertyMenu *release_ptr );
	void unLink( NormalNodeEditorPropertyMenu *signal_ptr, OutputPort *output_port, InputPort *input_port );
	void show_node_edit_info_widget_signal( NormalNodeEditorPropertyMenu *signal_ptr, Node *show_node );
	void show_node_at_widget_signal( NormalNodeEditorPropertyMenu *signal_ptr, Node *ensure_node );
};

#endif // NORMALNODEEDITORPROPERTYMENU_H_H_HEAD__FILE__
