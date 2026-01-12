#ifndef MACRO_H_H_HEAD__FILE__
#define MACRO_H_H_HEAD__FILE__


#define AliasTypeNames(  _Type , ...) aliasTypeNames =std::vector< QString >( {typeid( _Type ).name(   ), __VA_ARGS__ } )
#define Stack_Type_Name( Def_var_value, _Type, ... ) typeName = #_Type;\
	AliasTypeNames(_Type,__VA_ARGS__ ); \
	setNewObjTypeFunction( [] {  \
		return new _Type{Def_var_value}; \
	} ); \
	setDeleteObjTypeFunction( [] ( void *delete_obj_ptr ) { \
		delete ( _Type * ) delete_obj_ptr; \
		return true; \
	} )

#endif // MACRO_H_H_HEAD__FILE__
