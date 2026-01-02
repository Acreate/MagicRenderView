#ifndef NODEBUILDERINFO_H_H_HEAD__FILE__
#define NODEBUILDERINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class InputPortBuilderInfo;
class VarDirector;
class OutputPortBuilderInfo;
class Node;
class NodeBuilderInfo : public QObject {
	Q_OBJECT;
protected:
	Node *node;
	using UCallFunctionAlias = std::function< bool( std::vector< InputPortBuilderInfo * > &, std::vector< OutputPortBuilderInfo * > &, std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector ) >;
	UCallFunctionAlias nodeCallFunction;
public:
	NodeBuilderInfo( Node *node );
	virtual bool init( const UCallFunctionAlias &node_call_fucntion );
	virtual bool call( std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector );
};

class OutputPortBuilderInfoTools {
	friend class NodeBuilderInfo;
	static void getValueInfo( OutputPortBuilderInfo *output_port_builder_info, VarDirector *&result_var_director, void *&result_value_ptr );
};
class InputPortBuilderInfoTools {
	friend class NodeBuilderInfo;
	static void getValueInfo( InputPortBuilderInfo *input_port_builder_info, VarDirector *&result_var_director, void *&result_value_ptr );
};
#endif // NODEBUILDERINFO_H_H_HEAD__FILE__
