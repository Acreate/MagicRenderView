#ifndef NODEFRINEDCLASS_H_H_HEAD__FILE__
#define NODEFRINEDCLASS_H_H_HEAD__FILE__
namespace NodeRunLinkTools{ class Get;}
namespace NodeTools{ class NodeComponentControl;}
#define NodeFrinedClass() \
	friend class InputportLinkOutputPortInfo; \
	friend class NodeDirector;\
	friend class NodeStack;\
	friend class NodeRefLinkInfo;\
	friend class NodePortLinkInfo;\
	friend class NodePortLinkActionPair;\
	friend class NodeBuilderTools;\
	friend class NodeWidgetInfoTools;\
	friend class NodeRunInfo;\
	friend class NormalNodeEditorPropertyMenu;\
	friend class NodeTypeInfoSerializeion;\
	friend class NodeTypeInfo;\
	friend class PortTypeInfo;\
	friend class NodeInfoEditorDirector;\
	friend class NodeComponentControl;\
	friend class NodeRunLink;\
	friend class NodeInfoWidget;\
	friend class NodeRunLinkTools::Get;\
	friend class NodeTools::NodeComponentControl;\
	friend class PortLinkType
 
#endif // NODEFRINEDCLASS_H_H_HEAD__FILE__
