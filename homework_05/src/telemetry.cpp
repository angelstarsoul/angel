#include "telemetry.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits> 
#include <sstream>

bool parse_frame(const std::string& line, Frame& frame) {
    std::istringstream iss(line);
    
    if (!(iss >> frame.timestamp_ms >> frame.seq >> frame.voltage_v >> 
              frame.current_a >> frame.temperature_c >> frame.gps_fix >> frame.satellites)) {
        return false;
    }

    
    std::string extra;
    if (iss >> extra) {
        return false; 
    }

    return true;
}

int read_frames(const char* path, Frame frames[], int max_frames) {
    std::ifstream input(path);
    if (!input) {
        std::cerr << "error: failed to open input file: " << path << '\n';
        return 0;
    }

    int frame_count = 0;
    std::string line;
    int line_number = 0;

    long prev_timestamp = -1;

    while (std::getline(input, line) && frame_count < max_frames) {
        ++line_number;
        if (line.empty() || line[0] == '#' || line[0] == '\n') {
            continue;
        }

        if (!parse_frame(line, frames[frame_count])) {
            std::cerr << "error: invalid frame at line " << line_number << '\n';
            return -1;
        }

        
        const Frame& f = frames[frame_count];

        if (f.timestamp_ms <= prev_timestamp && frame_count > 0) {
            std::cerr << "error: non-increasing timestamp at line " << line_number << '\n';
            return -1;
        }
        if (f.seq != frame_count + 1) {
            std::cerr << "error: wrong sequence number at line " << line_number 
                      << " (expected " << (frame_count + 1) << ", got " << f.seq << ")\n";
            return -1;
        }
        if (f.voltage_v <= 0.0) {
            std::cerr << "error: invalid voltage at line " << line_number << '\n';
            return -1;
        }
        if (f.temperature_c < -40.0 || f.temperature_c > 120.0) {
            std::cerr << "error: temperature out of range at line " << line_number << '\n';
            return -1;
        }
        if (f.gps_fix != 0 && f.gps_fix != 1) {
            std::cerr << "error: invalid gps_fix at line " << line_number << '\n';
            return -1;
        }

        prev_timestamp = f.timestamp_ms;
        ++frame_count;
    }

    return frame_count;
}
Summary summarize(const Frame frames[], int frame_count) {
    Summary s{};
    s.frames_total = frame_count;
    s.frames_valid = frame_count;

    if (frame_count == 0) {
        s.voltage_min = 0.0;
        s.voltage_max = 0.0;
        s.temperature_avg = 0.0;
        s.frame_rate_hz = 0.0;
        return s;
    }

    s.voltage_min = frames[0].voltage_v;
    s.voltage_max = frames[0].voltage_v;
    double temp_sum = 0.0;

    for (int i = 0; i < frame_count; ++i) {
        s.voltage_min = std::min(s.voltage_min, frames[i].voltage_v);
        s.voltage_max = std::max(s.voltage_max, frames[i].voltage_v);
        temp_sum += frames[i].temperature_c;

        if (frames[i].voltage_v < 22.0) {
            ++s.low_voltage_frames;
        }
    }

    s.temperature_avg = temp_sum / frame_count;

    if (frame_count >= 2) {
        long elapsed = frames[frame_count-1].timestamp_ms - frames[0].timestamp_ms;
        s.frame_rate_hz = (elapsed > 0) ? 
            static_cast<double>(frame_count - 1) * 1000.0 / elapsed : 0.0;
    }

    return s;
}

void print_summary(const Summary& summary) {
    std::cout << "frames_total " << summary.frames_total << '\n';
    std::cout << "frames_valid " << summary.frames_valid << '\n';
    std::cout << "voltage_min " << summary.voltage_min << '\n';
    std::cout << "voltage_max " << summary.voltage_max << '\n';
    std::cout << "temperature_avg " << summary.temperature_avg << '\n';
    std::cout << "low_voltage_frames " << summary.low_voltage_frames << '\n';
    std::cout << "frame_rate_hz " << summary.frame_rate_hz << '\n';
}