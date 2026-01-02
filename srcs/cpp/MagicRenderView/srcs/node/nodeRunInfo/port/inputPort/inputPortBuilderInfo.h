#ifndef INPUTPORTBUILDERINFO_H_H_HEAD__FILE__
#define INPUTPORTBUILDERINFO_H_H_HEAD__FILE__
#pragma once
#include <QObject>

class NodeBuilderInfo;
class VarDirector;
class InputPort;
class InputPortBuilderInfo : public QObject {
	Q_OBJECT;
	friend class InputPortBuilderInfoTools;
protected:
	using UCallFunctionAlias = std::function< bool( InputPortBuilderInfo *call_obj_ptr, std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector ) >;
	InputPort *inputPort;
	UCallFunctionAlias inputPortCallFunction;
	VarDirector *varDirector = nullptr;
	void *varValuePtr = nullptr;
public:
	InputPortBuilderInfo( InputPort *input_port );
	virtual bool init( const UCallFunctionAlias &input_port_call_function );
	virtual bool call( std::vector< NodeBuilderInfo * > &result_suggestion_next_builder_vector );
};

#endif // INPUTPORTBUILDERINFO_H_H_HEAD__FILE__
