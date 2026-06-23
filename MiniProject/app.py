import streamlit as st
import os
import sys

sys.path.append(os.path.dirname(os.path.abspath(__file__)))

import time_core

if "time_system" not in st.session_state:
    st.session_state.time_system = time_core.TimeTrackerSystem()

st.set_page_config(page_title="C++ Powered Time Tracker", layout="wide")
st.title("⏱️ Time Tracker & Duration Adder (C++ Engine)")
st.caption("Performance Time Math Managed by an Advanced Native C++ Backend Layer")

col1, col2 = st.columns([1, 1])

# --- COLUMN 1: DURATION ADDER CALCULATOR ---
with col1:
    st.subheader("➕ Duration Accumulator Calculator")
    st.write("Add two distinct time frames together processed through overloaded C++ functions.")
    
    t1_col1, t1_col2 = st.columns(2)
    with t1_col1:
        d1_h = st.number_input("Duration 1: Hours", min_value=-10, value=2, key="d1h")
    with t1_col2:
        d1_m = st.number_input("Duration 1: Minutes", min_value=-10, value=45, key="d1m")
        
    st.write("➕")
    
    t2_col1, t2_col2 = st.columns(2)
    with t2_col1:
        d2_h = st.number_input("Duration 2: Hours", min_value=-10, value=1, key="d2h")
    with t2_col2:
        d2_m = st.number_input("Duration 2: Minutes", min_value=-10, value=30, key="d2m")

    if st.button("Calculate Accumulated Sum", type="primary"):
        # Triggers math inside C++ directly
        calc_result = st.session_state.time_system.add_two_durations(d1_h, d1_m, d2_h, d2_m)
        if "Exception" in calc_result:
            st.warning(calc_result)
        else:
            st.success(calc_result)

# --- COLUMN 2: TASK REGISTRY LOGGER ---
with col2:
    st.subheader("📝 Project Task Logger")
    
    task_name = st.text_input("Task/Activity Name", placeholder="e.g., Code Refactoring")
    task_cat = st.selectbox("Category Tag", ["Development", "Design", "Meetings", "Research"])
    
    log_col1, log_col2 = st.columns(2)
    with log_col1:
        log_h = st.number_input("Time Spent: Hours", min_value=0, value=0)
    with log_col2:
        log_m = st.number_input("Time Spent: Minutes", min_value=0, value=45)
        
    if st.button("Log Task Entry to Memory"):
        if task_name.strip() == "":
            st.error("Please enter a valid task name.")
        else:
            st.session_state.time_system.log_task(task_name, task_cat, log_h, log_m)
            st.toast("Logged securely via C++ registry structures!")

    st.markdown("---")
    st.subheader("📋 Tracked Timesheet Registry")
    
    report_data = st.session_state.time_system.fetch_registry_report()
    
    if not report_data:
        st.info("No active tasks logged in this backend memory pool yet.")
    else:
        for record in report_data:
            st.info(record)
            
        # Requests C++ loop calculation
        grand_total = st.session_state.time_system.calculate_grand_total()
        st.metric(label="Total Billable Time Accumulated (C++ Engine)", value=grand_total)
        
        if st.button("Clear Session"):
            st.session_state.time_system = time_core.TimeTrackerSystem()
            st.rerun()
