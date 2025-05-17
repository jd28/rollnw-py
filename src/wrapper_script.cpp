#include "casters.hpp"
#include "opaque_types.hpp"

#include <nw/resources/ResourceManager.hpp>
#include <nw/script/Nss.hpp>
#include <nw/script/NssLexer.hpp>
#include <nw/script/Token.hpp>

#include <nanobind/make_iterator.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <string>

namespace nb = nanobind;
namespace nws = nw::script;

using namespace std::literals;

void init_script(nb::module_& nw)
{
    nb::class_<nws::SourcePosition>(nw, "SourcePosition")
        .def_rw("line", &nws::SourcePosition::line)
        .def_rw("column", &nws::SourcePosition::column);

    nb::class_<nws::SourceRange>(nw, "SourceRange")
        .def(nb::init<>())
        .def_ro("start", &nws::SourceRange::start)
        .def_ro("end", &nws::SourceRange::end);

    nb::class_<nws::SourceLocation>(nw, "SourceLocation")
        .def("length", &nws::SourceLocation::length)
        .def("view", &nws::SourceLocation::view)
        .def_ro("range", &nws::SourceLocation::range);

    nb::enum_<nws::SymbolKind>(nw, "SymbolKind")
        .value("variable", nws::SymbolKind::variable)
        .value("function", nws::SymbolKind::function)
        .value("type", nws::SymbolKind::type)
        .value("param", nws::SymbolKind::param)
        .value("field", nws::SymbolKind::field);

    nb::class_<nws::Symbol>(nw, "Symbol")
        .def_ro("node", &nws::Symbol::node)
        .def_ro("decl", &nws::Symbol::decl)
        .def_ro("comment", &nws::Symbol::comment)
        .def_ro("type", &nws::Symbol::type)
        .def_ro("kind", &nws::Symbol::kind)
        .def_ro("provider", &nws::Symbol::provider, nb::rv_policy::reference_internal)
        .def_ro("view", &nws::Symbol::view);

    nb::class_<nws::InlayHint>(nw, "InlayHint")
        .def_ro("message", &nws::InlayHint::message)
        .def_ro("position", &nws::InlayHint::position);

    nb::class_<nws::SignatureHelp>(nw, "SignatureHelp")
        .def_ro("decl", &nws::SignatureHelp::decl)
        .def_ro("expr", &nws::SignatureHelp::expr)
        .def_ro("active_param", &nws::SignatureHelp::active_param);

    nb::class_<nws::Context>(nw, "Context")
        .def(nb::init<>())
        .def(nb::init<std::vector<std::string>>())
        .def(nb::init<std::vector<std::string>, std::string>())
        .def("add_include_path", &nws::Context::add_include_path)
        .def("command_script", &nws::Context::command_script, nb::rv_policy::reference_internal)
        .def("get", &nws::Context::get, nb::rv_policy::reference_internal, nb::arg("resref"), nb::arg("is_command_script") = false);

    nb::enum_<nw::script::DiagnosticType>(nw, "DiagnosticType")
        .value("lexical", nws::DiagnosticType::lexical)
        .value("parse", nws::DiagnosticType::parse)
        .value("semantic", nws::DiagnosticType::semantic);

    nb::enum_<nw::script::DiagnosticSeverity>(nw, "DiagnosticSeverity")
        .value("error", nws::DiagnosticSeverity::error)
        .value("hint", nws::DiagnosticSeverity::hint)
        .value("information", nws::DiagnosticSeverity::information)
        .value("warning", nws::DiagnosticSeverity::warning);

    nb::class_<nws::Diagnostic>(nw, "Diagnostic")
        .def_ro("type", &nws::Diagnostic::type)
        .def_ro("severity", &nws::Diagnostic::severity)
        .def_ro("script", &nws::Diagnostic::script)
        .def_ro("message", &nws::Diagnostic::message)
        .def_ro("location", &nws::Diagnostic::location);

    nb::enum_<nws::NssTokenType>(nw, "NssTokenType")
        .value("INVALID", nws::NssTokenType::INVALID)
        .value("END", nws::NssTokenType::END)
        // Identifier
        .value("IDENTIFIER", nws::NssTokenType::IDENTIFIER)
        // Punctuation
        .value("LPAREN", nws::NssTokenType::LPAREN)       // (
        .value("RPAREN", nws::NssTokenType::RPAREN)       // )
        .value("LBRACE", nws::NssTokenType::LBRACE)       // {
        .value("RBRACE", nws::NssTokenType::RBRACE)       // }
        .value("LBRACKET", nws::NssTokenType::LBRACKET)   // [
        .value("RBRACKET", nws::NssTokenType::RBRACKET)   // ]
        .value("COMMA", nws::NssTokenType::COMMA)         //
        .value("COLON", nws::NssTokenType::COLON)         // :
        .value("QUESTION", nws::NssTokenType::QUESTION)   // ?
        .value("SEMICOLON", nws::NssTokenType::SEMICOLON) // ;
        .value("POUND", nws::NssTokenType::POUND)         // #
        .value("DOT", nws::NssTokenType::DOT)             // .
        // Operators
        .value("AND", nws::NssTokenType::AND)               // '&'
        .value("ANDAND", nws::NssTokenType::ANDAND)         // &&
        .value("ANDEQ", nws::NssTokenType::ANDEQ)           // &=
        .value("DIV", nws::NssTokenType::DIV)               // /
        .value("DIVEQ", nws::NssTokenType::DIVEQ)           // /=
        .value("EQ", nws::NssTokenType::EQ)                 // =
        .value("EQEQ", nws::NssTokenType::EQEQ)             // ==
        .value("GT", nws::NssTokenType::GT)                 // >
        .value("GTEQ", nws::NssTokenType::GTEQ)             // >=
        .value("LT", nws::NssTokenType::LT)                 // <
        .value("LTEQ", nws::NssTokenType::LTEQ)             // <=
        .value("MINUS", nws::NssTokenType::MINUS)           // -
        .value("MINUSEQ", nws::NssTokenType::MINUSEQ)       // -=
        .value("MINUSMINUS", nws::NssTokenType::MINUSMINUS) // --
        .value("MOD", nws::NssTokenType::MOD)               // %
        .value("MODEQ", nws::NssTokenType::MODEQ)           // %=
        .value("TIMES", nws::NssTokenType::TIMES)           // *
        .value("TIMESEQ", nws::NssTokenType::TIMESEQ)       // *=
        .value("NOT", nws::NssTokenType::NOT)               // !
        .value("NOTEQ", nws::NssTokenType::NOTEQ)           // !=
        .value("OR", nws::NssTokenType::OR)                 // '|'
        .value("OREQ", nws::NssTokenType::OREQ)             // |=
        .value("OROR", nws::NssTokenType::OROR)             // ||
        .value("PLUS", nws::NssTokenType::PLUS)             // +
        .value("PLUSEQ", nws::NssTokenType::PLUSEQ)         // +=
        .value("PLUSPLUS", nws::NssTokenType::PLUSPLUS)     // ++
        .value("SL", nws::NssTokenType::SL)                 // <<
        .value("SLEQ", nws::NssTokenType::SLEQ)             // <<=
        .value("SR", nws::NssTokenType::SR)                 // >>
        .value("SREQ", nws::NssTokenType::SREQ)             // >>=
        .value("TILDE", nws::NssTokenType::TILDE)           // ~
        .value("USR", nws::NssTokenType::USR)               // >>>
        .value("USREQ", nws::NssTokenType::USREQ)           // >>>=
        .value("XOR", nws::NssTokenType::XOR)               // ^
        .value("XOREQ", nws::NssTokenType::XOREQ)           // ^=
        // Constants
        .value("FLOAT_CONST", nws::NssTokenType::FLOAT_CONST)
        .value("INTEGER_CONST", nws::NssTokenType::INTEGER_CONST)
        .value("OBJECT_INVALID_CONST", nws::NssTokenType::OBJECT_INVALID_CONST)
        .value("OBJECT_SELF_CONST", nws::NssTokenType::OBJECT_SELF_CONST)
        .value("STRING_CONST", nws::NssTokenType::STRING_CONST)
        .value("STRING_RAW_CONST", nws::NssTokenType::STRING_RAW_CONST)
        // Keywords
        .value("ACTION", nws::NssTokenType::ACTION)                     // action
        .value("BREAK", nws::NssTokenType::BREAK)                       // break
        .value("CASE", nws::NssTokenType::CASE)                         // case
        .value("CASSOWARY", nws::NssTokenType::CASSOWARY)               // cassowary
        .value("CONST", nws::NssTokenType::CONST_)                      // const
        .value("CONTINUE", nws::NssTokenType::CONTINUE)                 // continue
        .value("DEFAULT", nws::NssTokenType::DEFAULT)                   // default
        .value("DO", nws::NssTokenType::DO)                             // do
        .value("EFFECT", nws::NssTokenType::EFFECT)                     // effect
        .value("ELSE", nws::NssTokenType::ELSE)                         // else
        .value("EVENT", nws::NssTokenType::EVENT)                       // event
        .value("FLOAT", nws::NssTokenType::FLOAT)                       // float
        .value("FOR", nws::NssTokenType::FOR)                           // for
        .value("IF", nws::NssTokenType::IF)                             // if
        .value("INT", nws::NssTokenType::INT)                           // int
        .value("ITEMPROPERTY", nws::NssTokenType::ITEMPROPERTY)         // itemproperty
        .value("JSON", nws::NssTokenType::JSON)                         // json
        .value("JSON_CONST", nws::NssTokenType::JSON_CONST)             // json constant
        .value("LOCATION", nws::NssTokenType::LOCATION)                 // location
        .value("LOCATION_INVALID", nws::NssTokenType::LOCATION_INVALID) // location invalid const
        .value("OBJECT", nws::NssTokenType::OBJECT)                     // object
        .value("RETURN", nws::NssTokenType::RETURN)                     // return
        .value("STRING", nws::NssTokenType::STRING)                     // string
        .value("STRUCT", nws::NssTokenType::STRUCT)                     // struct
        .value("SQLQUERY", nws::NssTokenType::SQLQUERY)                 // sqlquery
        .value("SWITCH", nws::NssTokenType::SWITCH)                     // switch
        .value("TALENT", nws::NssTokenType::TALENT)                     // talent
        .value("VECTOR", nws::NssTokenType::VECTOR)                     // vector
        .value("VOID", nws::NssTokenType::VOID_)                        // void
        .value("WHILE", nws::NssTokenType::WHILE);                      // while

    nb::class_<nws::Type>(nw, "Type")
        .def_ro("type_qualifier", &nws::Type::type_qualifier)
        .def_ro("type_specifier", &nws::Type::type_specifier)
        .def_ro("struct_id", &nws::Type::struct_id);

    nb::class_<nws::NssToken>(nw, "NssToken")
        .def("__repr__", [](const nws::NssToken& tk) {
            std::stringstream ss;
            ss << tk;
            return ss.str();
        })
        .def_ro("type", &nws::NssToken::type)
        .def_ro("loc", &nws::NssToken::loc);

    nb::class_<nws::NssLexer>(nw, "NssLexer")
        .def(nb::init<std::string_view, nws::Context*>(),
            nb::keep_alive<1, 3>())
        .def("next", &nws::NssLexer::next)
        .def("current", &nws::NssLexer::current);

    nb::class_<nws::Export>(nw, "Export")
        .def_prop_ro(
            "decl", [](const nws::Export& self) { return self.decl; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "type", [](const nws::Export& self) { return static_cast<nws::Declaration*>(self.type); },
            nb::rv_policy::reference_internal)
        .def_ro("command_id", &nws::Export::command_id);

    nb::class_<nws::Nss>(nw, "Nss")
        .def(nb::init<std::filesystem::path, nws::Context*, bool>(),
            nb::arg("path"), nb::arg("ctx"), nb::arg("is_command_script") = false,
            nb::keep_alive<1, 3>())
        .def(
            "ast", [](nws::Nss& self) {
                return &self.ast();
            },
            nb::rv_policy::reference_internal)
        .def("complete", [](const nws::Nss& self, const std::string& needle, bool no_filter) {
                nws::CompletionContext out;
                self.complete(needle, out, no_filter);
                return std::move(out.completions); })
        .def("complete_at", [](nws::Nss& self, const std::string& needle, size_t line, size_t character, bool no_filter) {
                nws::CompletionContext out;
                self.complete_at(needle, line, character, out, no_filter);
                return std::move(out.completions); })
        .def("complete_dot", [](nws::Nss& self, const std::string& needle, size_t line, size_t character, bool no_filter) {
                std::vector<nw::script::Symbol> out;
                self.complete_dot(needle, line, character, out, no_filter);
                return out; })
        .def("dependencies", &nws::Nss::dependencies)
        .def("diagnostics", &nws::Nss::diagnostics)
        .def("errors", &nws::Nss::errors)
        .def("exports", [](const nws::Nss& self) {
                std::vector<nws::Symbol> result;
                for (const auto& [key, exp] : self.exports()) {
                    if (exp.decl) { result.push_back(self.declaration_to_symbol(exp.decl)); }
                    if (exp.type) { result.push_back(self.declaration_to_symbol(exp.type)); }
                }
                return result; }, nb::rv_policy::reference_internal)
        .def("inlay_hints", &nws::Nss::inlay_hints)
        .def("locate_export", &nws::Nss::locate_export, nb::arg("symbol"), nb::arg("is_type"), nb::arg("search_dependancies") = false, nb::rv_policy::reference_internal)
        .def("locate_symbol", &nws::Nss::locate_symbol, nb::rv_policy::reference_internal)
        .def("name", &nws::Nss::name)
        .def("parse", &nws::Nss::parse)
        .def("process_includes", &nws::Nss::process_includes, nb::arg("parent") = nullptr)
        .def("resolve", &nws::Nss::resolve)
        .def("signature_help", &nws::Nss::signature_help, nb::rv_policy::reference_internal)
        .def("type_name", [](const nws::Nss& self, const nws::AstNode* node) {
            if (!node) { return ""sv; }
            return self.ctx() ? self.ctx()->type_name(node->type_id_) : ""sv; })
        .def("view_from_range", &nws::Nss::view_from_range)
        .def("warnings", &nws::Nss::warnings)
        .def_static("from_string", [](std::string_view str, nws::Context* ctx, bool command_script) { return new nws::Nss(str, ctx, command_script); }, nb::arg("str"), nb::arg("ctx"), nb::arg("is_command_script") = false, nb::keep_alive<0, 2>());

    nb::class_<nws::Include>(nw, "Include")
        .def_ro("resref", &nws::Include::resref)
        .def_ro("location", &nws::Include::location)
        .def_ro("script", &nws::Include::script)
        .def_ro("used", &nws::Include::used);

    nb::class_<nws::Comment>(nw, "Comment")
        .def("__str__", [](const nws::Comment& self) { return self.comment_; });

    nb::class_<nws::Ast>(nw, "Ast")
        .def(
            "__getitem__", [](const nws::Ast& self, size_t index) {
                return self.decls[index];
            },
            nb::rv_policy::reference_internal)
        .def("__len__", [](const nws::Ast& self) { return self.decls.size(); })
        .def("__iter__", [](const nws::Ast& self) { return nb::make_iterator(
                                                        nb::type<nw::Vector<nws::Statement*>>(),
                                                        "DeclIterator",
                                                        self.decls.begin(), self.decls.end()); }, nb::keep_alive<0, 1>())
        .def_ro("defines", &nws::Ast::defines)
        .def_ro("includes", &nws::Ast::includes)
        .def_ro("comments", &nws::Ast::comments)
        .def("find_comment", &nws::Ast::find_comment);

    nb::class_<nws::AstNode>(nw, "AstNode")
        .def(
            "complete", [](nws::AstNode& self, const std::string& needle) {
                std::vector<const nws::Declaration*> out;
                self.complete(needle, out);
                return out;
            },
            nb::rv_policy::reference_internal);

    nb::class_<nws::Expression, nws::AstNode>(nw, "Expression");

    nb::class_<nws::AssignExpression, nws::Expression>(nw, "AssignExpression")
        .def_ro("operator", &nws::AssignExpression::op)
        .def_prop_ro(
            "lhs", [](nws::AssignExpression& self) { return self.lhs; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "rhs", [](nws::AssignExpression& self) { return self.rhs; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::BinaryExpression, nws::Expression>(nw, "BinaryExpression")
        .def_ro("operator", &nws::BinaryExpression::op)
        .def_prop_ro(
            "lhs", [](nws::BinaryExpression& self) { return self.lhs; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "rhs", [](nws::BinaryExpression& self) { return self.rhs; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::CallExpression, nws::Expression>(nw, "CallExpression")
        .def_prop_ro(
            "expr", [](nws::CallExpression& expr) { return expr.expr; },
            nb::rv_policy::reference_internal)
        .def("__len__", [](nws::CallExpression& self) { return self.args.size(); })
        .def(
            "__getitem__", [](nws::CallExpression& self, size_t idx) { return self.args[idx]; },
            nb::rv_policy::reference_internal)
        .def(
            "__iter__", [](nws::CallExpression& self) {
                return nb::make_iterator(nb::type<nw::PVector<nws::SourceRange>>(), "ArgIterator", self.args.begin(), self.args.end());
            },
            nb::keep_alive<0, 1>());

    nb::class_<nws::ComparisonExpression, nws::Expression>(nw, "ComparisonExpression")
        .def_ro("operator", &nws::ComparisonExpression::op)
        .def_prop_ro(
            "lhs", [](nws::ComparisonExpression& self) { return self.lhs; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "rhs", [](nws::ComparisonExpression& self) { return self.rhs; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::ConditionalExpression, nws::Expression>(nw, "ConditionalExpression")
        .def_prop_ro(
            "test", [](nws::ConditionalExpression& self) { return self.test; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "true_branch", [](nws::ConditionalExpression& self) { return self.true_branch; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "false_branch", [](nws::ConditionalExpression& self) { return self.false_branch; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::DotExpression, nws::Expression>(nw, "DotExpression")
        .def_prop_ro(
            "lhs", [](nws::DotExpression& self) { return self.lhs; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "rhs", [](nws::DotExpression& self) { return self.rhs; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::EmptyExpression, nws::Expression>(nw, "EmptyExpression");

    nb::class_<nws::GroupingExpression, nws::Expression>(nw, "GroupingExpression")
        .def_prop_ro(
            "expr", [](nws::GroupingExpression& self) { return self.expr; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::LiteralExpression, nws::Expression>(nw, "LiteralExpression")
        .def_ro("literal", &nws::LiteralExpression::literal)
        .def_ro("data", &nws::LiteralExpression::data);

    nb::class_<nws::LiteralVectorExpression, nws::Expression>(nw, "LiteralVectorExpression")
        .def_ro("x", &nws::LiteralVectorExpression::x)
        .def_ro("y", &nws::LiteralVectorExpression::y)
        .def_ro("z", &nws::LiteralVectorExpression::z);

    nb::class_<nws::LogicalExpression, nws::Expression>(nw, "LogicalExpression")
        .def_ro("operator", &nws::LogicalExpression::op)
        .def_prop_ro(
            "lhs", [](nws::LogicalExpression& self) { return self.lhs; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "rhs", [](nws::LogicalExpression& self) { return self.rhs; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::PostfixExpression, nws::Expression>(nw, "PostfixExpression")
        .def_ro("operator", &nws::PostfixExpression::op)
        .def_prop_ro(
            "lhs", [](nws::PostfixExpression& self) { return self.lhs; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::UnaryExpression, nws::Expression>(nw, "UnaryExpression")
        .def_ro("operator", &nws::UnaryExpression::op)
        .def_prop_ro(
            "rhs", [](nws::UnaryExpression& self) { return self.rhs; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::VariableExpression, nws::Expression>(nw, "VariableExpression")
        .def_ro("var", &nws::VariableExpression::var);

    nb::class_<nws::Statement, nws::AstNode>(nw, "Statement");

    nb::class_<nws::BlockStatement, nws::Statement>(nw, "BlockStatement")
        .def("__len__", [](nws::BlockStatement& self) { return self.nodes.size(); })
        .def(
            "__getitem__", [](nws::BlockStatement& self, size_t idx) { return self.nodes[idx]; },
            nb::rv_policy::reference_internal)
        .def(
            "__iter__", [](const nws::BlockStatement& self) {
                return nb::make_iterator(nb::type<nw::PVector<nws::Statement*>>(), "BlockIterator", self.nodes.begin(), self.nodes.end());
            },
            nb::keep_alive<0, 1>())
        .def_ro("range", &nws::BlockStatement::range_);

    nb::class_<nws::DoStatement, nws::Statement>(nw, "DoStatement")
        .def_prop_ro(
            "block", [](nws::DoStatement& self) { return self.block; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "test", [](nws::DoStatement& self) { return self.expr; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::EmptyStatement, nws::Statement>(nw, "EmptyStatement");

    nb::class_<nws::ExprStatement, nws::Statement>(nw, "ExprStatement")
        .def_prop_ro(
            "expr", [](nws::LabelStatement& self) { return self.expr; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::IfStatement, nws::Statement>(nw, "IfStatement")
        .def_prop_ro(
            "test", [](nws::IfStatement& self) { return self.expr; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "true_branch", [](nws::IfStatement& self) { return self.if_branch; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "false_branch", [](nws::IfStatement& self) { return self.else_branch; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::ForStatement, nws::Statement>(nw, "ForStatement")
        .def_prop_ro(
            "init", [](nws::ForStatement& self) { return self.init; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "test", [](nws::ForStatement& self) { return self.check; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "increment", [](nws::ForStatement& self) { return self.inc; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "block", [](nws::ForStatement& self) { return self.block; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::JumpStatement, nws::Statement>(nw, "JumpStatement")
        .def_ro("operator", &nws::JumpStatement::op)
        .def_prop_ro(
            "expr", [](nws::JumpStatement& self) { return self.expr; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::LabelStatement, nws::Statement>(nw, "LabelStatement")
        .def_ro("label", &nws::LabelStatement::type)
        .def_prop_ro(
            "expr", [](nws::LabelStatement& self) { return self.expr; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::SwitchStatement, nws::Statement>(nw, "SwitchStatement")
        .def_prop_ro(
            "block", [](nws::SwitchStatement& self) { return self.block; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "target", [](nws::SwitchStatement& self) { return self.target; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::WhileStatement, nws::Statement>(nw, "WhileStatement")
        .def_prop_ro(
            "block", [](nws::WhileStatement& self) { return self.block; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "test", [](nws::WhileStatement& self) { return self.check; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::Declaration, nws::Statement>(nw, "Declaration")
        .def("identifier", &nws::Declaration::identifier,
            "Gets the declarations identifier")
        .def_ro("type", &nws::Declaration::type)
        .def("range", &nws::Declaration::range)
        .def("selection_range", &nws::Declaration::selection_range);

    nb::class_<nws::FunctionDecl, nws::Declaration>(nw, "FunctionDecl")
        .def("__len__", [](nws::FunctionDecl& self) { return self.params.size(); })
        .def(
            "__getitem__", [](nws::FunctionDecl& self, size_t idx) { return self.params[idx]; },
            nb::rv_policy::reference_internal)
        .def(
            "__iter__", [](const nws::FunctionDecl& self) {
                return nb::make_iterator(nb::type<nw::PVector<nws::VarDecl*>>(), "ParamIterator", self.params.begin(), self.params.end());
            },
            nb::keep_alive<0, 1>());

    nb::class_<nws::FunctionDefinition, nws::Declaration>(nw, "FunctionDefinition")
        .def_prop_ro(
            "decl", [](nws::FunctionDefinition& self) { return self.decl_inline; },
            nb::rv_policy::reference_internal)
        .def_prop_ro(
            "block", [](nws::FunctionDefinition& self) { return self.block; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::StructDecl, nws::Declaration>(nw, "StructDecl")
        .def("__len__", [](nws::StructDecl& self) { return self.decls.size(); })
        .def(
            "__getitem__", [](nws::StructDecl& self, size_t idx) { return self.decls[idx]; },
            nb::rv_policy::reference_internal)
        .def(
            "__iter__", [](const nws::StructDecl& self) {
                return nb::make_iterator(nb::type<nw::PVector<nws::Declaration*>>(), "DeclIterator", self.decls.begin(), self.decls.end());
            },
            nb::keep_alive<0, 1>())
        .def("locate_member_decl", &nws::StructDecl::locate_member_decl, nb::rv_policy::reference_internal);

    nb::class_<nws::VarDecl, nws::Declaration>(nw, "VarDecl")
        .def_prop_ro(
            "init", [](nws::VarDecl& self) { return self.init; },
            nb::rv_policy::reference_internal);

    nb::class_<nws::DeclList, nws::Declaration>(nw, "DeclList")
        .def("__len__", [](nws::DeclList& self) { return self.decls.size(); })
        .def(
            "__getitem__", [](nws::DeclList& self, size_t idx) { return self.decls[idx]; },
            nb::rv_policy::reference_internal)
        .def(
            "__iter__", [](const nws::BlockStatement& self) {
                return nb::make_iterator(nb::type<nw::PVector<nws::Statement*>>(), "DeclIterator", self.nodes.begin(), self.nodes.end());
            },
            nb::keep_alive<0, 1>())
        .def("locate_decl", &nws::DeclList::locate_decl, nb::rv_policy::reference_internal);
}
