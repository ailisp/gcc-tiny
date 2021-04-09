#include "coolgate-token.h"

namespace Coolgate
{

const char *
get_token_description (TokenId tid)
{
  switch (tid)
    {
#define COOLGATE_TOKEN(name, descr)                                                \
  case name:                                                                   \
    return descr;
#define COOLGATE_TOKEN_KEYWORD(x, y) COOLGATE_TOKEN (x, y)
      COOLGATE_TOKEN_LIST
#undef COOLGATE_TOKEN_KEYWORD
#undef COOLGATE_TOKEN
    default:
      gcc_unreachable ();
    }
}

const char *
token_id_to_str (TokenId tid)
{
  switch (tid)
    {
#define COOLGATE_TOKEN(name, _)                                                    \
  case name:                                                                   \
    return #name;
#define COOLGATE_TOKEN_KEYWORD(x, y) COOLGATE_TOKEN (x, y)
      COOLGATE_TOKEN_LIST
#undef COOLGATE_TOKEN_KEYWORD
#undef COOLGATE_TOKEN
    default:
      gcc_unreachable ();
    }
}

}
