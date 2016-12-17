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
    // TODO:: what if the document is not present in the collection?

    // TODO:: move prepare statement to another method
    this->conn->prepare (
        "insertToken",
        "INSERT INTO index (token, documentid, tf, idf) VALUES ($1, $2, $3, $4);"
    );
    work w (*conn);

    for (auto& token : doc.getTokens ()) {
        w.prepared ("insertToken")
            (token.getData ())
            (doc.getId ())
            (token.getTf ())
            (token.getIdf ())
            .exec ();
    }

    w.commit ();
}

long IndexWriter::countDocuments () {
    this->conn->prepare (
        "countDocuments",
        "SELECT count (id) FROM documents;"
    );
    work w (*conn);

    auto res = w.prepared ("countDocuments").exec ();

    return res.front ()[0].as<long> ();
}

long IndexWriter::countDocuments (string token) {
    this->conn->prepare (
            "countDocumentFrequency",
            "SELECT count (documentid) FROM index WHERE token=$1;"
    );
    work w (*conn);

    auto res = w.prepared ("countDocumentFrequency").exec ();

    return res.front ()[0].as<long> ();
}
