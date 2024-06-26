#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/image.h>
#include <gtkmm/grid.h>

// Replace with your actual API key
const std::string API_KEY = "0fd400453571bfef80db27c0b0f5a0ae
";

// Function to fetch weather data from OpenWeatherMap API
std::string fetchWeatherData(const std::string& city) {
    std::string url = "https://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + API_KEY + "&units=metric";

    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, 1L);

        char* buffer;
        size_t size;
        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &size);
            buffer = static_cast<char*>(malloc(size + 1));
            if (buffer) {
                curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &buffer);
                return std::string(buffer);
            }
        }

        curl_easy_cleanup(curl);
    }

    return "";
}

// Function to parse JSON weather data
std::map<std::string, std::string> parseWeatherData(const std::string& json_data) {
    std::map<std::string, std::string> weather_data;

    Json::Reader reader;
    Json::Value root;
    if (reader.parse(json_data, root)) {
        if (root["main"].isArray()) {
            weather_data["temp"] = root["main"]["temp"].asString();
            weather_data["feels_like"] = root["main"]["feels_like"].asString();
            weather_data["temp_min"] = root["main"]["temp_min"].asString();
            weather_data["temp_max"] = root["main"]["temp_max"].asString();
            weather_data["pressure"] = root["main"]["pressure"].asString();
            weather_data["humidity"] = root["main"]["humidity"].asString();
            weather_data["wind_speed"] = root["wind"]["speed"].asString();
            weather_data["description"] = root["weather"][0]["description"].asString();
        }
    }

    return weather_data;
}

// Function to display weather data
void displayWeather(const std::map<std::string, std::string>& weather_data) {
    std::cout << "Current Temperature: " << weather_data["temp"] << "°C" << std::endl;
    std::cout << "Feels Like: " << weather_data["feels_like"] << "°C" << std::endl;
    std::cout << "Minimum Temperature: " << weather_data["temp_min"] << "°C" << std::endl;
    std::cout << "Maximum Temperature: " << weather_data["temp_max"] << "°C" << std::endl;
    std::cout << "Pressure: " << weather_data["pressure"] << "hPa" << std::endl;
    std::cout << "Humidity: " << weather_data["humidity"] << "%" << std::endl;
    std::cout << "Wind Speed: " << weather_data["wind_speed"] << "m/s" << std::endl;
    std::cout << "Description: " << weather_data["description"] << std::endl;
}

// Function to save weather data to a file
void saveWeatherData(const std::map<std::string, std::string>& weather_data, const std::string& filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << "Current Temperature: " << weather_data["temp"] << "°C" << std::endl;
        outfile << "Feels Like: " << weather_data["feels_like"] << "°C" << std::endl;
        outfile << "Minimum Temperature: " << weather_data["temp_min"] << "°C" << std::endl;
        outfile << "Maximum Temperature: " << weather_data["temp_max"] << "°C" << std::endl;
        outfile << "Pressure: " << weather_data["pressure"] << "hPa" << std::endl;
        outfile << "Humidity: " << weather_data["humidity"] << "%" << std::endl;
        outfile << "Wind Speed: " << weather_data["wind_speed"] << "m/s" << std::endl;
        outfile << "Description: " << weather_data["description"] << std::endl;
        outfile.close();
    }
}

// Main function
int main(int argc, char *argv[]) {
    // Initialize GTK+ application
    Gtk::Application app = Gtk::Application::create(argc, argv, "org.example.weatherapp");

    // Create main window
    Gtk::Window window;
    window.set_title("Weather App");
    window.set_default_size(400, 300);

    // Create a vertical box layout
    Gtk::Box vbox(Gtk::Orientation::VERTICAL);

    // Create a label for the city input
    Gtk::Label city_label("Enter City:");
    vbox.pack_start(city_label, false, false, 5);

    // Create an entry for city input
    Gtk::Entry city_entry;
    vbox.pack_start(city_entry, false, false, 5);

    // Create a button to fetch weather data
    Gtk::Button fetch_button("Fetch Weather");
    vbox.pack_start(fetch_button, false, false, 5);

    // Create a grid layout for displaying weather data
    Gtk::Grid grid;
    vbox.pack_start(grid, true, true, 5);

    // Create labels for weather data
    Gtk::Label temp_label("Temperature:");
    Gtk::Label feels_like_label("Feels Like:");
    Gtk::Label temp_min_label("Min Temp:");
    Gtk::Label temp_max_label("Max Temp:");
    Gtk::Label pressure_label("Pressure:");
    Gtk::Label humidity_label("Humidity:");
    Gtk::Label wind_speed_label("Wind Speed:");
    Gtk::Label description_label("Description:");

    // Create labels to display weather data
    Gtk::Label temp_value;
    Gtk::Label feels_like_value;
    Gtk::Label temp_min_value;
    Gtk::Label temp_max_value;
    Gtk::Label pressure_value;
    Gtk::Label humidity_value;
    Gtk::Label wind_speed_value;
    Gtk::Label description_value;

    // Add labels to the grid
    grid.attach(temp_label, 0, 0, 1, 1);
    grid.attach(temp_value, 1, 0, 1, 1);
    grid.attach(feels_like_label, 0, 1, 1, 1);
    grid.attach(feels_like_value, 1, 1, 1, 1);
    grid.attach(temp_min_label, 0, 2, 1, 1);
    grid.attach(temp_min_value, 1, 2, 1, 1);
    grid.attach(temp_max_label, 0, 3, 1, 1);
    grid.attach(temp_max_value, 1, 3, 1, 1);
    grid.attach(pressure_label, 0, 4, 1, 1);
    grid.attach(pressure_value, 1, 4, 1, 1);
    grid.attach(humidity_label, 0, 5, 1, 1);
    grid.attach(humidity_value, 1, 5, 1, 1);
    grid.attach(wind_speed_label, 0, 6, 1, 1);
    grid.attach(wind_speed_value, 1, 6, 1, 1);
    grid.attach(description_label, 0, 7, 1, 1);
    grid.attach(description_value, 1, 7, 1, 1);

    // Connect fetch button to signal handler
    fetch_button.signal_clicked().connect([&]() {
        // Get city name from entry
        std::string city = city_entry.get_text();

        // Fetch weather data
        std::string weather_data = fetchWeatherData(city);

        // Parse JSON data
        std::map<std::string, std::string> parsed_data = parseWeatherData(weather_data);

        // Update weather data labels
        temp_value.set_text(parsed_data["temp"] + "°C");
        feels_like_value.set_text(parsed_data["feels_like"] + "°C");
        temp_min_value.set_text(parsed_data["temp_min"] + "°C");
        temp_max_value.set_text(parsed_data["temp_max"] + "°C");
        pressure_value.set_text(parsed_data["pressure"] + "hPa");
        humidity_value.set_text(parsed_data["humidity"] + "%");
        wind_speed_value.set_text(parsed_data["wind_speed"] + "m/s");
        description_value.set_text(parsed_data["description"]);
    });

    // Add layout to window
    window.add(vbox);

    // Show the window
    window.show_all();

    // Run the GTK+ application
    return app.run(window);
}

