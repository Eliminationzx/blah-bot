//
// Created by user on 7/26/16.
//


#include <string>
#include <vector>

std::string pageText = "This domain is established to be used for illustrative examples in documents. You may use this "
        "domain in examples without prior coordination or asking for permission. "
        "More information...";

std::vector<std::string> expectedTokens {
        "This",
        "domain",
        "is",
        "established",
        "to",
        "be",
        "used",
        "for",
        "illustrative",
        "examples",
        "in",
        "documents",
        "You",
        "may",
        "use",
        "this",
        "domain",
        "in",
        "examples",
        "without",
        "prior",
        "coordination",
        "or",
        "asking",
        "for",
        "permission",
        "More",
        "information"
};
