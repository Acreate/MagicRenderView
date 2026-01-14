#ifndef PORTFRINEDCLASS_H_H_HEAD__FILE__
#define PORTFRINEDCLASS_H_H_HEAD__FILE__


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
	friend class PortLinkType;

#define InputPortFrinedClass( ) \
	ConjugatePortFrinedClass( ); \
	friend class OutputPort

#define OutputPortFrinedClass( ) \
	ConjugatePortFrinedClass( ); \
	friend class InputPort

#endif // PORTFRINEDCLASS_H_H_HEAD__FILE__
