#include <iostream>
#include <string>

#include <uriparser/Uri.h>

std::string fromRange(const UriTextRangeA & rng)
{
    return std::string(rng.first, rng.afterLast);
}

std::string fromList(UriPathSegmentA * xs, const std::string & delim)
{
    UriPathSegmentStructA * head(xs);
    std::string accum;

    while (head) {
        accum += delim + fromRange(head->text);
        head = head->next;
    }

    return accum;
}

int main(int argc, char *argv[]) 
{
	UriUriA uriParse;
    UriParserStateA state;
    state.uri = &uriParse;
    if (uriParseUriA(&state, 
    argv[1] ? argv[1] : "http://www.google.com/lesliezhai") == URI_SUCCESS) {
        std::cout << fromRange(uriParse.scheme) << std::endl;
        std::cout << fromRange(uriParse.hostText) << std::endl;
        std::cout << fromRange(uriParse.portText) << std::endl;
        std::cout << fromList(uriParse.pathHead, "/") << std::endl;
        std::cout << fromRange(uriParse.query) << std::endl;
        std::cout << fromRange(uriParse.fragment) << std::endl;
    }
    uriFreeUriMembersA(&uriParse);
    return 0;
}
