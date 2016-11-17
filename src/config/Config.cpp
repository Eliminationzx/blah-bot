#include <fstream>

#include "boost/filesystem.hpp"

#include "Config.h"

using namespace std;
using namespace boost;

optional <bool> Config::getBool (std::string key)
{
    if (storage.find (key) != storage.end ())
        return any_cast <bool> (storage[key]);

    return optional <bool> {};
}

optional <int> Config::getInt (std::string key)
{
    if (storage.find (key) != storage.end ())
        return any_cast <int> (storage[key]);

    return optional <int> {};
}

optional <double> Config::getDouble (std::string key)
{
    if (storage.find (key) != storage.end ())
        return any_cast <double> (storage[key]);

    return optional <double> {};
}

optional <string> Config::getString (std::string key)
{
    if (storage.find (key) != storage.end ())
        return any_cast <string> (storage[key]);

    return optional <string> {};
}

void Config::setBool (std::string key, bool value)
{
    storage[key] = value;
}

void Config::setInt (std::string key, int value)
{
    storage[key] = value;
}

void Config::setDouble (std::string key, double value)
{
    storage[key] = value;
}

void Config::setString (std::string key, string value)
{
    storage[key] = value;
}

void Config::loadFrom (std::string path)
{
    // open the specified file
    ifstream file (path);

    // TODO: log error or exception?
    if (!file.is_open ())
        return;

    size_t colonIndex;
    size_t firstQuoteIndex;
    size_t lastQuoteIndex;
    size_t digitIndex;
    size_t dotIndex;
    string key;

    // for every line
    for (string line; getline (file, line);)
    {
        colonIndex = string::npos;
        firstQuoteIndex = string::npos;
        lastQuoteIndex = string::npos;
        digitIndex = string::npos;
        dotIndex = string::npos;

        // split it by colon
        colonIndex = line.find_first_of (':');
        key = string (line, 0, colonIndex);

        // find if the value is of string type
        firstQuoteIndex = line.find_first_of ('"');
        lastQuoteIndex = line.find_last_of ('"');

        if (firstQuoteIndex == string::npos && lastQuoteIndex == string::npos)
        {
            // the value is not a string

            if (line.find ("True") != string::npos || line.find ("true") != string::npos)
            {
                setBool (key, true);
            }
            else if (line.find ("False") != string::npos || line.find ("false") != string::npos)
            {
                setBool (key, false);
            }
            else
            {
                digitIndex = line.find_first_of ("0123456789", colonIndex);
                dotIndex = line.find ('.');

                // if there's a dot - then it's a double value
                if (dotIndex == string::npos)
                {
                    setInt (
                        key,
                        stoi (line.substr (digitIndex, line.length () - digitIndex))
                    );
                }
                // otherwise - it's an int value
                else
                {
                    setDouble (
                        key,
                        stod (line.substr (digitIndex, line.length () - digitIndex))
                    );
                }
            }
        }
        else
        {
            setString (
                key,
                string (line, firstQuoteIndex + 1, lastQuoteIndex - firstQuoteIndex - 1)
            );
        }
    }
}
