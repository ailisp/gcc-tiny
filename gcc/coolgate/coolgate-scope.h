#ifndef COOLGATE_SCOPE_H
#define COOLGATE_SCOPE_H

#include "coolgate-symbol-mapping.h"
#include <tr1/memory>
#include <vector>

namespace Coolgate
{

struct Scope
{
public:
  SymbolMapping &
  get_current_mapping ()
  {
    gcc_assert (!map_stack.empty ());
    return map_stack.back ();
  }

  void push_scope ();
  void pop_scope ();

  Scope ();

  SymbolPtr lookup (const std::string &str);

private:
  typedef std::vector<SymbolMapping> MapStack;
  MapStack map_stack;
};

}

#endif // COOLGATE_SCOPE_H
