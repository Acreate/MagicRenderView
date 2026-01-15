#ifndef NODETOOLS_H_H_HEAD__FILE__
#define NODETOOLS_H_H_HEAD__FILE__
#include <vector>

class DynamicTypeInputPort;
class VarDirector;
namespace NodeEnum {
	enum class NodeType;
}
class DynamicTypeOutputPort;
class Node;
class OutputPort;
class InputPort;
class NodeTools {
	friend class Node;
public:
	virtual ~NodeTools( ) = default;
protected:
	Node *nodePtr;
protected:
	NodeTools( Node *node_ptr )
		: nodePtr( node_ptr ) { }
public:
	virtual std::vector< InputPort * > * getRefPort( OutputPort *output_port );
	virtual const std::vector< InputPort * > * getRefPort( const OutputPort *output_port ) const;
	virtual bool getRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector );
	virtual bool getFilterRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool getFilterNotRefPortNodeVector( const OutputPort *output_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool setPortVar( OutputPort *output_port, void *new_par );
	virtual bool setPortVar( DynamicTypeOutputPort *output_port, void *new_par );
	virtual bool setPortMultiple( OutputPort *output_port, bool multiple );
	virtual bool getVarDirector( OutputPort *output_port, VarDirector * &result_var_director, void *&result_var_ptr );
	virtual bool setVarDirector( OutputPort *output_port, VarDirector *var_director );
	virtual bool getInfo( OutputPort *output_port, Node * &result_input_port_node_parent, VarDirector * &result_var_director, void *&result_var_ptr );
	virtual bool setInfo( OutputPort *output_port, VarDirector *var_director, void *var_ptr );

	virtual std::vector< OutputPort * > * getRefPort( InputPort *input_port );
	virtual const std::vector< OutputPort * > * getRefPort( const InputPort *input_port );
	virtual bool getRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector );
	virtual bool getFilterRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool getFilterNotRefPortNodeVector( const InputPort *input_port, std::vector< Node * > &result_filter_node_vector, NodeEnum::NodeType node_type );
	virtual bool setPortVar( InputPort *input_port, void *new_par );
	virtual bool setPortVar( DynamicTypeInputPort *input_port, void *new_par );
	virtual bool setPortMultiple( InputPort *input_port, bool multiple );
	virtual bool setVarDirector( InputPort *input_port, VarDirector *var_director );
	virtual bool getVarDirector( InputPort *input_port, VarDirector * &result_var_director, void *&result_var_ptr );
	virtual bool getInfo( InputPort *input_port, Node * &result_input_port_node_parent, VarDirector * &result_var_director, void *&result_var_ptr );
	virtual bool setInfo( InputPort *input_port, VarDirector *var_director, void *var_ptr );
};

#endif // NODETOOLS_H_H_HEAD__FILE__
