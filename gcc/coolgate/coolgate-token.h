#ifndef COOLGATE_TOKEN_H
#define COOLGATE_TOKEN_H

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "input.h"

#include <string>
#include <tr1/memory>

namespace Coolgate
{

// COOLGATE_TOKEN(name, description)
// COOLGATE_TOKEN_KEYWORD(name, identifier)
//
// Keep COOLGATE_TOKEN_KEYWORD sorted

#define COOLGATE_TOKEN_LIST                                                        \
  COOLGATE_TOKEN (FIRST_TOKEN, "<first-token-marker>")                             \
  COOLGATE_TOKEN (END_OF_FILE, "end of file")                                      \
  COOLGATE_TOKEN (ASSIG, ":=")                                                     \
  COOLGATE_TOKEN (ASTERISK, "*")                                                   \
  COOLGATE_TOKEN (COLON, ":")                                                      \
  COOLGATE_TOKEN (COMMA, ",")                                                      \
  COOLGATE_TOKEN (DIFFERENT, "!=")                                                 \
  COOLGATE_TOKEN (EQUAL, "=")                                                      \
  COOLGATE_TOKEN (LEFT_PAREN, "(")                                                 \
  COOLGATE_TOKEN (MINUS, "-")                                                      \
  COOLGATE_TOKEN (PLUS, "+")                                                       \
  COOLGATE_TOKEN (RIGHT_PAREN, ")")                                                \
  COOLGATE_TOKEN (SEMICOLON, ";")                                                  \
  COOLGATE_TOKEN (SLASH, "/")                                                      \
  COOLGATE_TOKEN (PERCENT, "%")                                                    \
  COOLGATE_TOKEN (GREATER, ">")                                                    \
  COOLGATE_TOKEN (GREATER_OR_EQUAL, ">=")                                          \
  COOLGATE_TOKEN (LOWER, "<")                                                      \
  COOLGATE_TOKEN (LOWER_OR_EQUAL, "<=")                                            \
  COOLGATE_TOKEN (IDENTIFIER, "identifier")                                        \
  COOLGATE_TOKEN (INTEGER_LITERAL, "integer literal")                              \
  COOLGATE_TOKEN (REAL_LITERAL, "real literal")                                    \
  COOLGATE_TOKEN (STRING_LITERAL, "string literal")                                \
  COOLGATE_TOKEN (LEFT_SQUARE, "[")                                                \
  COOLGATE_TOKEN (RIGHT_SQUARE, "]")                                               \
  COOLGATE_TOKEN (DOT, ".")                                                        \
                                                                               \
  COOLGATE_TOKEN_KEYWORD (AND, "and")                                              \
  COOLGATE_TOKEN_KEYWORD (BOOL, "bool")                                            \
  COOLGATE_TOKEN_KEYWORD (DO, "do")                                                \
  COOLGATE_TOKEN_KEYWORD (ELSE, "else")                                            \
  COOLGATE_TOKEN_KEYWORD (END, "end")                                              \
  COOLGATE_TOKEN_KEYWORD (FALSE_LITERAL, "false")                                  \
  COOLGATE_TOKEN_KEYWORD (FLOAT, "float")                                          \
  COOLGATE_TOKEN_KEYWORD (FOR, "for")                                              \
  COOLGATE_TOKEN_KEYWORD (IF, "if")                                                \
  COOLGATE_TOKEN_KEYWORD (INT, "int")                                              \
  COOLGATE_TOKEN_KEYWORD (NOT, "not")                                              \
  COOLGATE_TOKEN_KEYWORD (OR, "or")                                                \
  COOLGATE_TOKEN_KEYWORD (READ, "read")                                            \
  COOLGATE_TOKEN_KEYWORD (RECORD, "record")                                        \
  COOLGATE_TOKEN_KEYWORD (THEN, "then")                                            \
  COOLGATE_TOKEN_KEYWORD (TO, "to")                                                \
  COOLGATE_TOKEN_KEYWORD (TRUE_LITERAL, "true")                                    \
  COOLGATE_TOKEN_KEYWORD (TYPE, "type")                                            \
  COOLGATE_TOKEN_KEYWORD (VAR, "var")                                              \
  COOLGATE_TOKEN_KEYWORD (WHILE, "while")                                          \
  COOLGATE_TOKEN_KEYWORD (WRITE, "write")                                          \
                                                                               \
  COOLGATE_TOKEN (LAST_TOKEN, "<last-token-marker>")

enum /* class */ TokenId
{
#define COOLGATE_TOKEN(name, _) name,
#define COOLGATE_TOKEN_KEYWORD(x, y) COOLGATE_TOKEN (x, y)
  COOLGATE_TOKEN_LIST
#undef COOLGATE_TOKEN_KEYWORD
#undef COOLGATE_TOKEN
};

const char *get_token_description (TokenId tid);
const char *token_id_to_str (TokenId tid);

struct Token;
typedef std::tr1::shared_ptr<Token> TokenPtr;
typedef std::tr1::shared_ptr<const Token> const_TokenPtr;

struct Token
{
private:
  TokenId token_id;
  location_t locus;
  std::string *str;

  Token (TokenId token_id_, location_t locus_)
    : token_id (token_id_), locus (locus_), str (0)
  {
  }
  Token (TokenId token_id_, location_t locus_, const std::string& str_)
    : token_id (token_id_), locus (locus_), str (new std::string (str_))
  {
  }

  // No default initializer
  Token ();
  // Do not copy/assign tokens
  Token (const Token &);
  Token &operator=(const Token &);

public:
  ~Token () { delete str; }

  static TokenPtr
  make (TokenId token_id, location_t locus)
  {
    return TokenPtr(new Token (token_id, locus));
  }

  static TokenPtr
  make_identifier (location_t locus, const std::string& str)
  {
    return TokenPtr(new Token (IDENTIFIER, locus, str));
  }

  static TokenPtr
  make_integer (location_t locus, const std::string& str)
  {
    return TokenPtr(new Token (INTEGER_LITERAL, locus, str));
  }

  static TokenPtr
  make_real (location_t locus, const std::string& str)
  {
    return TokenPtr(new Token (REAL_LITERAL, locus, str));
  }

  static TokenPtr
  make_string (location_t locus, const std::string& str)
  {
    return TokenPtr(new Token (STRING_LITERAL, locus, str));
  }

  TokenId
  get_id () const
  {
    return token_id;
  }

  location_t
  get_locus () const
  {
    return locus;
  }

  const std::string &
  get_str () const
  {
    gcc_assert (str != NULL);
    return *str;
  }

  // diagnostics
  const char *
  get_token_description () const
  {
    return Coolgate::get_token_description (token_id);
  }

  // debugging
  const char *
  token_id_to_str () const
  {
    return Coolgate::token_id_to_str (token_id);
  }
};

}

#endif // COOLGATE_TOKEN_H
