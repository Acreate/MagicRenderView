#ifndef PORTFRINEDCLASS_H_H_HEAD__FILE__
#define PORTFRINEDCLASS_H_H_HEAD__FILE__

#define Declaration_Class_Name() \
	class VarDirector; \
	class Node; \
	class NodeRefLinkInfo; \
	class NodePortLinkInfo; \
	class NodePortLinkActionPair; \
	class InputportLinkOutputPortInfo; \
	class NodeDirector; \
	class NodeStack; \
	class NodeRefLinkInfoTools; \
	class NodeBuilderTools; \
	class NodeRunInfo; \
	class NormalNodeEditorPropertyMenu; \
	class NodeTypeInfoSerializeion; \
	class NodeTypeInfo; \
	class PortTypeInfo; \
	class NodeTools; \
	class PortLinkType

#define ConjugatePortFrinedClass( ) \
	friend class Node; \
	friend class NodeRefLinkInfo; \
	friend class NodePortLinkInfo; \
	friend class NodePortLinkActionPair; \
	friend class InputportLinkOutputPortInfo; \
	friend class NodeDirector; \
	friend class NodeStack; \
	friend class NodeRefLinkInfoTools; \
	friend class NodeBuilderTools; \
	friend class NodeRunInfo; \
	friend class NormalNodeEditorPropertyMenu; \
	friend class NodeTypeInfoSerializeion; \
	friend class NodeTypeInfo; \
	friend class PortTypeInfo; \
	friend class NodeTools; \
	friend class PortLinkType

#define InputPortFrinedClass( ) \
	ConjugatePortFrinedClass( ); \
	friend class OutputPort

#define OutputPortFrinedClass( ) \
	ConjugatePortFrinedClass( ); \
	friend class InputPort

#define NodePortFrinedClass( ) \
	ConjugatePortFrinedClass( );

#endif // PORTFRINEDCLASS_H_H_HEAD__FILE__
