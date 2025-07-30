import streamlit as st
import pandas as pd
import sqlite3
import matplotlib.pyplot as plt

DB_PATH = "../data/financial_data.db"

@st.cache_data(ttl=600)
def load_data():
    conn = sqlite3.connect(DB_PATH)
    query = "SELECT * FROM stock_data ORDER BY Date"
    df = pd.read_sql(query, conn, parse_dates=['Date'])
    conn.close()
    return df

def plot_stock(df):
    st.subheader("Stock Price with Moving Averages")
    plt.figure(figsize=(12,6))
    plt.plot(df['Date'], df['Close'], label='Close Price')
    plt.plot(df['Date'], df['MA_7'], label='7-day MA')
    plt.plot(df['Date'], df['MA_30'], label='30-day MA')
    plt.legend()
    st.pyplot(plt)

def generate_signals(df):
    df_signals = df.copy()
    df_signals["Signal"] = 0
    df_signals.loc[df_signals["MA_7"] > df_signals["MA_30"], "Signal"] = 1
    df_signals.loc[df_signals["MA_7"] < df_signals["MA_30"], "Signal"] = -1
    df_signals["Position"] = df_signals["Signal"].diff()
    return df_signals

def show_signals(df):
    st.subheader("Buy/Sell Signals")

    # Buy and sell signals based on crossover logic
    buy_signals = df[df['Position'] == 1]
    sell_signals = df[df['Position'] == -1]

    st.write("Buy Signals:")
    st.dataframe(buy_signals[['Date', 'Close']])

    st.write("Sell Signals:")
    st.dataframe(sell_signals[['Date', 'Close']])

    if st.button("Export signals to CSV"):
        signals_csv = pd.concat([buy_signals, sell_signals]).sort_values(by='Date')
        signals_csv.to_csv('../data/signals_report.csv', index=False)
        st.success("Signals exported to ../data/signals_report.csv")


def main():
    st.title("Financial Data Dashboard - AAPL")
    df = load_data()
    plot_stock(df)
    df_with_signals = generate_signals(df)
    show_signals(df_with_signals)

if __name__ == "__main__":
    main()
