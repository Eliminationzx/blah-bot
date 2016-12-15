//
// Created by user on 12/15/16.
//

#include "IndexWriter.h"

using namespace std;
using namespace pqxx;

IndexWriter::IndexWriter (shared_ptr <connection> Conn)
    : conn (Conn)
{}

void IndexWriter::write (Document& doc) {
    this->conn->prepare (
        "insertToken",
        "INSERT INTO index (token, documentid, tf, idf) VALUES ($1, $2, $3, $4);"
    );
    work w (*conn);

    // for every token
    for (auto& token : doc.getTokens ()) {
        w.prepared ("insertToken")
            (token.first)
            (doc.getId ())
            (token.second.first)
            (token.second.second)
            .exec ();
    }

    w.commit ();
}
