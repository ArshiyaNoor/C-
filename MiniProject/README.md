# High-Performance Time Tracker and Duration Adder

## Project Description
The High-Performance Time Tracker and Duration Adder is a streamlined productivity tool designed to simplify project timeline logging and precise time arithmetic. Tracking time manually often leads to messy calculations when dealing with mismatched hours and minutes, such as adding 45 minutes to 35 minutes. This application provides a centralized timesheet registry where users can log tasks under specific categories and utilize a dedicated duration calculator that automatically rolls over excess minutes into hours, ensuring clean project timeline summaries.

## Key Features
* Smart Time Accumulator: A standalone calculator that lets you add distinct time frames together with automated base-60 minute rollover math.
* Categorized Task Logging: Allows users to log distinct project activities under organized tags like Development, Design, Meetings, and Research.
* Live Timesheet Registry: Displays a clean, structured visual breakdown of all recorded activities stored in the active tracking session.
* Live Grand-Total Metric: Dynamically sums up and displays the overall billable project hours accumulated across all logged tasks.

## Advanced OOP Features Implemented
* Operator Overloading: Overrides the native binary + operator inside the Duration class to seamlessly sum multi-parameter variables (Hours and Minutes) while instantly evaluating 60-minute arithmetic overflow boundaries.
* Dynamic Memory Allocation: Leverages heap-allocated pointer structures (std::make_unique) to encapsulate duration logs inside volatile TrackedTask models safely.
* Robust Exception Handling: Utilizes structured try-catch parameters to throw custom time anomalies (like negative unit entries) immediately back to the presentation layer without dropping application states.
* Encapsulation and Registry Pattern: Fully isolates task data records inside a clean TimeTrackerSystem class controller, updating an interface array via string mapping streams.

## Architecture and Frameworks
* Core Engine: Native C++ Backend
* Interface Layer: Pybind11 Python Binding
* UI Module: Streamlit Web Dashboard
