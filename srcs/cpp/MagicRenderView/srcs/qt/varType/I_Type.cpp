#include "./I_Type.h"

#include "I_Stack.h"

I_Type::I_Type( const std_shared_ptr< I_Stack > &create_obj_stack, void *var_p ) : createObjStack( create_obj_stack ), typeInfo( create_obj_stack.get( )->getGenerateTypeInfo( ) ), p( var_p ) {

}
I_Type::~I_Type( ) {
	createObjStack->deleteTarget( typeInfo, p );
}
