#ifndef OUTPUTPORTBUILDERINFO_H_H_HEAD__FILE__
#define OUTPUTPORTBUILDERINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class NodeBuilderInfo;
class VarDirector;
class OutputPort;
class OutputPortBuilderInfo : public QObject {
	Q_OBJECT;
	friend class OutputPortBuilderInfoTools;
protected:
	OutputPort *outputPort;
	using UCallFunctionAlias = std::function< bool( OutputPortBuilderInfo *call_obj_ptr, std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector ) >;
	UCallFunctionAlias outputPortCallFunction;
	VarDirector *varDirector = nullptr;
	void *varValuePtr = nullptr;
public:
	OutputPortBuilderInfo( OutputPort *output_port );
	virtual bool init( const UCallFunctionAlias &output_port_call_function );
	virtual bool call( std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector );
};
#endif // OUTPUTPORTBUILDERINFO_H_H_HEAD__FILE__
