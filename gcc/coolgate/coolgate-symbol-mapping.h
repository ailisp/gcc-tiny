#ifndef COOLGATE_SYMBOL_MAPPING_H
#define COOLGATE_SYMBOL_MAPPING_H

#include "coolgate/coolgate-symbol.h"
#include <tr1/memory>
#include <map>

namespace Coolgate
{

struct SymbolMapping
{
public:

  void insert (SymbolPtr s);
  SymbolPtr get (const std::string &str) const;

private:

  typedef std::map<std::string, SymbolPtr > Map;
  Map map;
};

}

#endif // COOLGATE_SYMBOL_MAPPING_H
