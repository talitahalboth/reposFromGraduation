%{
#include "posfixo.tab.h"
%}

%%

[\n\t ]  

\+    { return MAIS; }
\-    { return MENOS; }
\*    { return ASTERISCO;  }
\/    { return DIV;  }
a     { return IDENT;   }
and   { return AND;  }
or    { return OR;  }
b     {return BOOL;   }

%%

