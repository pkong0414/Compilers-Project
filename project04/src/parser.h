

#include <string>

#ifndef PARSER_H
#define PARSER_H

class Parser {



public:
    void program();
    void block( struct Node*, std::string );
    void vars( struct Node*, std::string );
    void expr( struct Node*, std::string );
    void N( struct Node*, std::string );
    void A( struct Node*, std::string );
    void M( struct Node*, std::string );
    void R( struct Node*, std::string );
    void stats( struct Node*, std::string );
    void mStat( struct Node*, std::string );
    bool stat( struct Node*, std::string );
    void in( struct Node*, std::string );
    void out( struct Node*, std::string );
    void iffy( struct Node*, std::string );
    void loop( struct Node*, std::string );
    void assign( struct Node*, std::string );
    void RO( struct Node*, std::string );

};



#endif //PARSER_H