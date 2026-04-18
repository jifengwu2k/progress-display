#pragma once

#include <cstdint>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


inline size_t count_digits(uintmax_t num) {
    size_t digits = 1; // Zero has one digit.
    while (num >= 10) {
        num /= 10;
        ++digits;
    }
    return digits;
}


struct ProgressDisplay {
    const uintmax_t total;
    const size_t total_digits;
    const std::chrono::time_point<std::chrono::system_clock> start_time;
    const std::string prefix;
    const std::string suffix;
    uintmax_t current;
    std::ostream& output_stream;
    
    ProgressDisplay(uintmax_t total, std::ostream& output_stream, const std::string& prefix = "", const std::string& suffix = "") : total(total), total_digits(count_digits(total)), start_time(std::chrono::system_clock::now()), prefix(prefix), suffix(suffix), current(0), output_stream(output_stream) { }
    
    void update(uintmax_t new_current) {
        current = (new_current <= total) ? new_current : total;
        display();
    }
    
    void increment(uintmax_t amount = 1) {
        const uintmax_t remaining = total - current;
        update((amount >= remaining) ? total : (current + amount));
    }

    std::string progress_string() const {
        const int percentage =
            (total == 0) ? 100 : static_cast<int>(static_cast<float>(current) / static_cast<float>(total) * 100.f);

	std::stringstream ss;

	ss << '\r';

	if (!prefix.empty()) ss << prefix << ' ';
	
	ss << std::setw(3) << percentage << '%'
	<< ' '
	<< std::setw(total_digits) << current << '/' << std::setw(total_digits) << total;

	if (!suffix.empty()) ss << ' ' << suffix;

	return ss.str();
    }
    
    void display() {
        // Write and flush the current progress line.
        output_stream << progress_string() << std::flush;
    }
    
    void finish() {
	update(total);
        output_stream << std::endl;
    }
};
