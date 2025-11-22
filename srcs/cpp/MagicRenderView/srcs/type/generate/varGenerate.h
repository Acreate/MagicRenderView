#ifndef VARGENERATE_H_H_HEAD__FILE__
#define VARGENERATE_H_H_HEAD__FILE__
#pragma once
#include <qstring.h>
#include <vector>
class InfoStack;
class VarGenerate {
protected:
	std::vector< InfoStack * > stacksUnityVector;
	std::vector< InfoStack * > stacksVectorVector;
	std::vector< InfoStack * > stacksListVector;
	std::vector< InfoStack * > stacksVectorPairtVector;
	std::vector< InfoStack * > stacksListPairtVector;
protected:
	virtual void realeaseStackVector( std::vector< InfoStack * > &clear_redundancy_vector );
public:
	VarGenerate( );
	virtual ~VarGenerate( );
protected:
	virtual void * create( const std::vector< InfoStack * > &stacks_vector, const QString &type_name );
	virtual void * createAtUnityObjPtr( const QString &type_name );
	virtual void * createAtVectorObjPtr( const QString &type_name );
	virtual void * createAtListObjPtr( const QString &type_name );
	virtual bool realease( const std::vector< InfoStack * > &clear_redundancy_vector, const void *delete_obj_ptr );
	virtual bool getTypeName( const std::vector< InfoStack * > &clear_redundancy_vector, const QString &type_info_name, QString &result_type_name );
	virtual bool getTypeName( const type_info &type_info_ref, QString &result_type_name );
	virtual void clearRedundancy( );
	virtual void clearRedundancy( std::vector< InfoStack * > &clear_redundancy_vector );
public:
	virtual std::vector< std::pair< void *, void * > > * createAtVectorAnyPairtObjPtr( );
	virtual std::list< std::pair< void *, void * > > * createAtListAnyPairtObjPtr( );
	virtual bool realease( const void *delete_obj_ptr );
	template< typename TTypeName >
	TTypeName * createAtUnityObjPtr( ) {
		auto resultPtr = createAtUnityObjPtr( typeid( TTypeName ).name( ) );
		if( resultPtr == nullptr )
			return nullptr;
		return ( TTypeName * ) resultPtr;
	}
	template< typename TTypeName >
	std::vector< TTypeName > * createAtVectorObjPtr( ) {
		auto resultPtr = createAtVectorObjPtr( typeid( std::vector< TTypeName > ).name( ) );
		if( resultPtr == nullptr )
			return nullptr;
		return ( std::vector< TTypeName > * ) resultPtr;
	}
	template< typename TTypeName >
	std::list< TTypeName > * createAtListObjPtr( ) {
		auto resultPtr = createAtListObjPtr( typeid( std::list< TTypeName > ).name( ) );
		if( resultPtr == nullptr )
			return nullptr;
		return ( std::list< TTypeName > * ) resultPtr;
	}
	template< typename TTypeName >
	bool getTypeName( QString &result_type_name ) {
		return getTypeName( typeid( TTypeName ), result_type_name );
	}
};
#define Type_Name_Unity( Type_Name ) #Type_Name
#define Type_Name_Vector( Type_Name ) "vector<" Type_Name_Unity(Type_Name) ">"
#define Type_Name_List( Type_Name ) "list<" Type_Name_Unity(Type_Name) ">"
#endif // VARGENERATE_H_H_HEAD__FILE__
