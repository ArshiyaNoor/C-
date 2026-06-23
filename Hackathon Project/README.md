# OOPXtreme: Intelligent Healthcare Monitor

## Project Description
The Intelligent Healthcare Monitor is a real-time patient tracking and vital signs simulation dashboard designed for high-stress medical wards. The system allows healthcare staff to register incoming patients, assign them to standard wards or intensive care units (ICU), and monitor their physiological vitals. By offloading complex data management and safety checks to a compiled native backend, the system guarantees high-speed processing, data integrity, and immediate clinical warnings when a patient's vitals cross hazardous boundaries.

## Key Features
* Dual-Tier Patient Registration: Supports separate asset tracking for standard In-Patients and high-risk Critical Care (ICU) patients.
* Real-Time Vital Signs Simulator: Simulates live patient heart rates and blood pressure tracking straight from the web interface.
* Automated Clinical Alerts: Instantly flags critical vital readings with highly visible UI warnings for healthcare personnel.
* Fail-Safe Data Validation: Prevents human data-entry errors by checking medical ranges before saving them to system memory.

## Advanced OOP Features Implemented
* Abstract Base Classes and Pure Virtual Functions: The foundational Patient class dictates core rules for resource tracking without allowing direct instantiation.
* Runtime Polymorphism: Dynamically manages heterogeneous collections of patients via smart pointers (std::unique_ptr), resolving derived types (InPatient vs. CriticalPatient) at runtime.
* Dynamic Memory and Resource Management: Custom constructor and destructor handling to safely manage memory allocations on the heap for persistent tracking variables.
* Custom Exception Handling: Implements an explicit InvalidVitalException structure to capture anomalous data fields before engine processing.
* Operator and Function Overloading: Incorporates mathematical vectoring overrides on physiological data structures (VitalSign addition operations) alongside flexible, overloaded registry methods.

## Architecture and Frameworks
* Backend: C++14 Engine
* Binding Layer: Pybind11 (Exposes native memory structures to Python wrappers)
* Frontend: Streamlit Interactive Dashboard
