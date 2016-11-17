#include <string>
#include <map>

#include "boost/any.hpp"

/*!
 * \brief Configuration class
 *
 * Provides an interface to configuration data storage:
 * - load/store config on the disk
 * - access config data by a key
 *
 * Access to data of different types is done by using appropriate methods:
 * getInt for int values, etc.
 *
 * All the data is stored in key: value pairs
 * for bool:
 * "key": True | False
 * for int
 * "key": x
 * for double:
 * "key": x.y
 * for string:
 * "key": "value"
 */
class Config
{
     std::map <std::string, boost::any> storage;

public:
    Config () = default;
    ~Config () = default;
    Config (const Config& ) = delete;
    Config (Config&& ) = delete;

    /*!
     * \brief get the value of type bool for a key
     *
     * @param config key
     * @return bool value
     */
    bool getBool (std::string key);

    /*!
     * \brief get the value of type int for a key
     *
     * @param config key
     * @return int value
     */
    int getInt (std::string key);

    /*!
     * \brief get the value of type double for a key
     *
     * @param config key
     * @return double value
     */
    double getDouble (std::string key);

    /*!
     * \brief get the value of type string for a key
     *
     * @param config key
     * @return string value
     */
    std::string getString (std::string key);

    /*!
     * \brief Set the value of type bool for a key
     *
     * @param config key
     * @param bool value
     */
    void setBool (std::string key, bool value);

    /*!
     * \brief Set the value of type int for a key
     *
     * @param config key
     * @param int value
     */
    void setInt (std::string key, int value);

    /*!
     * \brief Set the value of type double for a key
     *
     * @param config key
     * @param double value
     */
    void setDouble (std::string key, double value);

    /*!
     * \brief Set the value of type string for a key
     *
     * @param config key
     * @param string value
     */
    void setString (std::string key, std::string value);

    /*!
     * \brief Load config data from the specified path using the defined format
     *
     * @param fs path to storage file
     */
    void loadFrom (std::string path);
};