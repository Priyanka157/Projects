import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

st.title('💡 Smart Lighting Insights Dashboard')

# Load and preprocess data
df = pd.read_csv('2019Floor1.csv')
df['timestamp'] = pd.to_datetime(df['Date'])  # Fix here
df = df.set_index('timestamp')
df = df.fillna(method='ffill')

# Select a zone
zone = st.selectbox('Select Zone', ['z1_Light(kW)', 'z2_Light(kW)', 'z3_Light(kW)', 'z4_Light(kW)'])

# Daily average
df_daily = df[[zone]].resample('D').mean()

# Show chart
st.line_chart(df_daily)
