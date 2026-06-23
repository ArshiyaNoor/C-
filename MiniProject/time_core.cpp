#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

namespace py = pybind11;

// Custom exception for faulty time values
class InvalidTimeException : public std::runtime_error {
public:
    InvalidTimeException(const std::string& msg) : std::runtime_error("Time Error: " + msg) {}
};

// Core Time Logic Class
class Duration {
public:
    int hours;
    int minutes;

    Duration(int h, int m) : hours(h), minutes(m) {
        if (h < 0 || m < 0) {
            throw InvalidTimeException("Time units cannot be negative values!");
        }
        normalize();
    }

    void normalize() {
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes = minutes % 60;
        }
    }

    // Operator Overloading (+) to add time frames directly
    Duration operator+(const Duration& other) const {
        return Duration(this->hours + other.hours, this->minutes + other.minutes);
    }

    std::string toString() const {
        return std::to_string(hours) + "h " + std::to_string(minutes) + "m";
    }
};

// Managing tracked task instances
class TrackedTask {
private:
    std::string taskName;
    std::string category;
    std::unique_ptr<Duration> durationPtr; // Dynamic Memory via pointers

public:
    TrackedTask(std::string name, std::string cat, int h, int m) : taskName(name), category(cat) {
        durationPtr = std::make_unique<Duration>(h, m);
    }

    std::string getSummary() const {
        return "**[" + category + "]** " + taskName + " — *Total Time: " + durationPtr->toString() + "*";
    }

    Duration getDuration() const {
        return *durationPtr;
    }
};

// System Registry Wrapper
class TimeTrackerSystem {
private:
    std::vector<TrackedTask> taskRegistry;

public:
    TimeTrackerSystem() {}

    void logTask(std::string name, std::string cat, int h, int m) {
        taskRegistry.push_back(TrackedTask(name, cat, h, m));
    }

    std::vector<std::string> fetchRegistryReport() {
        std::vector<std::string> report;
        for (const auto& task : taskRegistry) {
            report.push_back(task.getSummary());
        }
        return report;
    }

    // Accumulates total math down in C++ using the overloaded + operator
    std::string calculateGrandTotal() {
        if (taskRegistry.empty()) return "0h 0m";
        
        Duration total(0, 0);
        for (const auto& task : taskRegistry) {
            total = total + task.getDuration();
        }
        return total.toString();
    }

    // Interface entry for the standalone duration adder calculator
    std::string addTwoDurations(int h1, int m1, int h2, int m2) {
        try {
            Duration d1(h1, m1);
            Duration d2(h2, m2);
            Duration result = d1 + d2;
            return "### Total Combined Duration: `" + result.toString() + "`";
        } 
        catch (const InvalidTimeException& e) {
            return std::string("❌ Exception Caught: ") + e.what();
        }
    }
};

// Pybind11 Native Export Definition
PYBIND11_MODULE(time_core, m) {
    py::class_<TimeTrackerSystem>(m, "TimeTrackerSystem")
        .def(py::init<>())
        .def("log_task", &TimeTrackerSystem::logTask)
        .def("fetch_registry_report", &TimeTrackerSystem::fetchRegistryReport)
        .def("calculate_grand_total", &TimeTrackerSystem::calculateGrandTotal)
        .def("add_two_durations", &TimeTrackerSystem::addTwoDurations);
}
