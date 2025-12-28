#ifndef NODETYPEINFO_H_H_HEAD__FILE__
#define NODETYPEINFO_H_H_HEAD__FILE__
#pragma once
#include <cstdint>
#include <QString>

class PortTypeInfo;
class Node;
class NodeTypeInfo {
	friend class NodeTypeInfoSerializeion;
	friend class NodeTypeInfoStack;
protected:
	QString nodeName;
	uint64_t nodeGeneratorCode;
	int32_t posX;
	int32_t posY;
	std::vector< PortTypeInfo * > portLinkInfoVector;
public:
	NodeTypeInfo( ) { }
	virtual ~NodeTypeInfo( );
	virtual bool load( Node *node_ptr );
	virtual const QString & getNodeName( ) const { return nodeName; }
	virtual uint64_t getNodeGeneratorCode( ) const { return nodeGeneratorCode; }
	virtual int32_t getPosX( ) const { return posX; }
	virtual int32_t getPosY( ) const { return posY; }
	virtual const std::vector< PortTypeInfo * > & getPortLinkInfoVector( ) const { return portLinkInfoVector; }
};

#endif // NODETYPEINFO_H_H_HEAD__FILE__
