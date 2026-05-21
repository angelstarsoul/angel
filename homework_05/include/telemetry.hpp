#pragma once


const int MAX_TELEMETRY_FRAMES = 128;


struct Frame {
    long timestamp_ms;
    int seq;
    double voltage_v;
    double current_a;
    double temperature_c;
    int gps_fix;
    int satellites;
};


struct Summary {
    int frames_total;
    int frames_valid;
    double voltage_min;
    double voltage_max;
    double temperature_avg;
    int low_voltage_frames;
    double frame_rate_hz;
};


int read_frames(const char* path, Frame frames[], int max_frames);


Summary summarize(const Frame frames[], int frame_count);


void print_summary(const Summary& summary);
