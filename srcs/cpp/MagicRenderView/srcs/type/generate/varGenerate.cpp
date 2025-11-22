#include "varGenerate.h"

#include "infoStackGenerate.h"

#include <type/stack/infoStack.h>

#define Generate_InfoStack_Unity( Target_Stack_Obj, Fill_Ptr, Def_Var, Type_Name_, ...) \
	Fill_Ptr = InfoStackGenerate::generateInfoStack( \
 			Type_Name_Unity(Type_Name_), \
			{ typeid(Type_Name_).name( ), __VA_ARGS__ }, \
			[] { return new Type_Name_( Def_Var ); }, \
			[] ( void *p ) { delete ( Type_Name_ * ) p; } ); \
	if( Fill_Ptr )\
		Target_Stack_Obj.emplace_back( Fill_Ptr );

#define Generate_InfoStack_Vector( Target_Stack_Obj, Fill_Ptr, Type_Name_, ...) \
	Fill_Ptr = InfoStackGenerate::generateInfoStack( \
 			Type_Name_Vector(Type_Name_), \
			{ typeid(std::vector<Type_Name_>).name( ), __VA_ARGS__ }, \
			[] { return new std::vector<Type_Name_>(  ); }, \
			[] ( void *p ) { delete ( std::vector<Type_Name_> * ) p; } ); \
	if( Fill_Ptr )\
		Target_Stack_Obj.emplace_back( Fill_Ptr );

#define Generate_InfoStack_List( Target_Stack_Obj, Fill_Ptr, Type_Name_, ...) \
	Fill_Ptr = InfoStackGenerate::generateInfoStack( \
 			Type_Name_List(Type_Name_), \
			{ typeid(std::list<Type_Name_>).name( ), __VA_ARGS__ }, \
			[] { return new std::list<Type_Name_>(  ); }, \
			[] ( void *p ) { delete ( std::list<Type_Name_> * ) p; } ); \
	if( Fill_Ptr )\
		Target_Stack_Obj.emplace_back( Fill_Ptr );

#define Generate_InfoStack_Vector_Pair( Target_Stack_Obj, Fill_Ptr, ...) \
	Fill_Ptr = InfoStackGenerate::generateInfoStack( \
 			"vector<pair<void*,void*>>", \
			{ typeid(std::vector<std::pair<void*,void*>>).name( ), __VA_ARGS__ }, \
			[] { return new std::vector<std::pair<void*,void*>>(  ); }, \
			[] ( void *p ) { delete ( std::vector<std::pair<void*,void*>> * ) p; } ); \
	if( Fill_Ptr )\
		Target_Stack_Obj.emplace_back( Fill_Ptr );

#define Generate_InfoStack_List_Pair( Target_Stack_Obj, Fill_Ptr, ...) \
	Fill_Ptr = InfoStackGenerate::generateInfoStack( \
 			"list<pair<void*,void*>>", \
			{ typeid(std::list<std::pair<void*,void*>>).name( ), __VA_ARGS__ }, \
			[] { return new std::list<std::pair<void*,void*>>(  ); }, \
			[] ( void *p ) { delete ( std::list<std::pair<void*,void*>> * ) p; } ); \
	if( Fill_Ptr )\
		Target_Stack_Obj.emplace_back( Fill_Ptr );

VarGenerate::VarGenerate( ) {
	InfoStack *generateInfoStack;
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, int64_t );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, int32_t );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, int16_t );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, int8_t, Type_Name_Unity(char), Type_Name_Unity(data) );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, uint64_t, Type_Name_Unity(size_t) );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, uint32_t );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, uint16_t );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, uint8_t, Type_Name_Unity(uchar), Type_Name_Unity(uData) );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0, bool, Type_Name_Unity(boolean), Type_Name_Unity(bin) );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0.0f, float, Type_Name_Unity(float32_f) );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, 0.0, double, Type_Name_Unity(float64_f) );
	Generate_InfoStack_Unity( stacksUnityVector, generateInfoStack, "", QString );

	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, int64_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, int32_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, int16_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, int8_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, uint64_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, uint32_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, uint16_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, uint8_t );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, float );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, double );
	Generate_InfoStack_Vector( stacksVectorVector, generateInfoStack, QString );

	Generate_InfoStack_List( stacksListVector, generateInfoStack, int64_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, int32_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, int16_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, int8_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, uint64_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, uint32_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, uint16_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, uint8_t );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, float );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, double );
	Generate_InfoStack_List( stacksListVector, generateInfoStack, QString );

	Generate_InfoStack_Vector_Pair( stacksVectorPairtVector, generateInfoStack );
	Generate_InfoStack_List_Pair( stacksListPairtVector, generateInfoStack );
	clearRedundancy( );
}
void VarGenerate::realeaseStackVector( std::vector< InfoStack * > &clear_redundancy_vector ) {
	size_t count = clear_redundancy_vector.size( );
	auto arrayPtr = clear_redundancy_vector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		delete arrayPtr[ index ];
	clear_redundancy_vector.clear( );
}
VarGenerate::~VarGenerate( ) {
	realeaseStackVector( stacksUnityVector );
	realeaseStackVector( stacksVectorVector );
	realeaseStackVector( stacksListVector );
	realeaseStackVector( stacksVectorPairtVector );
	realeaseStackVector( stacksListPairtVector );
}
void * VarGenerate::create( const std::vector< InfoStack * > &stacks_vector, const QString &type_name ) {
	size_t count = stacks_vector.size( );
	auto arrayPtr = stacks_vector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->getTypeName( ) == type_name )
			return arrayPtr[ index ]->createTypePtr( );
	index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isAliasTypeNames( type_name ) )
			return arrayPtr[ index ]->createTypePtr( );
	return nullptr;
}
void * VarGenerate::createAtUnityObjPtr( const QString &type_name ) {
	return create( stacksUnityVector, type_name );
}
void * VarGenerate::createAtVectorObjPtr( const QString &type_name ) {
	return create( stacksVectorVector, type_name );
}
void * VarGenerate::createAtListObjPtr( const QString &type_name ) {
	return create( stacksListVector, type_name );
}
bool VarGenerate::realease( const std::vector< InfoStack * > &clear_redundancy_vector, const void *delete_obj_ptr ) {
	size_t count = clear_redundancy_vector.size( );
	auto arrayPtr = clear_redundancy_vector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->deleteTypePtr( delete_obj_ptr ) )
			return true;
	return false;
}
bool VarGenerate::getTypeName( const std::vector< InfoStack * > &clear_redundancy_vector, const QString &type_info_name, QString &result_type_name ) {
	size_t count = clear_redundancy_vector.size( );
	auto arrayPtr = clear_redundancy_vector.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->getTypeName( ) == type_info_name ) {
			result_type_name = arrayPtr[ index ]->getTypeName( );
			return true;
		}
	index = 0;
	for( ; index < count; ++index )
		if( arrayPtr[ index ]->isAliasTypeNames( type_info_name ) ) {
			result_type_name = arrayPtr[ index ]->getTypeName( );
			return true;
		}
	return false;
}
bool VarGenerate::getTypeName( const type_info &type_info_ref, QString &result_type_name ) {
	QString typeInfoName = type_info_ref.name( );
	if( getTypeName( stacksUnityVector, typeInfoName, result_type_name ) )
		return true;
	if( getTypeName( stacksVectorVector, typeInfoName, result_type_name ) )
		return true;
	if( getTypeName( stacksListVector, typeInfoName, result_type_name ) )
		return true;
	if( getTypeName( stacksVectorPairtVector, typeInfoName, result_type_name ) )
		return true;
	if( getTypeName( stacksListPairtVector, typeInfoName, result_type_name ) )
		return true;
	return false;
}

std::vector< std::pair< void *, void * > > * VarGenerate::createAtVectorAnyPairtObjPtr( ) {
	size_t count = stacksVectorPairtVector.size( );
	if( count == 0 )
		return nullptr;
	return ( std::vector< std::pair< void *, void * > > * ) stacksVectorPairtVector.data( )[ 0 ]->createTypePtr( );
}
std::list< std::pair< void *, void * > > * VarGenerate::createAtListAnyPairtObjPtr( ) {
	size_t count = stacksListPairtVector.size( );
	if( count == 0 )
		return nullptr;
	return ( std::list< std::pair< void *, void * > > * ) stacksListPairtVector.data( )[ 0 ]->createTypePtr( );
}
bool VarGenerate::realease( const void *delete_obj_ptr ) {
	if( realease( stacksUnityVector, delete_obj_ptr ) )
		return true;
	if( realease( stacksVectorVector, delete_obj_ptr ) )
		return true;
	if( realease( stacksListVector, delete_obj_ptr ) )
		return true;
	if( realease( stacksVectorPairtVector, delete_obj_ptr ) )
		return true;
	if( realease( stacksListPairtVector, delete_obj_ptr ) )
		return true;
	return false;
}
void VarGenerate::clearRedundancy( ) {
	clearRedundancy( stacksUnityVector );
	clearRedundancy( stacksVectorVector );
	clearRedundancy( stacksListVector );
	clearRedundancy( stacksVectorPairtVector );
	clearRedundancy( stacksListPairtVector );
}
void VarGenerate::clearRedundancy( std::vector< InfoStack * > &clear_redundancy_vector ) {
	size_t count = clear_redundancy_vector.size( );
	std::vector< InfoStack * > buff( count );
	auto arrayPtr = clear_redundancy_vector.data( );
	size_t index = 0;
	size_t subIndex;
	size_t buffIndex = 0;
	auto buffArrayPtr = buff.data( );
	for( ; index < count; ++index ) {
		auto &checkTypeName = arrayPtr[ index ]->getTypeName( );
		for( subIndex = index + 1; subIndex < count; ++subIndex )
			if( arrayPtr[ subIndex ]->isType( checkTypeName ) )
				break;
		if( subIndex != count ) {
			delete arrayPtr[ index ];
			continue;
		}
		buffArrayPtr[ buffIndex ] = arrayPtr[ index ];
		buffIndex += 1;
	}
	buff.resize( buffIndex );
	clear_redundancy_vector = buff;
}
