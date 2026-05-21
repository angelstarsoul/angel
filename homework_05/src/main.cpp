#include "telemetry.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: telemetry_check <input_path>" << std::endl;
        return 1;
    }

    Frame frames[MAX_TELEMETRY_FRAMES];
    const int frame_count = read_frames(argv[1], frames, MAX_TELEMETRY_FRAMES);


    if (frame_count < 0) {
        std::cerr << "Error: invalid telemetry data" << std::endl;
        return 1;                  
    }

    if (frame_count == 0) {
        std::cout << "frames_total 0" << std::endl;
        std::cout << "frames_valid 0" << std::endl;
        std::cout << "voltage_min 0" << std::endl;
        std::cout << "voltage_max 0" << std::endl;
        std::cout << "temperature_avg 0" << std::endl;
        std::cout << "low_voltage_frames 0" << std::endl;
        std::cout << "frame_rate_hz 0" << std::endl;
        return 0;
    }


    const Summary summary = summarize(frames, frame_count);
    print_summary(summary);

    return 0;
}