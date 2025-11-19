#ifndef VARGENERATE_H_H_HEAD__FILE__
#define VARGENERATE_H_H_HEAD__FILE__
#pragma once

#include <alias/type_alias.h>

#include <qt/enums/nodeItemEnum.h>

class I_Var;
class I_Stack;
class I_Type;
class NodeItem;
class I_IsType;
class I_Serialization‌;
class I_Conver;
class VarGenerate : public QObject {
	Q_OBJECT;
public:
	class NodeItemGenerate {
		std_shared_ptr< I_Type > type;
		QString name;
		QString dir;
		nodeItemEnum::Node_Item_Type enumType;
	public:
		virtual ~NodeItemGenerate( ) = default;
		NodeItemGenerate( const std_shared_ptr< I_Type > &var, const QString &name, const QString &dir, nodeItemEnum::Node_Item_Type enum_type )
			: type( var ),
			name( name ),
			dir( dir ),
			enumType( enum_type ) { }
		virtual bool isType( const QString &dir, const QString &name ) {
			return dir == this->dir && name == this->name;
		}
		virtual const std_shared_ptr< I_Type > & getType( ) const { return type; }
		virtual const QString & getName( ) const { return name; }
		virtual const QString & getDir( ) const { return dir; }
		virtual nodeItemEnum::Node_Item_Type getEnumType( ) const { return enumType; }
	};
public:
	/// @brief 节点排序类型
	using node_name_type_vector_pairt = std_vector_pairt< QString, std_shared_ptr< I_Type > >;
	using node_dir_type_vector_pairt = std_vector_pairt< QString, node_name_type_vector_pairt >;
	using node_enum_type_vector_pairt = std_pairt< nodeItemEnum::Node_Item_Type, node_dir_type_vector_pairt >;
	using Node_Type_Sort_Vector = std_vector< node_enum_type_vector_pairt >;
protected:
	/// @brief 转换列表
	std_vector< std_shared_ptr< I_Conver > > converVector;
	/// @brief 堆栈列表
	std_vector< std_shared_ptr< I_Stack > > stackVector;
	/// @brief 类型识别列表
	std_vector< std_shared_ptr< I_IsType > > isTypeVector;
	/// @brief 类型生成列表
	std_vector< std_shared_ptr< I_Type > > generateAnyTypeInfos;
	/// @brief 节点生成映射
	std_vector< std_shared_ptr< NodeItemGenerate > > generateNodeItemTypeInfos;
	/// @brief 排序后的节点
	Node_Type_Sort_Vector nodeItemSortMap;
protected:
	/// @brief 添加一个节点的排序对象
	/// @param enum_type 节点的枚举类
	/// @param dir_name 目录
	/// @param type_pro_name 原名
	/// @param type_ptr 类型指针
	/// @return 成功返回 true
	virtual bool appendSortMap( const nodeItemEnum::Node_Item_Type &enum_type, const QString &dir_name, const QString &type_pro_name, const std_shared_ptr< I_Type > &type_ptr );
public:
	/// @brief 追加一个类型生成器
	/// @param generate_var_type_info cpp 类型
	/// @param type_target_memory_size 类型占用量
	/// @param enum_type 节点类型
	/// @param dir_name 目录名称
	/// @param type_pro_name 原名称
	/// @param generate_var_name_vector 类型字符串别名
	/// @param generate_var_function 类型生成器
	/// @param release_var_function 释放函数
	virtual bool appendNodeItemGenerateInstance( const type_info &generate_var_type_info, const size_t &type_target_memory_size, const nodeItemEnum::Node_Item_Type &enum_type, const QString &dir_name, const QString &type_pro_name, const std_vector< QString > &generate_var_name_vector, const createFunction &generate_var_function, const releaseFunction &release_var_function );
	/// @brief 追加一个类型生成器
	/// @param generate_var_type_info cpp 类型
	/// @param type_target_memory_size 类型占用量
	/// @param type_pro_name 原名称
	/// @param generate_var_name_vector 类型字符串别名
	/// @param generate_var_function 类型生成器
	/// @param release_var_function 释放函数
	virtual bool appendVarTypeGenerateInstance( const type_info &generate_var_type_info, const size_t &type_target_memory_size, const QString &type_pro_name, const std_vector< QString > &generate_var_name_vector, const createFunction &generate_var_function, const releaseFunction &release_var_function );
	/// @brief 追加一个赋值类型对象
	/// @param new_conver 对象指针
	virtual void appendConverInstance( const std_shared_ptr< I_Conver > &new_conver ) {
		converVector.insert( converVector.begin( ), new_conver );
	}
	/// @brief 追加一个赋值类型对象
	/// @param new_stack 对象指针
	virtual void appendStackInstance( const std_shared_ptr< I_Stack > &new_stack ) {
		stackVector.insert( stackVector.begin( ), new_stack );
	}
	/// @brief 追加一个识别类型对象
	/// @param new_is_type 识别类型对象指针
	virtual void appendIsTypeInstance( const std_shared_ptr< I_IsType > &new_is_type ) {
		isTypeVector.insert( isTypeVector.begin( ), new_is_type );
	}
	~VarGenerate( ) override = default;
	/// @brief 校验是否支持左值与右值操作
	/// @param left_type_info 左值类型
	/// @param right_type_info 右值类型
	/// @param start_index 开始下标
	/// @return 不支持返回 false
	virtual bool supportType( const type_info &left_type_info, const type_info &right_type_info, size_t &start_index ) const;
	/// @brief 类型转换赋值
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @param start_index 开始下标
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool conver( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const;

	/// @brief 类型加法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @param start_index 开始下标
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool add( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const;

	/// @brief 类型减法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @param start_index 开始下标
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool sub( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const;

	/// @brief 类型乘法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @param start_index 开始下标
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool mul( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const;

	/// @brief 类型除法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @param start_index 开始下标
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool div( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, size_t &start_index ) const;

	/// @brief 右值是否等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @param start_index 开始下标
	/// @return 成功比较返回 true
	virtual bool equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const;
	/// @brief 右值是否大于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @param start_index 开始下标
	/// @return 成功比较返回 true
	virtual bool greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const;
	/// @brief 右值是否小于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @param start_index 开始下标
	/// @return 成功比较返回 true
	virtual bool lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const;
	/// @brief 右值是否大于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @param start_index 开始下标
	/// @return 成功比较返回 true
	virtual bool greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const;
	/// @brief 右值是否小于于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @param start_index 开始下标
	/// @return 成功比较返回 true
	virtual bool lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool, size_t &start_index ) const;

	/// @brief 存储序列化
	/// @param target_type_info 序列化对象类型
	/// @param target_ptr 序列化对象指针
	/// @param result_vector 返回二进制数据
	/// @param result_count 二进制数据的量
	/// @param start_index 开始下标
	/// @return 成功序列化返回 true
	virtual bool toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count, size_t &start_index ) const;

	/// @brief 加载序列化
	/// @param target_type_info 序列化当中实例化的对象类型
	/// @param target_ptr 序列化加载的返回指针
	/// @param result_count 使用数据量
	/// @param source_data_ptr 指向数据段的起始指针
	/// @param source_data_count 指向数据段的长度
	/// @param start_index 开始下标
	/// @return 成功使用数据返回 true
	virtual bool toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count, size_t &start_index ) const;

	/// @brief 获取类型的生成信息
	/// @param generate_type_name 类型名称
	/// @param result_info 返回生成函数与信息列表
	/// @param start_index 开始下标
	/// @return 失败返回 false
	virtual bool getTypeInfoGenerateInfo( const QString &generate_type_name, I_Type *&result_info, size_t &start_index ) const;

	/// @brief 获取类型的生成信息
	/// @param generate_type_info 类型
	/// @param result_info 返回字符串名称与生成函数
	/// @param start_index 开始下标
	/// @return 失败返回 false
	virtual bool getTypeInfoGenerateInfo( const type_info &generate_type_info, I_Type *&result_info, size_t &start_index ) const;

	/// @brief 获取类型的字符串形式
	/// @param check_type_info 类型识别
	/// @param check_type_data_ptr 识别对象指针
	/// @param check_type_data_count 检查对象指向内存的数量
	/// @param result_alias_name_list 返回别名列表
	/// @param start_index 开始下标
	/// @return true 表示成功
	virtual bool getCheckTypeNames( const QString &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_pairt< const I_Type *, std_vector< QString > > &result_alias_name_list, size_t &start_index ) const;
	/// @brief 获取类型的字符串形式
	/// @param check_type_info 检查的类型
	/// @param check_type_data_ptr 识别对象指针
	/// @param check_type_data_count 检查对象指向内存的数量
	/// @param result_type_string_name 返回的字符串名称 
	/// @param start_index 开始下标
	/// @return true 表示正确识别
	virtual bool getCheckTypeNames( const type_info &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_vector< QString > &result_type_string_name, size_t &start_index );

	/// @brief 创建匹配的类型
	/// @param check_type_info 创建的类型
	/// @param create_name 创建的类型名称
	/// @param create_is_right_call_back_function 创建成功时，会调用该函数，需要用户保存，并且返回 true，若返回 false，则自动释放
	/// @param start_index 开始下标
	/// @return 若成功创建并且调用create_is_right_call_back_function则返回 true（create_is_right_call_back_function 返回 false 时，仍然返回 true）
	virtual bool createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function, size_t &start_index ) const;

	/// @brief 校验是否支持左值与右值操作
	/// @param left_type_info 左值类型
	/// @param right_type_info 右值类型
	/// @return 不支持返回 false
	virtual bool supportType( const type_info &left_type_info, const type_info &right_type_info ) const {
		size_t index = 0;
		return supportType( left_type_info, right_type_info, index );
	}
	/// @brief 类型转换赋值
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool conver( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) const {
		size_t index = 0;
		return conver( left_type_info, left, right_type_info, right, index );
	}
	/// @brief 类型加法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool add( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) const {
		size_t index = 0;
		return add( left_type_info, left, right_type_info, right, index );
	}

	/// @brief 类型减法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool sub( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) const {
		size_t index = 0;
		return sub( left_type_info, left, right_type_info, right, index );
	}

	/// @brief 类型乘法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool mul( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) const {
		size_t index = 0;
		return mul( left_type_info, left, right_type_info, right, index );
	}

	/// @brief 类型除法
	/// @param left_type_info left 类型信息
	/// @param left 被赋值
	/// @param right_type_info right 类型信息
	/// @param right 赋值
	/// @return left 值被 right 改变时，返回 true。否则返回 false
	virtual bool div( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right ) const {
		size_t index = 0;
		return div( left_type_info, left, right_type_info, right, index );
	}

	/// @brief 右值是否等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool equThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) const {
		size_t index = 0;
		return equThanTarget( left_type_info, left, right_type_info, right, result_bool, index );
	}
	/// @brief 右值是否大于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) const {
		size_t index = 0;
		return greaterThanTarget( left_type_info, left, right_type_info, right, result_bool, index );
	}
	/// @brief 右值是否小于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) const {
		size_t index = 0;
		return lessThanTarget( left_type_info, left, right_type_info, right, result_bool, index );
	}
	/// @brief 右值是否大于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool greaterOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) const {
		size_t index = 0;
		return greaterOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool, index );
	}
	/// @brief 右值是否小于于等于左值
	/// @param left_type_info 左值类型
	/// @param left 左值指针
	/// @param right_type_info 右值类型
	/// @param right 右值指针
	/// @param result_bool 返回结果
	/// @return 成功比较返回 true
	virtual bool lessOrEquThanTarget( const type_info &left_type_info, void *left, const type_info &right_type_info, const void *right, bool *result_bool ) const {
		size_t index = 0;
		return lessOrEquThanTarget( left_type_info, left, right_type_info, right, result_bool, index );
	}

	/// @brief 存储序列化
	/// @param target_type_info 序列化对象类型
	/// @param target_ptr 序列化对象指针
	/// @param result_vector 返回二进制数据
	/// @param result_count 二进制数据的量
	/// @return 成功序列化返回 true
	virtual bool toBinVector( const type_info &target_type_info, const void *target_ptr, std_vector< uint8_t > &result_vector, size_t &result_count ) const {
		size_t index = 0;
		return toBinVector( target_type_info, target_ptr, result_vector, result_count, index );
	}

	/// @brief 加载序列化
	/// @param target_type_info 序列化当中实例化的对象类型
	/// @param target_ptr 序列化加载的返回指针
	/// @param result_count 使用数据量
	/// @param source_data_ptr 指向数据段的起始指针
	/// @param source_data_count 指向数据段的长度
	/// @return 成功使用数据返回 true
	virtual bool toOBjVector( const type_info &target_type_info, void *target_ptr, size_t &result_count, const uint8_t *source_data_ptr, const size_t &source_data_count ) const {
		size_t index = 0;
		return toOBjVector( target_type_info, target_ptr, result_count, source_data_ptr, source_data_count, index );
	}

	/// @brief 获取类型的生成信息
	/// @param generate_type_name 类型名称
	/// @param result_info 返回生成函数与信息列表
	/// @return 失败返回 false
	virtual bool getTypeInfoGenerateInfo( const QString &generate_type_name, I_Type * &result_info ) const {
		size_t index = 0;
		return getTypeInfoGenerateInfo( generate_type_name, result_info, index );
	}

	/// @brief 获取类型的生成信息
	/// @param generate_type_info 类型
	/// @param result_info 返回字符串名称与生成函数
	/// @return 失败返回 false
	virtual bool getTypeInfoGenerateInfo( const type_info &generate_type_info, I_Type * &result_info ) const {
		size_t index = 0;
		return getTypeInfoGenerateInfo( generate_type_info, result_info, index );
	}
	/// @brief 获取类型的字符串形式
	/// @param check_type_info 类型识别
	/// @param check_type_data_ptr 识别对象指针
	/// @param check_type_data_count 检查对象指向内存的数量
	/// @param result_alias_name_list 返回别名列表
	/// @return true 表示成功
	virtual bool getCheckTypeNames( const QString &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_pairt< const I_Type *, std_vector< QString > > &result_alias_name_list ) const {
		size_t index = 0;
		return getCheckTypeNames( check_type_info, check_type_data_ptr, check_type_data_count, result_alias_name_list, index );
	}
	/// @brief 获取类型的字符串形式
	/// @param check_type_info 检查的类型
	/// @param check_type_data_ptr 识别对象指针
	/// @param check_type_data_count 检查对象指向内存的数量
	/// @param result_type_string_name 返回的字符串名称 
	/// @return true 表示正确识别
	virtual bool getCheckTypeNames( const type_info &check_type_info, const uint8_t *check_type_data_ptr, const size_t &check_type_data_count, std_vector< QString > &result_type_string_name ) {
		size_t index = 0;
		return getCheckTypeNames( check_type_info, check_type_data_ptr, check_type_data_count, result_type_string_name, index );
	}

	/// @brief 创建匹配的类型
	/// @param check_type_info 创建的类型
	/// @param create_name 创建的类型名称
	/// @param create_is_right_call_back_function 创建成功时，会调用该函数，需要用户保存，并且返回 true，若返回 false，则自动释放
	/// @return 若成功创建并且调用create_is_right_call_back_function则返回 true（create_is_right_call_back_function 返回 false 时，仍然返回 true）
	virtual bool createCheckTypeName( const type_info &check_type_info, const QString &create_name, const std_function< bool( I_Var *create_var_ptr ) > &create_is_right_call_back_function ) const {
		size_t index = 0;
		return createCheckTypeName( check_type_info, create_name, create_is_right_call_back_function, index );
	}
	/// @brief 创建节点
	/// @param dir_name 目录名称
	/// @param class_name 类名称
	/// @return 节点
	virtual NodeItem * createNodeItem( const QString &dir_name, const QString &class_name );
	/// @brief 获取所有支持节点列表
	/// @return 节点列表
	virtual const std_vector< std_shared_ptr< NodeItemGenerate > > & getGenerateNodeItemTypeInfos( ) const { return generateNodeItemTypeInfos; }
	virtual const Node_Type_Sort_Vector & getNodeItemSortMap( ) const { return nodeItemSortMap; }
	/// @brief 增加一个类型赋值对象
	/// @tparam ttype 赋值对象类型
	template< typename ttype >
		requires requires ( ttype *ptr, I_Conver *base_ptr ) {
			base_ptr = ptr;
		}
	void appendConverInstance( ) {
		appendConverInstance( std_shared_ptr< I_Conver >( new ttype ) );
	}

	/// @brief 增加一个类型赋值对象
	/// @tparam ttype 赋值对象类型
	template< typename ttype >
		requires requires ( ttype *ptr, I_Stack *base_ptr ) {
			base_ptr = ptr;
		}
	void appendStackInstance( ) {
		appendStackInstance( std_shared_ptr< I_Stack >( new ttype ) );
	}

	/// @brief 增加一个类型赋值对象
	/// @tparam ttype 赋值对象类型
	template< typename ttype >
		requires requires ( ttype *ptr, I_IsType *base_ptr ) {
			base_ptr = ptr;
		}
	void appendIsTypeInstance( ) {
		appendIsTypeInstance( std_shared_ptr< I_IsType >( new ttype ) );
	}

	/// @brief 追加一个类型生成器
	/// @param type_pro_name 原生名称
	/// @param generate_var_name_vector 类型字符串别名
	/// @param generate_var_function 类型生成器
	/// @param release_var_function 释放器
	template< typename ttype >
	bool appendVarTypeGenerateInstance( const QString &type_pro_name, const std_vector< QString > &generate_var_name_vector, const createFunction &generate_var_function, const releaseFunction &release_var_function ) {
		const type_info &typeInfo = typeid( ttype );
		return appendVarTypeGenerateInstance( typeInfo, sizeof( ttype ), type_pro_name, generate_var_name_vector, generate_var_function, release_var_function );
	}

	/// @brief 追加一个类型生成器
	/// @param release_var_function 释放器
	/// @param type_pro_name 原生名称
	/// @param generate_var_name_vector 类型字符串别名
	template< typename ttype >
	bool appendVarTypeGenerateInstance( const QString &type_pro_name, const std_vector< QString > &generate_var_name_vector, const releaseFunction &release_var_function ) {
		const type_info &typeInfo = typeid( ttype );
		createFunction generate_var_function = []( ) {
			return new ttype( );
		};
		return appendVarTypeGenerateInstance( typeInfo, sizeof( ttype ), type_pro_name, generate_var_name_vector, generate_var_function, release_var_function );
	}

	/// @brief 追加一个类型生成器
	/// @param type_pro_name 原生名称
	/// @param generate_var_name_vector 类型字符串别名
	template< typename ttype >
	bool appendVarTypeGenerateInstance( const QString &type_pro_name, const std_vector< QString > &generate_var_name_vector ) {
		const type_info &typeInfo = typeid( ttype );
		createFunction generate_var_function = []( ) {
			return new ttype( );
		};
		releaseFunction release_var_function = [] ( void *p ) {
			delete ( ttype * ) p;
		};
		return appendVarTypeGenerateInstance( typeInfo, sizeof( ttype ), type_pro_name, generate_var_name_vector, generate_var_function, release_var_function );
	}

	/// @brief 追加一个类型生成器
	/// @param type_pro_name 原生名称
	template< typename ttype >
	bool appendVarTypeGenerateInstance( const QString &type_pro_name ) {
		const type_info &typeInfo = typeid( ttype );
		createFunction generate_var_function = []( ) {
			return new ttype( );
		};
		releaseFunction release_var_function = [] ( void *p ) {
			delete ( ttype * ) p;
		};
		return appendVarTypeGenerateInstance( typeInfo, sizeof( ttype ), type_pro_name, { }, generate_var_function, release_var_function );
	}
	/// @brief 追加一个类型生成器
	/// @param generate_var_name_vector 类型字符串别名
	template< typename ttype >
	bool appendVarTypeGenerateInstance( const std_vector< QString > &generate_var_name_vector ) {
		const type_info &typeInfo = typeid( ttype );
		createFunction generate_var_function = []( ) {
			return new ttype( );
		};
		releaseFunction release_var_function = [] ( void *p ) {
			delete ( ttype * ) p;
		};
		return appendVarTypeGenerateInstance( typeInfo, sizeof( ttype ), typeInfo.name( ), generate_var_name_vector, generate_var_function, release_var_function );
	}
	/// @brief 追加一个类型生成器
	template< typename ttype >
	bool appendVarTypeGenerateInstance( ) {
		const type_info &typeInfo = typeid( ttype );
		createFunction generate_var_function = []( ) {
			return new ttype( );
		};
		releaseFunction release_var_function = [] ( void *p ) {
			delete ( ttype * ) p;
		};
		return appendVarTypeGenerateInstance( typeInfo, sizeof( ttype ), typeInfo.name( ), { }, generate_var_function, release_var_function );
	}

	/// @brief 追加一个类型生成器
	/// @param generate_var_name_vector 类型字符串别名
	template< typename ttype >
		requires requires ( NodeItem *p, ttype *tp ) {
			p = tp;
		}
	bool appendNodeItemGenerateInstance( const std_vector< QString > &generate_var_name_vector ) {

		auto &typeInfo = typeid( ttype );
		auto memorySize = sizeof( ttype );
		QString dirName = ttype::getStaticMetaObjectDir( );
		QString objName = ttype::getStaticMetaObjectName( );
		nodeItemEnum::Node_Item_Type enumType = ttype::getStaticMetaNodeType( );
		createFunction generateVarFunction = []( ) {
			return new ttype( );
		};
		releaseFunction releaseVarFunction = [] ( void *p ) {
			delete ( ttype * ) p;
			return true;
		};
		return appendNodeItemGenerateInstance( typeInfo, memorySize, enumType, dirName, objName, generate_var_name_vector, generateVarFunction, releaseVarFunction );
	}

	/// @brief 追加一个类型生成器
	template< typename ttype >
		requires requires ( NodeItem *p, ttype *tp ) {
			p = tp;
		}
	bool appendNodeItemGenerateInstance( ) {
		return appendNodeItemGenerateInstance< ttype >( { } );
	}
	//template< typename TType >
	//std_shared_ptr< I_Var > createType( const QString &var_name ) {
	//	auto typePtr = new I_Type(
	//		typeid( TType ),
	//		sizeof( TType ),
	//		[] ( void *p ) {
	//			delete ( TType * ) p;
	//			return true;
	//		},
	//		[]( ) ->void * {
	//			return new TType( );
	//		} );
	//	std_shared_ptr< I_Var > result( new I_Var( typePtr, var_name ) );
	//	return result;
	//}

};

#endif // VARGENERATE_H_H_HEAD__FILE__
