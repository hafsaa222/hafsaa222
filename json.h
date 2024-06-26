#ifndef JSON_HPP
#define JSON_HPP

#include <initializer_list>
#include <iosfwd>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Definition of the json class
namespace nlohmann
{
    // Type for JSON null
    struct nullptr_t
    {
        // nullptr_t is a constant
        constexpr nullptr_t(int) noexcept {}
    };

    // Type for JSON value
    class json
    {
    public:
        // Enumeration for value type
        enum class value_t : std::uint8_t
        {
            null,     // null value
            object,   // object ({})
            array,    // array ([])
            string,   // string
            boolean,  // boolean (true/false)
            number_integer,  // integer number
            number_unsigned, // unsigned integer number
            number_float,    // floating-point number
            binary,          // binary array (deprecated)
            discarded        // deprecated
        };

        // Constructor for JSON object
        json() noexcept : m_type(value_t::null) {}

        // Destructor
        ~json() = default;

        // Constructor for JSON object with nullptr
        json(std::nullptr_t) noexcept : m_type(value_t::null) {}

        // Type for initializer list
        using initializer_list_t = std::initializer_list<json>;

        // ... (The content continues, but is too long to display here)

        // Type for string
        using string_t = std::string;

        // Type for array
        using array_t = std::vector<json>;

        // Type for object
        using object_t = std::map<string_t, json>;

    private:
        // Type for JSON value
        value_t m_type;
        // Union for JSON value
        union
        {
            std::nullptr_t json_null;
            boolean_t boolean;
            number_integer_t number_integer;
            number_unsigned_t number_unsigned;
            number_float_t number_float;
            string_t* string;
            array_t* array;
            object_t* object;
        } m_value;
    };

    // ... (The content continues, but is too long to display here)
}
{
  "coord": {
    "lon": 10.99,
    "lat": 44.34
  },
  "weather": [
    {
      "id": 501,
      "main": "Rain",
      "description": "moderate rain",
      "icon": "10d"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 298.48,
    "feels_like": 298.74,
    "temp_min": 297.56,
    "temp_max": 300.05,
    "pressure": 1015,
    "humidity": 64,
    "sea_level": 1015,
    "grnd_level": 933
  },
  "visibility": 10000,
  "wind": {
    "speed": 0.62,
    "deg": 349,
    "gust": 1.18
  },
  "rain": {
    "1h": 3.16
  },
  "clouds": {
    "all": 100
  },
  "dt": 1661870592,
  "sys": {
    "type": 2,
    "id": 2075663,
    "country": "IT",
    "sunrise": 1661834187,
    "sunset": 1661882248
  },
  "timezone": 7200,
  "id": 3163858,
  "name": "Zocca",
  "cod": 200
        }
#endif
