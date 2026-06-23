import streamlit as st
import os
import sys

# Ensure Python can look for the compiled shared library in the current folder
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

# Import the compiled C++ Module
try:
    import healthcare_core
except ImportError:
    st.error("🚨 Could not find the compiled C++ module (`healthcare_core`). Please follow the build compilation steps below first!")
    st.stop()

# Initialize the C++ Core class into Streamlit State
if "monitor_system" not in st.session_state:
    st.session_state.monitor_system = healthcare_core.HealthMonitorSystem()

st.set_page_config(page_title="OOPXtreme Healthcare Monitor", layout="wide")
st.title("🏥 OOPXtreme: Intelligent Healthcare Monitor")
st.caption("Powered by an Advanced C++ Backend Engine with Runtime Polymorphism & Dynamic Memory")

# Sidebar - Add Patients
st.sidebar.header("📋 Patient Admission")
p_type = st.sidebar.selectbox("Patient Type", ["In-Patient (Standard)", "Critical Patient (ICU)"])
p_name = st.sidebar.text_input("Patient Name", "John Doe")
p_age = st.sidebar.number_input("Age", min_value=1, max_value=120, value=45)
p_id = st.sidebar.number_input("Patient ID (Unique Number)", min_value=1000, max_value=9999, value=1001)
p_room = st.sidebar.text_input("Room Ward Assigned", "Ward-3B")

icu_id = ""
if p_type == "Critical Patient (ICU)":
    icu_id = st.sidebar.text_input("ICU Bed ID Identifier", "ICU-09")

if st.sidebar.button("Register & Allocate Dynamic Resources"):
    if p_type == "In-Patient (Standard)":
        st.session_state.monitor_system.add_in_patient(p_name, p_age, p_id, p_room)
    else:
        st.session_state.monitor_system.add_critical_patient(p_name, p_age, p_id, p_room, icu_id)
    st.sidebar.success(f"Successfully deployed resources for {p_name}!")

# Main Dashboard Interface
col1, col2 = st.columns([3, 2])

with col1:
    st.subheader("👥 Active Patient Registry (Polymorphic Output)")
    report_data = st.session_state.monitor_system.fetch_system_report()
    
    if not report_data:
        st.info("No active patients currently tracked in memory.")
    else:
        for record in report_data:
            if "CRITICAL" in record:
                st.error(record)
            else:
                st.info(record)

with col2:
    st.subheader("🩺 Real-Time Vital Signs Simulator")
    st.write("Enter vitals to evaluate system bounds and trigger dynamic custom C++ Exception Handling structures.")
    
    hr = st.number_input("Heart Rate (BPM)", value=75)
    bp = st.number_input("Systolic Blood Pressure (mmHg)", value=120)
    
    if st.button("Evaluate Vitals via C++ Core"):
        # Sends inputs straight to the C++ exceptions block
        result_message = st.session_state.monitor_system.process_vitals(hr, bp)
        
        if "Exception" in result_message:
            st.warning(result_message)
        elif "WARNING" in result_message:
            st.error(result_message)
        else:
            st.success(result_message)