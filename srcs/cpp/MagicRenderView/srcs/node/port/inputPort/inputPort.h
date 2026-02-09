#ifndef INPUTPORT_H_H_HEAD__FILE__
#define INPUTPORT_H_H_HEAD__FILE__

#include <define/portFrinedClass.h>

#include "../nodePort.h"

class SrackInfo;
class QHBoxLayout;
class QLabel;
class Application;
class VarDirector;
class OutputPort;
class NodePortLinkInfo;
class Node;
class NodeRunInfo;
class InputPort : public NodePort {
	Q_OBJECT;
private:
	InputPortFrinedClass( );
protected:
	std::vector< OutputPort * > refOutputPortVector;
protected:
	QLabel *ico;
	QLabel *showTitle;
	QHBoxLayout *mainLayout;
	Node *parentNode;
protected:
	virtual bool emplaceBackOutputPortRef( OutputPort *output_port_ptr );
	virtual bool eraseOutputPortRef( OutputPort *output_port_ptr );
	virtual void clearOutputPortRef( );
	/// @brief 绑定端口信息
	/// @return 成功返回 true
	virtual bool bindPortInfo( );
	/// @brief 释放端口信息
	/// @return 成功返回 true
	virtual bool releasePortInfo( );
public:
	InputPort( const QString &name );
	~InputPort( ) override;
	bool init( Node *parent ) override;
	QPoint getLinkPoint( ) const override;
	virtual bool hasOutputPortRef( const OutputPort *output_port_ptr ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
	bool event( QEvent *event ) override;
public:
	// 信号
Q_SIGNALS:
	/// @brief 释放对象产生信号
	/// @param release_node_port 释放对象指针
	/// @param srack_info 信号行
	void release_node_signal( InputPort *release_node_port, const SrackInfo &srack_info );
	/// @brief 链接信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void connect_input_port_signal( InputPort *input_port, OutputPort *ref_output_port );
	/// @brief 断开信号
	/// @param input_port 输入端口
	/// @param ref_output_port 输出端口
	void dis_connect_input_port_signal( InputPort *input_port, OutputPort *ref_output_port );
};

#endif // INPUTPORT_H_H_HEAD__FILE__
