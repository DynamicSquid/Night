#pragma once

#include "lexer.hpp"
#include "token.hpp"
#include "stmt.hpp"

#include <memory>
#include <tuple>
#include <vector>
#include <string>
#include <unordered_set>
#include <functional>

#define NIGHT_COMPILE_ERROR(msg, fix, link) \
	night::error(Location{ __FILE__, __LINE__ }, night::error_compile, lexer.get_loc(), msg, fix, link)

class Parser
{
private:
	struct CheckVariable;
	struct Type;
public:
	using ParserScope = Scope<CheckVariable>;
	using TypeContainer = std::unordered_multiset<Type>;

public:
	Parser(
		Lexer& lexer
	);

public:
	Stmt parse_statement(
		ParserScope& scope
	);

private:
	/*
	 * parses body that precedes a statement
	 *   ex. body of conditionals, loops, or functions
	 *
	 * lexer should be at token before body; ends at last token of body
	 */
	std::vector<Stmt> parse_body(
		ParserScope& scope,
		std::string const& stmt_name,
		std::string const& stmt_format,
		std::string const& stmt_learn
	);

	/*
	 * parses condition
	 *   ex. conditionals or loops
	 * 
	 * lexer should be at token before opening bracket; ends at closing bracket
	 */
	std::shared_ptr<ExprNode> parse_condition(
		ParserScope& scope,
		std::string const& stmt_name,
		std::string const& stmt_format,
		std::string const& stmt_learn
	);

	// starts at first argument token
	// ends at close bracket
	auto parse_arguments(
		ParserScope& scope,
		std::string const& func_name
	);

	// starts at token before expression
	// ends at the first non-expression token
	std::tuple<std::shared_ptr<ExprNode>, TypeContainer> parse_expression(
		ParserScope& scope,
		TypeContainer const& required_types = {}
	);

	bool higher_precedence(
		std::string const& op1,
		std::string const& op2) const;

	TypeContainer type_check_expr(
		ParserScope& scope,
		std::shared_ptr<ExprNode> const& expr,
		TypeContainer const& required_types = {}
	) const;

	void check_call_types(
		std::vector<TypeContainer> const& param_types,
		std::vector<TypeContainer> const& arg_types,
		std::string const& func_name
	);

	std::string types_as_str(
		TypeContainer const& var_types_set
	) const;

public:
	struct CheckVariable;

private:
	struct CheckFunction;
	struct CheckClass;

	using CheckVariableContainer = std::unordered_map<std::string, CheckVariable>;
	using CheckFunctionContainer = std::unordered_map<std::string, CheckFunction>;
	using CheckClassContainer	 = std::unordered_map<std::string, CheckClass>;

private:
	Lexer& lexer;

public:
	static TypeContainer const all_types;

	CheckFunctionContainer check_funcs;
	CheckClassContainer check_classes;

private:
	struct CheckVariable
	{
		// a note about parameters:
		/*
		// to perform type checking, parameters' types must be evaluated when the
		// function is defined
		//
		// they are stored in the same container as normal variables, so the only
		// difference is that they don't have a type
		//
		// they can be differentiated from normal variables using the method:
		// 'needs_types()'
		//
		// their types are giving to them through the expressions they encounter,
		// for example 'param || true' would mean 'param' is a boolean
		//
		// if a parameter still doesn't have a type at the end of the function,
		// then it is given all the types
		//
		// once a parameter has types, it then behaves like a normal variable
		*/
		TypeContainer types;
	};

	struct CheckFunction
	{
		std::vector<TypeContainer> param_types;

		// a note about return types:
		/*
		// function return types have to be deduced when they are defined
		//
		// this is done by examining the return statement(s) of the function
		//
		// if no return types can be deduced, then the return type is treated as
		// whatever type is required for it to be
		*/
		TypeContainer rtn_types;

		bool is_void;
	};

	struct CheckClass
	{
		CheckVariableContainer vars;
		CheckFunctionContainer methods;
	};

	std::pair<std::string const, CheckFunction> make_check_function(
		std::string const& name,

		std::vector<TypeContainer> const& params = {},
		TypeContainer const& rtn_types = {}
	);

	std::pair<std::string const, CheckClass> make_check_class(
		std::string const& name,

		CheckVariableContainer const& vars,
		CheckFunctionContainer const& methods
	);


	struct Type
	{
		enum T {
			BOOL,
			INT, FLOAT,
			STR, ARR
		} const type;

		Type(T _type);
		Type(T _type, TypeContainer const& _elem_types);

		std::string to_str() const;

		TypeContainer const elem_types;
	};
};