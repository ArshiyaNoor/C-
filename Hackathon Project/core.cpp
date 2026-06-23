#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

namespace py = pybind11;

// ==========================================
// 1. CUSTOM EXCEPTION HANDLING
// ==========================================
class InvalidVitalException : public std::runtime_error {
public:
    InvalidVitalException(const std::string& msg) : std::runtime_error("Medical Alert: " + msg) {}
};

// ==========================================
// 2. ABSTRACT BASE CLASS & VIRTUAL FUNCTIONS
// ==========================================
class Patient {
protected:
    std::string name;
    int age;
    int* patientID; // Dynamic memory management

public:
    // Constructors & Destructors
    Patient(std::string n, int a, int id) : name(n), age(a) {
        patientID = new int(id); // Dynamic Memory Allocation
    }
    
    virtual ~Patient() {
        delete patientID; // Destructor Management
    }

    // Pure Virtual Function (Abstract Class)
    virtual std::string getPatientType() const = 0;
    
    // Virtual Function for Runtime Polymorphism
    virtual std::string getDetails() const {
        return "ID: " + std::to_string(*patientID) + " | Name: " + name + " | Age: " + std::to_string(age);
    }

    int getID() const { return *patientID; }
    std::string getName() const { return name; }
};

// ==========================================
// 3. INHERITANCE (Single & Multilevel)
// ==========================================
class InPatient : public Patient {
private:
    std::string roomNumber;
protected:
    double BaseAdmissionFee; // For demonstrating hybrid/multilevel attributes later

public:
    InPatient(std::string n, int a, int id, std::string room) 
        : Patient(n, a, id), roomNumber(room), BaseAdmissionFee(500.0) {}

    std::string getPatientType() const override { return "In-Patient (Admitted)"; }
    
    std::string getDetails() const override {
        return Patient::getDetails() + " | Room: " + roomNumber;
    }
};

// Critical Patient inherits from InPatient (Multilevel Inheritance)
class CriticalPatient : public InPatient {
private:
    std::string icuBedID;
public:
    CriticalPatient(std::string n, int a, int id, std::string room, std::string icuID)
        : InPatient(n, a, id, room), icuBedID(icuID) {}

    std::string getPatientType() const override { return "CRITICAL CARE PATIENT"; }
    
    std::string getDetails() const override {
        return InPatient::getDetails() + " | ICU Bed: " + icuBedID + " [Requires Constant Monitoring]";
    }
};

// ==========================================
// 4. OPERATOR & FUNCTION OVERLOADING
// ==========================================
class VitalSign {
public:
    int heartRate;
    int systolicBP;

    VitalSign(int hr, int bp) : heartRate(hr), systolicBP(bp) {
        // Exception Handling Trigger
        if (hr < 0 || hr > 250 || bp < 0 || bp > 300) {
            throw InvalidVitalException("Physiologically impossible vital signs detected!");
        }
    }

    // Operator Overloading (+) to average out/combine vital states if needed
    VitalSign operator+(const VitalSign& other) {
        return VitalSign((this->heartRate + other.heartRate) / 2, (this->systolicBP + other.systolicBP) / 2);
    }
};

// ==========================================
// 5. SYSTEM MANAGEMENT (The Controller)
// ==========================================
class HealthMonitorSystem {
private:
    std::vector<std::unique_ptr<Patient>> records; // Polymorphic pointer storage

public:
    HealthMonitorSystem() {}

    // Function Overloading (Polymorphism via Overloading)
    void addPatient(std::string name, int age, int id, std::string room) {
        records.push_back(std::make_unique<InPatient>(name, age, id, room));
    }

    void addPatient(std::string name, int age, int id, std::string room, std::string icuID) {
        records.push_back(std::make_unique<CriticalPatient>(name, age, id, room, icuID));
    }

    std::vector<std::string> fetchSystemReport() {
        std::vector<std::string> report;
        for (const auto& patient : records) {
            // Demonstrating Runtime Polymorphism dynamically picking getPatientType and getDetails
            std::string line = "[" + patient->getPatientType() + "] " + patient->getDetails();
            report.push_back(line);
        }
        return report;
    }

    std::string processVitals(int hr, int bp) {
        try {
            VitalSign v(hr, bp);
            if (hr > 120 || bp > 140) {
                return "⚠️ CRITICAL WARNING: Vitals out of normal bounds! Triggering clinical alert.";
            }
            return "✅ Vitals Normal. Stable condition.";
        } 
        catch (const InvalidVitalException& e) {
            return std::string("❌ Exception Caught: ") + e.what();
        }
    }
};

// ==========================================
// PYBIND11 BINDINGS (Exposing C++ to Python)
// ==========================================
PYBIND11_MODULE(healthcare_core, m) {
    py::class_<HealthMonitorSystem>(m, "HealthMonitorSystem")
        .def(py::init<>())
        // Expose overloaded methods explicitly using function pointers
        .def("add_in_patient", py::overload_cast<std::string, int, int, std::string>(&HealthMonitorSystem::addPatient))
        .def("add_critical_patient", py::overload_cast<std::string, int, int, std::string, std::string>(&HealthMonitorSystem::addPatient))
        .def("fetch_system_report", &HealthMonitorSystem::fetchSystemReport)
        .def("process_vitals", &HealthMonitorSystem::processVitals);
}