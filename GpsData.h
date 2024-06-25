#ifndef GPS_CONVERTER_GPSDATA_H
#define GPS_CONVERTER_GPSDATA_H

#endif //GPS_CONVERTER_GPSDATA_H

#include <cmath>
#include <string>
#include <vector>

double DELTA = 41.7;
#define SET_DELTA(x) x == 24 ? DELTA = 41.7 : DELTA = 33.33

struct GPS {
    GPS() = default;
    GPS(double lat, double lon, double alt) {
        LAT = lat;
        LON = lon;
        ALT = alt;
    }

    double LAT = 0;
    double LON = 0;
    double ALT = 0;
};

class Data {
public:
    Data() = default;

    explicit Data(const std::vector<std::string>& line) {
        cts = std::stod(line[0]);
        date = line[1];
        gps_data = {std::stod(line[2]), std::stod(line[3]), std::stod(line[4])};
    }

    ~Data() = default;

    [[nodiscard]] double GetCts() const {
        return cts;
    }

    [[nodiscard]] std::string GetDate() const {
        return date;
    }

    [[nodiscard]] GPS GetGpsData() const {
        return gps_data;
    }

    [[nodiscard]] int GetFrame() const {
        return frame;
    }

    void CalculateFrame() {
        if (cts != 0) {
            double temp = std::round(cts / DELTA);
            frame = static_cast<int>(temp);
        }
    }

private:
    double cts = 0; // Время кадра в мс
    std::string date = ""; // дата кадра
    GPS gps_data = {}; // Данные GPS
    int frame = 0;
};